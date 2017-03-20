/* Name : Sanchit Chawla
   ID   : 5780642
*/

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
void transpose_submit(int M, int N, int A[N][M], int B[M][N]){

    int diag;
    int tempvalue;
    int incre;

    if (N == 32 || N == 64){

        if (N == 32){
            incre = 8;
        }
        else{
            incre = 4;
        }

        for (int c = 0; c < N; c+=incre){
                for (int r = 0; r < N; r+=incre){
                    for (int i = r; i < r + incre; i++){
                        for (int j = c; j < c + incre; j++){
                            if (i != j){
                                B[j][i] = A[i][j];
                            }
                            else{
                                tempvalue = A[i][j];
                                diag = i;
                            }
                        }
                        if (r == c){
                            B[diag][diag] = tempvalue;
                        }
                    }
                }
            }

    }
    else{

        incre = 16;

        for (int c = 0; c < M; c+=incre){
            for (int r = 0; r < N; r+=incre){
                for (int i = r; (i < r + incre) && (i < N); i++){
                    for (int j = c; (j < c + incre) && (j < M); j++){
                        if (i != j){
                            B[j][i] = A[i][j];
                        }
                        else{
                            tempvalue = A[i][j];
                            diag = i;
                        }
                    }

                    if (r == c){
                        B[diag][diag] = tempvalue;
                    }

                }
            }
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

