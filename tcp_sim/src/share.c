#include "share.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void run_simulation(tcp_variant variant, double loss_prob, FILE *out) {
    tcp_state_t s = {
        .cwnd            = 1,
        .ssthresh        = 64,
        .packets_sent    = 0,
        .packets_retx    = 0,
        .packets_acked   = 0
    };

    /* Seed RNG once per process */
    srand((unsigned)time(NULL));

    /* Discrete‐event: each round = one RTT */
    for (int round = 0; round < NUM_ROUNDS; round++) {
        int sent_this_round = s.cwnd;
        int acks_received   = 0;

        /* Send cwnd packets and randomly drop them */
        for (int i = 0; i < sent_this_round; i++) {
            s.packets_sent++;
            if (((double)rand() / RAND_MAX) > loss_prob) {
                /* packet delivered & ACKed */
                acks_received++;
                s.packets_acked++;
            } else {
                /* packet lost => retransmission later */
                s.packets_retx++;
            }
        }

        /* Congestion control update */
        if (acks_received == sent_this_round) {
            /* no loss this RTT */
            if (s.cwnd < s.ssthresh) {
                /* slow start: exponential */
                s.cwnd *= 2;
            } else {
                /* congestion avoidance: linear */
                s.cwnd += 1;
            }
        } else {
            /* detected loss -> cut window and adjust */
            s.ssthresh = s.cwnd / 2;
            if (s.ssthresh < 1) s.ssthresh = 1;

            if (variant == TAHOE) {
                /* Tahoe: go back to slow‐start */
                s.cwnd = 1;
            } else {
                /* Reno: fast recovery */
                s.cwnd = s.ssthresh + 3;
            }
        }
    }

    /* Compute metrics */
    double throughput = (double)s.packets_acked / NUM_ROUNDS;
    double goodput    = (double)s.packets_acked / s.packets_sent;

    /* Output one CSV line */
    fprintf(out,
            "%s,%.2f,%.2f,%.2f\n",
            (variant==TAHOE ? "Tahoe" : "Reno"),
            loss_prob,
            throughput,
            goodput);
            
}


