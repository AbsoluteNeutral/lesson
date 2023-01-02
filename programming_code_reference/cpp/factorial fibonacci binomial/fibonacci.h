#ifndef FIBONACCI_H_
#define FIBONACCI_H_

#include <vector>

namespace ddd{
  const int fibsize = 31;
  const int fibArray[fibsize]
  
  /* Templated */
  template<unsigned N>
  struct TFibonacci
  {
    constexpr static unsigned val = TFibonacci<N-2>::val + TFibonacci<N-1>::val;
  };
  template<>
  struct TFibonacci<1>
  {
    constexpr static unsigned val = 1;
  };
  template<>
  struct TFibonacci<0>
  {
    constexpr static unsigned val = 0;
  };
  
  unsigned Fibonacci(unsigned N);
  
  /* Get Sequences */
  //std::vector<int> GetFibonacciSequence(unsigned N, bool startsFrom0_)
  template<typename T = unsigned>
  std::vector<T> GetFibonacciSequence(unsigned N)
  {
    std::vector<T> tmp;
    {
      tmp.reserve(N + 1);       //starts from 0
      tmp.push_back(0);
      if(N == 0) return tmp;
      tmp.push_back(1);
      if(N == 1) return tmp;
      tmp.push_back(1);
      if(N == 2) return tmp;
      
      N -= 2;
      auto e = tmp.end();
      while(N--)
      {
        tmp.push_back( *(e-2) + *(e-1) );
        e = tmp.end();
      }
    }
    return tmp;
  }

} // namespace ddd

#endif //_ZG_FIBONACCI_H
