#include "share.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void run_simulation(tcp_variant variant,
                    double    loss_prob,
                    double   *throughput,
                    double   *goodput) {
    tcp_state_t s = {
        .cwnd          = 1,
        .ssthresh      = 64,
        .packets_sent  = 0,
        .packets_retx  = 0,
        .packets_acked = 0
    };

    /* Discrete‐event: each round = one RTT */
    for (int round = 0; round < NUM_ROUNDS; round++) {
        int sent_this_round = s.cwnd;
        int acks_received   = 0;

        /* Send cwnd packets and randomly drop them */
        for (int i = 0; i < sent_this_round; i++) {
            s.packets_sent++;
            if (((double)rand() / (double)RAND_MAX) > loss_prob) {
                /* delivered & ACKed */
                acks_received++;
                s.packets_acked++;
            } else {
                /* lost */
                s.packets_retx++;
            }
        }

        /* Congestion‐control logic */
        if (acks_received == sent_this_round) {
            /* no loss: slow‐start then congestion avoidance */
            if (s.cwnd < s.ssthresh) {
                s.cwnd *= 2;
            } else {
                s.cwnd += 1;
            }
        } else {
            /* loss detected: cut window & adjust */
            s.ssthresh = s.cwnd / 2;
            if (s.ssthresh < 1) s.ssthresh = 1;

            if (variant == TAHOE) {
                /* Tahoe: back to slow‐start */
                s.cwnd = 1;
            } else {
                /* Reno: fast recovery */
                s.cwnd = s.ssthresh + 3;
            }
        }
    }

    /* Compute metrics */
    *throughput = (double)s.packets_acked / (double)NUM_ROUNDS;
    *goodput    = (double)s.packets_acked / (double)s.packets_sent;
}

int main(int argc, char **argv) {
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s LOSS_PROB [SEED]\n", argv[0]);
        return 1;
    }

    double loss_prob = atof(argv[1]);
    unsigned int seed = (argc == 3)
        ? (unsigned int)atoi(argv[2])
        : (unsigned int)time(NULL);
    srand(seed);

    /* determine variant from the executable name */
    tcp_variant variant = (strstr(argv[0], "tahoe") != NULL)
                        ? TAHOE
                        : RENO;

    double thr, gpt;
    run_simulation(variant, loss_prob, &thr, &gpt);

    /* print one CSV line to stdout */
    printf("%s,%.2f,%.2f,%.2f\n",
           (variant == TAHOE ? "Tahoe" : "Reno"),
           loss_prob, thr, gpt);

    return 0;
}
