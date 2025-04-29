#Compiles the TCP simulation program.

#gcc -std=c11 -Wall src/share.c src/tahoe.c -o build/tahoe
#gcc -std=c11 -Wall src/share.c src/reno.c  -o build/reno


#Run and append to the CSV:

#./build/tahoe 0.01 >> data/results.csv
#./build/reno  0.01 >> data/results.csv


#!/usr/bin/env bash
set -e

# absolute path to tcp_sim
#ROOT="/Users/hanjo/PA3Final/tcp_sim"
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")"/.. && pwd)"

# make sure build/ exists
mkdir -p "$ROOT/build"

# compile Tahoe
gcc -std=c11 -Wall \
    "$ROOT/src/share.c" "$ROOT/src/tahoe.c" \
    -o "$ROOT/build/tahoe"

# compile Reno
gcc -std=c11 -Wall \
    "$ROOT/src/share.c" "$ROOT/src/reno.c" \
    -o "$ROOT/build/reno"

echo "✓ Built Tahoe and Reno in $ROOT/build/"


# excute with theis command:
# chmod +x /Users/hanjo/PA3Final/tcp_sim/scripts/build.sh


