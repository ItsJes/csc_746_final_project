#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>


#include <cmath> // For: fabs

#include <cblas.h>
#include <string.h>

/*
 * This routine performs a dgemv operation
 * Y :=  A * X + Y
 * where A is n-by-n matrix stored in row-major format, and X and Y are n by 1 vectors.
 * On exit, A and X maintain their input values.
 */
 void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition (vector<int>arr, int low, int high)
{
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element
 
    for (int j = low; j <= high- 1; j++)
    {

        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
 
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int index = partition(arr, low, high);
        quickSort(arr, low, index - 1);
        quickSort(arr, index + 1, high);
    }
}
void printArray(int arr[], int size) 
{ 
    for (int i = 0; i < size; i++) 
        cout << arr[i] << " "; 
    cout << endl; 
} 

/* The benchmarking program */
int main(int argc, char** argv) 
{
   // std::cout << "Description:\t" << dgemv_desc << std::endl << std::endl;

    std::cout << std::fixed << std::setprecision(2);

    //std::vector<int> test_sizes{64, 128, 256, 512, 1024, 2048};
    std::vector<int> test_sizes{1024, 2048, 4096, 8192, 16384};

    int n_problems = test_sizes.size();

    // preallocate memory buffers for all problems: assume the last number in test_sizes is the largest

    // allocate memory for 2 NxN matrices and 4 Nx1 vectors

    int max_size = test_sizes[n_problems-1];


           // load up matrics with some random numbers
    /* For each test size */
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time = std::chrono::high_resolution_clock::now();

    for (int n : test_sizes) 
    {
        printf("Working on problem size N=%d \n", n);

        std::vector<unsigned long long> vec(n,0);
  
        srand(time(0));
  
        generate(vec.begin(), vec.end(), rand);

        // insert start timer code here
        std::chrono::time_point<std::chrono::high_resolution_clock> start_time = std::chrono::high_resolution_clock::now();

        quickSort(vec, 0, n - 1);

        std::chrono::time_point<std::chrono::high_resolution_clock> end_time = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> elapsed = end_time - start_time;
        std::cout << " Vector Sort: " << printArray(vec, n - 1)  << " " << std::endl;
        std::cout << " Elapsed time is: " << elapsed.count() << " " << std::endl;
    
    } // end loop over problem sizes



    return 0;
}