#include <stdio.h>
#include <stdlib.h>
#include "share.h"
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s LOSS_PROB [SEED]\n", argv[0]);
        return 1;
    }

    double loss = atof(argv[1]);
    unsigned seed = (argc == 3)
                  ? (unsigned)atoi(argv[2])
                  : (unsigned)time(NULL);
    srand(seed);

    double thr, gpt;
    run_simulation(RENO, loss, &thr, &gpt);

    printf("Reno,%.2f,%.2f,%.2f\n",
           loss, thr, gpt);
    return 0;
}
