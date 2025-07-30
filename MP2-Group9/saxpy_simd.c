/*  Group 9, LBYARCH S12A 
    Siongco, Raine Margaux A.
    Tan, Reyvin Matthew T.
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

extern void saxpy_simd(float A, float* X, float* Y, float* Z, int n);

void saxpy_c(float A, float* X, float* Y, float* Z, int n) {
    for (int i = 0; i < n; i++) {
        Z[i] = A * X[i] + Y[i];
    }
}
  
int main() {
    int sizes[] = { 1048576, 16777216, 268435456 }; // 2^20, 2^24, 2^28 
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    float A = 2.0f; // Input Scalar Value (Used 2.0 based from example)

    printf("SAXPY Performance Analysis\n");
    printf("Vector sizes: 2^20, 2^24, 2^28\n\n");

    for (int k = 0; k < num_sizes; k++) {
        int n = sizes[k];

        printf("Testing with n = %d\n", n);

        // Allocate memory
        float* X = (float*)malloc(n * sizeof(float));
        float* Y = (float*)malloc(n * sizeof(float));
        float* Z_c = (float*)malloc(n * sizeof(float));
        float* Z_asm = (float*)malloc(n * sizeof(float));

        if (!X || !Y || !Z_c || !Z_asm) {
            printf("Memory allocation failed for n = %d\n", n);
            printf("Try reducing vector size or use a machine with more RAM\n\n");
            continue;
        }

        // Initializes the arrays with random values from (0.0 to 100.0)
        for (int i = 0; i < n; i++) {
            X[i] = ((float)rand() / RAND_MAX) * 100.0f;
            Y[i] = ((float)rand() / RAND_MAX) * 100.0f;
        }

		// Execution time of C version (measures average execution time after 30 times)
		clock_t start = clock(); // Used clock_t to measure the execution time for comparison
        for (int i = 0; i < 30; i++) {
            saxpy_c(A, X, Y, Z_c, n);
        }
        clock_t end = clock();
        double time_c = ((double)(end - start)) / CLOCKS_PER_SEC / 30.0;

        printf("C version time for n = %d: %f seconds\n", n, time_c);
        printf("C version output for n = %d (first 10 elements):\n", n);
        for (int i = 0; i < 10; i++) {
            printf("%f ", Z_c[i]);
        }
        printf("\n\n");

        //  Execution time of Assembly version (measures average execution time after 30 times)
        start = clock();
        for (int i = 0; i < 30; i++) {
            saxpy_simd(A, X, Y, Z_asm, n);
        }
        end = clock();
        double time_asm = ((double)(end - start)) / CLOCKS_PER_SEC / 30.0;

        printf("Assembly version time for n = %d: %f seconds\n", n, time_asm);
        printf("Assembly version output for n = %d (first 10 elements):\n", n);
        for (int i = 0; i < 10; i++) {
            printf("%f ", Z_asm[i]);
        }
        printf("\n");

		// Performance analysis of Execution Times
        double speedup = time_c / time_asm;     
		printf("Speedup (C/ASM): %.2fx\n", speedup); // Time difference between the two versions

        // Correctness check (first 100 elements)
        int correct = 1;
        for (int i = 0; i < 100 && i < n; i++) {
            float difference = fabs(Z_c[i] - Z_asm[i]);
            if (difference > 1e-6) {
                correct = 0;
                printf("Mismatch at index %d: C = %f, ASM = %f, Diff = %f\n", i, Z_c[i], Z_asm[i], difference);
            }
        }
        if (correct)
            printf("Correctness check: PASSED\n\n");
        else
            printf("Correctness check: FAILED\n\n");

        free(X); free(Y); free(Z_c); free(Z_asm);
    }

    return 0;
}