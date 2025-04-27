#!/usr/bin/env bash
set -e

ROOT="/Users/hanjo/PA3Final/tcp_sim"
BUILD="$ROOT/build"
DATA="$ROOT/data"

# losses to sweep
LOSSES=(0.00 0.01 0.02 0.05 0.10)

mkdir -p "$DATA"

# write header row
echo "variant,loss,throughput,goodput" > "$DATA/results.csv"

# fixed seed for reproducibility
SEED=123456

for loss in "${LOSSES[@]}"; do
    "$BUILD/tahoe" "$loss" "$SEED" >> "$DATA/results.csv"
    "$BUILD/reno"  "$loss" "$SEED" >> "$DATA/results.csv"
done

echo "✓ Wrote all results to $DATA/results.csv"

# Make it executable:
# chmod +x /Users/hanjo/PA3Final/tcp_sim/scripts/run_all.sh

