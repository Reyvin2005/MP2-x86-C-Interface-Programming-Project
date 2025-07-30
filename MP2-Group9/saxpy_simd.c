/*  Group 9, LBYARCH | S12A 
    Siongco, Raine Margaux A.
    Tan, Reyvin Matthew T.
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

extern void saxpy_simd(float A, float* X, float* Y, float* Z, int n);

void saxpy_simd_c(float A, float* X, float* Y, float* Z, int n) 
{
    for (int i = 0; i < n; i++) 
    {
        Z[i] = A * X[i] + Y[i];
    }
}
  
int main() 
{
    int testsizes[] = { 1048576, 16777216, 268435456 }; // 2^20, 2^24, 2^28 
    int num_sizes = sizeof(testsizes) / sizeof(testsizes[0]);
    float A = 2.0f; // Input Scalar Value (Used 2.0 based from example)
    int i, j;

    printf("SAXPY Performance Analysis\n");
    printf("Vector sizes: 2^20, 2^24, 2^28\n\n");

    for (j = 0; j < num_sizes; j++) 
    {
        int n = testsizes[j];

        printf("Testing with n = %d\n\n", n);

        // Allocation of memory
        float* X = (float*)malloc(n * sizeof(float));
        float* Y = (float*)malloc(n * sizeof(float));
        float* Z_c = (float*)malloc(n * sizeof(float));
        float* Z_asm = (float*)malloc(n * sizeof(float));

        if (!X || !Y || !Z_c || !Z_asm) 
        {
            printf("Memory allocation too large for n = %d\n", n);
            continue;
        }

        // Initializes the arrays with random values from (0.0 to 100.0)
        for (i = 0; i < n; i++) 
        {
            X[i] = ((float)rand() / RAND_MAX) * 100.0f;
            Y[i] = ((float)rand() / RAND_MAX) * 100.0f;
        }

		// Execution time of C version (measures average execution time after 30 times)
		clock_t start = clock(); // Used clock_t to measure the execution time for comparison

        for (i = 0; i < 30; i++) 
        {
            saxpy_simd_c(A, X, Y, Z_c, n);
        }
        clock_t end = clock();
        double time_c = ((double)(end - start)) / CLOCKS_PER_SEC / 30.0;

        printf("Time for n using C = %d: %f seconds\n", n, time_c);
        printf("Output for n using C = %d:\n", n);
		printf("Output of the First 10 elements:\n");

        for (i = 0; i < 10; i++) 
        {
            printf("%f ", Z_c[i]);
        }
        printf("\n\n");

        //  Execution time of Assembly version (measures average execution time after 30 times)
        start = clock();

        for (i = 0; i < 30; i++) 
        {
            saxpy_simd(A, X, Y, Z_asm, n);
        }
        end = clock();
        double time_asm = ((double)(end - start)) / CLOCKS_PER_SEC / 30.0;

        printf("Time for n using Assembly = %d: %f seconds\n", n, time_asm);
        printf("Output for n using Assembly = %d\n", n);
		printf("Output of the First 10 elements:\n");


        for (i = 0; i < 10; i++) 
        {
            printf("%f ", Z_asm[i]);
        }
        printf("\n\n");

		// Performance analysis of Execution Times
        double speediff = time_c / time_asm;     
		printf("Speediff (C/ASM) Time difference: Assembly is %.2fx faster\n", speediff); // Time difference between the two versions

		// Correctness checks (checks all elements of the two arrays)
        int check = 1;
        for (i = 0; i < n; i++) 
        {
            float difference = fabs(Z_c[i] - Z_asm[i]);
			if (difference > 1e-6) // 0.000001 threshold for correctness
            {
                check = 0;
                printf("Incorrect match at index %d: C = %f, ASM = %f, Difference = %f\n", i, Z_c[i], Z_asm[i], difference); // Error checking
            }
        }
        if (check)
            {
                printf("Correctness check: CORRECT\n");
                printf("Successfuly Tested\n\n");
            }
        else
            {
                printf("Correctness check: INCORRECT\n\n");
            }
            
        free(X); free(Y); free(Z_c); free(Z_asm);
    }

    return 0;
}
