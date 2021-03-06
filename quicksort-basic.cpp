#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>


#include <cmath> // For: fabs

#include <cblas.h>
#include <string.h>

using namespace std;

 void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int Partition(vector<unsigned long long> &v, int low, int high){
	
	int pivot = high;
	int j = low;
	for(int i = low;i < high; ++i){
		if(v[i] < v[pivot]){
			swap(v[i], v[j]);
			++j;
		}
	}
	swap(v[j], v[pivot]);
	return j;
	
}
 
void quickSort(vector<unsigned long long> &v, int low, int high)
{
    if (low < high)
    {
        int index = Partition(v, low, high);
        quickSort(v, low, index - 1);
        quickSort(v, index + 1, high);
    }
}

/*
void printArray(vector<unsigned long long> &v, int size) 
{ 
    for (int i = 0; i < size; i++) 
        cout << v[i] << " "; 
    cout << endl; 
} 
*/

int main(int argc, char** argv) 
{
    //std::vector<int> test_sizes{64, 128, 256, 512, 1024, 2048};
    std::vector<int> test_sizes{1024, 2048, 4096, 8192, 16384};
   // std::vector<int> test_sizes{32};

   // int n_problems = test_sizes.size();


    for (int n : test_sizes) 
    {
        printf("Working on problem size N=%d \n", n);
        std::cout << std::fixed << std::setprecision(10);

        std::vector<unsigned long long> vec(n,0);
  
        srand(time(0));
  
        generate(vec.begin(), vec.end(), rand);

        // insert start timer code here
        std::chrono::time_point<std::chrono::high_resolution_clock> start_time = std::chrono::high_resolution_clock::now();

        quickSort(vec, 0, n - 1);

        std::chrono::time_point<std::chrono::high_resolution_clock> end_time = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> elapsed = end_time - start_time;
        std::cout << " Vector Sort: " << std::endl;
        std::cout << " Elapsed time is: " << elapsed.count() << " " << std::endl;
    
    } // end loop over problem sizes



    return 0;
}
