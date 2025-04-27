#include <stdio.h>
#include <stdlib.h>
#include "share.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <loss_probability>\n", argv[0]);
        return 1;
    }

    double loss = atof(argv[1]);
    double thr, gpt;
    run_simulation(TAHOE, loss, &thr, &gpt);
    printf("Tahoe,%.2f,%.2f,%.2f\n", loss, thr, gpt);
    return 0;
}
