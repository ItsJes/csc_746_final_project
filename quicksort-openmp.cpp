#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>
#include <cmath> // For: fabs
#include <cblas.h>
#include <stack>


const char* dgemv_desc = "OpenMP dgemv.";

/*
 * This routine performs a dgemv operation
 * Y :=  A * X + Y
 * where A is n-by-n matrix stored in row-major format, and X and Y are n by 1 vectors.
 * On exit, A and X maintain their input values.
 */
using namespace std;
 void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int Partition(vector<unsigned long long> &v, int low, int high)
{
	
	int pivot = high;
	int j = low;
        for(int i = low;i < high; ++i)
        {
            if(v[i] < v[pivot])
            {
                swap(v[i], v[j]);
                ++j;
            }
        }
    
	swap(v[j], v[pivot]);
	return j;
	
}

void printArray(vector<unsigned long long> &v, int size) 
{ 
    for (int i = 0; i < size; i++)
    {
        cout << v[i] << " "; 
    }
    cout << endl; 
} 

void quickSortOMP(vector<unsigned long long> &v, int low, int high)
{
      
   #pragma omp parallel
   {
      int nthreads = omp_get_num_threads();
      int thread_id = omp_get_thread_num();
      printf("Hello world: thread %d of %d checking in. \n", thread_id, nthreads);
   }
   /*
    if (low < high)
    {
        int index = Partition(v, low, high);
        
        #pragma omp parallel sections
        {
           #pragma omp section
           {
            quickSortOMP(v, low, index - 1);
           }
           #pragma omp section
           {
            quickSortOMP(v, index + 1, high);
           }
        }
    
    }
    */

       if (low < high)
    {
        int p = Partition(v, low, high);
        
           #pragma omp task default(none) firstprivate(v,low,p)
           {
            quickSortOMP(v, low, p - 1);
           }
           #pragma omp task default(none) firstprivate(v,high,p)
           {
            quickSortOMP(v, p + 1, high);
           }
        
    
    }
    
}
/*
void printArray(vector<int> &v, int size) 
{ 
    for (int i = 0; i < size; i++){
        cout << v[i] << " ";
    } 
    cout << endl; 
} 
*/
/* The benchmarking program */
int main(int argc, char** argv) 
{
   // std::cout << "Description:\t" << dgemv_desc << std::endl << std::endl;

    std::cout << std::fixed << std::setprecision(10);

    //std::vector<int> test_sizes{64, 128, 256, 512, 1024, 2048};
   // std::vector<int> test_sizes{1024, 2048, 4096, 8192, 16384};
      std::vector<int> test_sizes{32};

    //int n_problems = test_sizes.size();

    // preallocate memory buffers for all problems: assume the last number in test_sizes is the largest

    // allocate memory for 2 NxN matrices and 4 Nx1 vectors

    //int max_size = test_sizes[n_problems-1];


           // load up matrics with some random numbers
    /* For each test size */

    for (int n : test_sizes) 
    {
        printf("Working on problem size N=%d \n", n);

        std::vector<unsigned long long> vec(n,0);
  
        srand(time(0));
  
        generate(vec.begin(), vec.end(), rand);

        // insert start timer code here
        std::chrono::time_point<std::chrono::high_resolution_clock> start_time = std::chrono::high_resolution_clock::now();
        #pragma omp parallel default(none) shared(vec,n)
        {
            #pragma omp single nowait
            {
                quickSortOMP(vec, 0, n - 1);
            }
        }
     
 
        std::chrono::time_point<std::chrono::high_resolution_clock> end_time = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> elapsed = end_time - start_time;
        std::cout << " Vector Sort: " << std::endl;
       // printArray(vec, n - 1);
        std::cout << " Elapsed time is: " << elapsed.count() << " " << std::endl;
    
    } // end loop over problem sizes



    return 0;
}

// EOF
