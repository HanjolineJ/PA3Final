Compiles the TCP simulation program.

gcc -std=c11 -Wall src/share.c src/tahoe.c -o build/tahoe
gcc -std=c11 -Wall src/share.c src/reno.c  -o build/reno


Run and append to the CSV:

./build/tahoe 0.01 >> data/results.csv
./build/reno  0.01 >> data/results.csv

