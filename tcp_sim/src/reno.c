#include <stdio.h>
#include <stdlib.h>
#include "share.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <loss_probability>\n", argv[0]);
        return 1;
    }

    double loss = atof(argv[1]);
    run_simulation(RENO, loss, stdout);
    return 0;
}
