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

void sortingFunc(std::vector<int> array1)
{
thrust::device_vector<int> vec(array1);
std::cout << "sorting integers\n";
  {
    //print(vec);
    std::clock_t start;
    double duration;
    start = std::clock();
    thrust::sort(vec.begin(), vec.end());
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout<<"printf: "<< duration <<'\n';
	//print(vec);
    std::ofstream output_file("/home/hitesh/Desktop/Project/Project_Final_Work/pglog.csv");
    std::ostream_iterator<int> output_iterator(output_file, "\n");
    thrust::copy(vec.begin(), vec.end(), output_iterator);
  }
}
