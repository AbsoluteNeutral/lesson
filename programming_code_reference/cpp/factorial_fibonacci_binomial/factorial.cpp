#include "factorial.h"

namespace ddd{
   // factorial loop
  int Factorial(int n)
  {
    int value = 1;
    while(n)
      value *= n--;
    return value;
  }
  
  // factorial for loop
  int FactorialF(int n)
  {
    int value = 1;
    for(int i = n; i > 1; --i) {
      value *= n;
      --n;
    }
    return value;
  }

  // factorial recursive
  int FactorialR(int n)
  {
    if(n <= 1) return 1;
    return FactorialR(n-1) * n;
  }

  // Binomial nCr term
  int nCr(int n, int r)
  {
    return Factorial(n) / (Factorial(n-r) * Factorial(r));
  }

} //namespace ddd
