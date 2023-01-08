#ifndef FIBONACCI_H_
#define FIBONACCI_H_

#include <vector>

namespace ddd{
  // static
  // pros - fastest
  // cons - no out of bound checks
  const int fibsize = 31;
  const int fibonacciArray[fibsize] = {
    0, 1, 1, 2, 3, 
    5, 8, 13, 21, 34, 
    55, 89, 144, 233, 377, 
    610, 987, 1597, 2584, 4181,
    6765, 10946, 17711, 28657, 46368,
    75025, 121393, 196418, 317811, 514229, 
    832040
  };
  
  int fibonacciLoop(int); // do while
  int fibonacciForLoop(int); // for loop
  int fibonacciWhile(int); // while
  int fibonacciR(int); // recursive
  
  // meta
  template<int n>
  struct FibonacciM
  {
    constexpr static int value = FibonacciM<n-2>::value + FibonacciM<n-1>::value;
  };
  template<>
  struct FibonacciM<1>
  {
    constexpr static int value = 1;
  };
  template<>
  struct FibonacciM<0>
  {
    constexpr static int value = 0;
  };
  
  // get fibonacci sequences
  template<typename T = int>
  std::vector<T> getFibonacciSequence(int n)
  {
    std::vector<T> tmp;
    {
      tmp.reserve(n + 1);       
      tmp.push_back(0);
      if(n == 0) return tmp;
        tmp.push_back(1);
      if(n == 1) return tmp;
        tmp.push_back(1);
      if(n == 2) return tmp;
      
      n -= 2;
      auto e = tmp.end();
      while(n--)
      {
        tmp.push_back( *(e-2) + *(e-1) );
        e = tmp.end();
      }
    }
    return tmp;
  }

} // namespace ddd

#endif // FIBONACCI_H_
