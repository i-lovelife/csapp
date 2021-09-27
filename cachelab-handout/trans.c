/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
int min(int x, int y) {return x>y?y:x;}
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, start_x, start_y, end_x, end_y, block_size, next_i, tmp;
    if (M == 32) {
        block_size = 8;
        for (start_x = 0; start_x < N; start_x+=block_size) {
            for (start_y = 0; start_y < M; start_y+=block_size) {
                end_x = min(start_x + block_size, N);
                end_y = min(start_y + block_size, M);
                for (i = start_x; i < end_x; i++) {
                    next_i = (i+1) == end_x? start_x:(i+1);
                    for (j = start_y; j < end_y; j++) {
                        if (i == j){
                            B[next_i][next_i] = A[i][j];
                        }
                        else {
                            B[j][i] = A[i][j];
                        }
                    }
                }
                if (start_x >= start_y && start_x < end_y){
                    tmp = B[start_x][start_x];
                    for (i = start_x + 1; i < end_x; i++) {
                        if (i >= start_y && i < end_y) {
                            B[i - 1][i - 1] = B[i][i]; 
                        }
                    }
                    B[end_x - 1][end_x - 1] = tmp;
                }
            }
        }
    }

    if (M == 64) {
        block_size = 4;
        for (start_x = 0; start_x < N; start_x+=block_size) {
            for (start_y = 0; start_y < M; start_y+=block_size) {
                end_x = min(start_x + block_size, N);
                end_y = min(start_y + block_size, M);
                for (i = start_x; i < end_x; i++) {
                    for (j = start_y; j < end_y; j++) {
                        if (i != j){
                            B[j][i] = A[i][j];
                        }
                    }
                }
            }
        }
        for (i = 0; i < M; i++) {
            B[i][i] = A[i][i];
        }
    }
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    //registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

