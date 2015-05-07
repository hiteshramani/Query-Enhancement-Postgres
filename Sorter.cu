#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/sort.h>
#include <thrust/random.h>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>


void print(const thrust::device_vector<int>& v)
{
  for(size_t i = 0; i < v.size(); i++)
    std::cout << " " << v[i];
  std::cout << "\n";
}

// user-defined comparison operator that acts like less<int>,
// except even numbers are considered to be smaller than odd numbers
struct evens_before_odds
{
  __host__ __device__
  bool operator()(int x, int y)
  {
    if (x % 2 == y % 2)
      return x < y;
    else if (x % 2)
      return false;
    else
      return true;
  }
};

/* Sorting Ascending Order */
void sortingFuncAsc(std::vector<int> host_array)
{
thrust::device_vector<int> device_vecArray(host_array);
std::cout << "sorting integers\n";
  {
	/* Start the Sorter clock */
    std::clock_t start_sort;
    double duration_sort;
    start_sort = std::clock();
    
    /* Sort the Array */
    thrust::sort(device_vecArray.begin(), device_vecArray.end());
    
    /* Calculate the duration and print it */
    duration_sort = ( std::clock() - start_sort ) / (double) CLOCKS_PER_SEC;
    std::cout<<"sorting time: "<< duration_sort <<'\n';
	
	/* Start the Copy clock */
	std::clock_t start_copy;
    double duration_copy;
    start_copy = std::clock();
    
    /* Copy Vectory array to the pglog csv file */
    std::ofstream output_file("/home/hitesh/Desktop/Project/Project_Final_Work/pglog.csv");
    std::ostream_iterator<int> output_iterator(output_file, "\n");
    thrust::copy(device_vecArray.begin(), device_vecArray.end(), output_iterator);
    
    /* Calculate the Copying duration and print it */
    duration_copy = ( std::clock() - start_copy ) / (double) CLOCKS_PER_SEC;
    std::cout<<"copying time: "<< duration_copy <<'\n';
  }
}

/*Sorting Descending Order */
void sortingFuncDesc(std::vector<int> host_array)
{
thrust::device_vector<int> device_vecArray(host_array);
std::cout << "sorting integers\n";
  {
	/* Start the Sorter clock */
    std::clock_t start_sort;
    double duration_sort;
    start_sort = std::clock();
    
    /* Sort the Array */
    thrust::sort(device_vecArray.begin(), device_vecArray.end(), thrust::greater<int>());
    
    /* Calculate the duration and print it */
    duration_sort = ( std::clock() - start_sort ) / (double) CLOCKS_PER_SEC;
    std::cout<<"sorting time: "<< duration_sort <<'\n';
	
	/* Start the Copy clock */
	std::clock_t start_copy;
    double duration_copy;
    start_copy = std::clock();
    
    /* Copy Vectory array to the pglog csv file */
    std::ofstream output_file("/home/hitesh/Desktop/Project/Project_Final_Work/pglog.csv");
    std::ostream_iterator<int> output_iterator(output_file, "\n");
    thrust::copy(device_vecArray.begin(), device_vecArray.end(), output_iterator);
    
    /* Calculate the Copying duration and print it */
    duration_copy = ( std::clock() - start_copy ) / (double) CLOCKS_PER_SEC;
    std::cout<<"copying time: "<< duration_copy <<'\n';
  }
}
