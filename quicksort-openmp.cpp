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
   
    if (low < high)
    {
        int p = Partition(v, low, high);
        
        #pragma omp parallel sections
        {
           #pragma omp section
           {
            quickSortOMP(v, low, p - 1);
           }
           #pragma omp section
           {
            quickSortOMP(v, p + 1, high);
           }
        }
    
    }
    
/*  Quicksort using task
    if (low < high)
    {
        int p = Partition(v, low, high);
        omp_set_num_threads( 4 );
        #pragma omp task default(none) firstprivate(v,low,p)
             quickSortOMP(v, low, p - 1);
        #pragma omp taskwait
        #pragma omp task default(none) firstprivate(v,high,p)
             quickSortOMP(v, p + 1, high);
        #pragma omp taskwait
        
    
    }
    */


/* Iterative version on Quicksort
    std::vector<int> s;
 
    int top = -1;
    s[++top] = low;
    s[++top] = high;

    #pragma omp parallel
    while (top >= 0) 
    {
        
        high = s[top--];
        low = s[top--];
 
        int p = Partition(v, low, high);
 
        if (p - 1 > low) {
            s[++top] = low;
            s[++top] = p - 1;
        }

        if (p + 1 < high) {
            s[++top] = p + 1;
            s[++top] = high;
        }
    }
    */
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

int main(int argc, char** argv) 
{

    std::cout << std::fixed << std::setprecision(10);

    //std::vector<int> test_sizes{64, 128, 256, 512, 1024, 2048};
    std::vector<int> test_sizes{1024, 2048, 4096, 8192, 16384};
     // std::vector<int> test_sizes{32};


    for (int n : test_sizes) 
    {
        printf("Working on problem size N=%d \n", n);

        std::vector<unsigned long long> vec(n,0);
  
        srand(time(0));
  
        generate(vec.begin(), vec.end(), rand);

        std::chrono::time_point<std::chrono::high_resolution_clock> start_time = std::chrono::high_resolution_clock::now();

        quickSortOMP(vec, 0, n - 1);
     
        std::chrono::time_point<std::chrono::high_resolution_clock> end_time = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> elapsed = end_time - start_time;
        std::cout << " Vector Sort: " << std::endl;
        std::cout << " Elapsed time is: " << elapsed.count() << " " << std::endl;
    
    } // end loop over problem sizes



    return 0;
}

// EOF
