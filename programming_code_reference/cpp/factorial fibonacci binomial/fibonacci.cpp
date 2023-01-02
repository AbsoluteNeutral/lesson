#include "fibonacci.h"

namespace ddd{
  // static
  // pros - fastest
  // cons - no out of bound checks
  const int fibsize = 31;
  const int fibArray[fibsize] = {
    0, 1, 1, 2, 3, 
    5, 8, 13, 21, 34, 
    55, 89, 144, 233, 377, 
    610, 987, 1597, 2584, 4181,
    6765, 10946, 17711, 28657, 46368,
    75025, 121393, 196418, 317811, 514229, 
    832040
  };


  unsigned Fibonacci(unsigned N)
  {
    if(N == 0) return 0;
    if(N == 1) return 1;
    unsigned fib0 = 0;
    unsigned fib1 = 1;
    unsigned tmp  = fib1;
    --N;
    while(--N)
    {
      tmp  = fib1;
      fib1 += fib0;
      fib0 = tmp;
    }
    return fib0 + fib1;
  }
}// namespace ddd

//#define _TEST_THIS 1
#ifdef _TEST_THIS
#include <iostream>
/* Recursive */
unsigned FibonacciRecursive(unsigned N)
{
  if(N == 0) return 0;
  if(N == 1) return 1;
  return FibonacciRecursive(N-2) + FibonacciRecursive(N-1);
}

/* Iterative forloop */
unsigned FibonacciItreativeFor(unsigned N)
{
  if(N == 0) return 0;
  if(N == 1) return 1;
  unsigned fib0 = 0;
  unsigned fib1 = 1;
  unsigned tmp  = fib1;
  for(unsigned i = 2; i < N; ++i)
  {
    tmp  = fib1;
    fib1 += fib0;
    fib0 = tmp;
  }
  return fib0 + fib1;
}

/* Iterative while */
unsigned FibonacciItreativeWhile(unsigned N)
{
  if(N == 0) return 0;
  if(N == 1) return 1;
  unsigned fib0 = 0;
  unsigned fib1 = 1;
  unsigned tmp  = fib1;
  --N;
  while(--N)
  {
    tmp  = fib1;
    fib1 += fib0;
    fib0 = tmp;
  }
  return fib0 + fib1;
}

/* Print Vector, only works for classes with 
  std::os& opeartor<<(std::ostream& os_, const class& classname_) 
  overload 
*/
template<typename T>
void PrintVector(const std::vector<T>& vec_)
{
  for(const auto& elem :vec_) 
  {
    std::cout << elem << " ";
  }
  std::cout << std::endl;
}

int main()
{
  std::cout << zg::TFibonacci<0>::val  << " " << FibonacciRecursive(0)  << " " << FibonacciItreativeWhile(0) << " " << FibonacciItreativeFor(0) << std::endl;
	std::cout << zg::TFibonacci<1>::val  << " " << FibonacciRecursive(1)  << " " << FibonacciItreativeWhile(1) << " " << FibonacciItreativeFor(1) << std::endl;
  std::cout << zg::TFibonacci<2>::val  << " " << FibonacciRecursive(2)  << " " << FibonacciItreativeWhile(2) << " " << FibonacciItreativeFor(2) << std::endl;	
  std::cout << zg::TFibonacci<3>::val  << " " << FibonacciRecursive(3)  << " " << FibonacciItreativeWhile(3) << " " << FibonacciItreativeFor(3) << std::endl;	
  std::cout << zg::TFibonacci<10>::val << " " << FibonacciRecursive(10) << " " << FibonacciItreativeWhile(10)<< " " << FibonacciItreativeFor(10) << std::endl;

  auto get = zg::GetFibonacciSequence(10);
  PrintVector(get);
}

#endif
