#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <partition.h>

const char* dgemv_desc = "OpenMP dgemv.";

/*
 * This routine performs a dgemv operation
 * Y :=  A * X + Y
 * where A is n-by-n matrix stored in row-major format, and X and Y are n by 1 vectors.
 * On exit, A and X maintain their input values.
 */

void quickSortOMP(int arr[], int low, int high)
{
      #pragma omp parallel
   {
      int nthreads = omp_get_num_threads();
      int thread_id = omp_get_thread_num();
      printf("Hello world: thread %d of %d checking in. \n", thread_id, nthreads);
   }
   
    if (low < high)
    {
        int index = partition(arr, low, high);
        #pragma omp parallel sections{
           #pragma omp section{
            quickSort(arr, low, index - 1);
           }
           #pragma omp section{
            quickSort(arr, index + 1, high);
           }
        }
    }
   
}