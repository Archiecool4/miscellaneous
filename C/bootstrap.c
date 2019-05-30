#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#define SIZE 100                // How many samples to bootstrap with
#define BINCOUNT 30             // How many bins to do the graph with
#define RANDOM (rand() % 10000) // Picks random values between 0 and 10000

/*
 * Picks random samples from an array and returns an array of the same length
 */
int *bs_sample(int *arr, int len) {
    int i, idx;
    int *sample = malloc(len * sizeof(int));
    assert(sample != NULL);
    for (i = 0; i < len; i++) {
        idx = (rand() % len);
        sample[i] = arr[idx];
    }
    return sample;
}

/*
 * Returns the mean value of a bootstrap sample
 */
double bs_replicate(int *arr, int len) {
    int i, count = 0;
    int *sample = bs_sample(arr, len);
    for (i = 0; i < len; i++) {
        count += sample[i];
    }
    free(sample);
    return (double) count / len;
}

/*
 * Draws a specified amount of bootstrap samples and returns an array
 */
double *draw_bs_reps(int *arr, int len, int iter) {
    int i;
    double *reps = malloc(iter * sizeof(double));
    assert(reps != NULL);
    for (i = 0; i < iter; i++) {
        reps[i] = bs_replicate(arr, len);
    }
    return reps;
}

int main(int argc, char *argv[]) {
    int i, j, iter, count;
    int bins[BINCOUNT] = {0};
    int *arr;
    double rep, min = INT_MAX, max = INT_MIN, inc, temp;
    double *reps;
    char *filename;
    FILE *f;

    if (argc == 1 || argc > 3) {
        fprintf(stderr, "Usage: %s [iterations] filename\n", argv[0]);
        exit(1);
    }

    iter = argc == 3 ? atoi(argv[1]) : 10000; // If not specified in command line args, sets iterations to 10000
    filename = argc == 3 ? argv[2] : argv[1];
    strcat(filename, ".csv");                 // We will use CSV so it'll be easy to graph in MS Excel
    f = fopen(filename, "w+");
    arr = malloc(SIZE * sizeof(int));
    assert(arr != NULL);
    for (i = 0; i < SIZE; i++) {
        // Pulling random samples from defined macro
        arr[i] = RANDOM;
    }
    
    // Get bootstrap replicates
    reps = draw_bs_reps(arr, SIZE, iter);
   
    // Get min and max of reps so we can calculate bincounts
    for (i = 0; i < iter; i++) {
        if (reps[i] > max) {
            max = reps[i];
        }
        if (reps[i] < min) {
            min = reps[i];
        }
    }
    
    // Bin increment
    inc = (max - min) / BINCOUNT;

    for (i = 0; i < iter; i++) {
        rep = reps[i];
        temp = min;
        count = 0;
        while (temp < max) {
            if (rep <= temp) {
                // Records count in bin if sample is less than threshold
                bins[count]++;
                break;
            }
            temp += inc;
            count++;
        }
    }

    fputs("Value,Probability\n", f);
    temp = min;
    for (i = 0; i < BINCOUNT; i++) {
        for (j = 0; j < BINCOUNT; j++, temp += inc / BINCOUNT) {
            // Writes BINCOUNT number of data points for each bin to the CSV
            fprintf(f, "%f,%d\n", temp, bins[i]);
        }
    }
   
    fclose(f);
    free(arr);
    free(reps);
    return 0;
}
