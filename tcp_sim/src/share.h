#ifndef SHARE_H
#define SHARE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* How many discrete rounds (RTTs) to simulate */
#define NUM_ROUNDS     1000

typedef enum { TAHOE, RENO } tcp_variant;

typedef struct {
    int cwnd;                  // congestion window (in MSS units)
    int ssthresh;              // slow-start threshold
    int packets_sent;          // total packets ever sent
    int packets_retx;          // total retransmissions
    int packets_acked;         // total unique ACKs
} tcp_state_t;

void run_simulation(tcp_variant variant,
    double    loss_prob,
    double   *throughput,
    double   *goodput);

#endif // SHARE_H
