#ifndef FACTORIAL_H_
#define FACTORIAL_H_
#include <vector>

namespace ddd{
  int Factorial(int n);   // factorial while loop
  int FactorialF(int n);  // factorial for loop
  int FactorialR(int n);  // factorial recursive
  int nCr(int n, int r);  // Binomial nCr term
  
  // meta factorial
  template<int n>
  struct TFactorial
  {
    constexpr static int val = TFactorial<n-1>::val * n;
  };
  template<>
  struct TFactorial<1>
  {
    constexpr static int val = 1;
  };
  template<>
  struct TFactorial<0>
  {
    constexpr static int val = 1;
  };
  
  // meta ninomial nCr term
  template<int N, int R>
  struct TnCr
  {
    constexpr static int val = TFactorial<N>::val / (TFactorial<N-R>::val * TFactorial<R>::val);
  };
  
  template<typename T = int>
  std::vector<T> GetBinomialSequence(int n)
  {
    std::vector<T> tmp;
    tmp.reserve(n + 1);
    tmp.push_back(T(1));
    
    for (int i = 0; i < n; ++i)
      tmp.push_back(T(1));
    
    //Loop is for N > 1, 3 term or more
    for (int i = 1; i < n; ++i)
    {
      T getprev = tmp[0];
      for (int j = 1; j < i + 1; ++j)
      {
        T value = getprev + tmp[j];
        getprev = tmp[j];
        tmp[j] = value;
      }
    }
    return tmp;
    
    ////__________ Brute force
    //std::vector<T> tmp;
    //tmp.push_back(T(1));
    //
    //for (int j = 0; j < n; ++j)
    //{
    //	std::vector<T> aatmp;
    //	for (auto i = 1; i < tmp.size(); ++i)
    //	{
    //		aatmp.push_back(tmp[i - 1] + tmp[i]);
    //	}
    //	aatmp.insert(aatmp.begin(), 1.0f);
    //	aatmp.push_back(T(1));
    //	tmp = aatmp;
    //}
    //return tmp;
  }
  
} //namespace ddd

#endif // FACTORIAL_H_
