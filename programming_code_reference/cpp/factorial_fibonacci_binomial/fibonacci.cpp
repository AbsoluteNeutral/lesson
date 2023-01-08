#include "fibonacci.h"

namespace ddd {
  // loop (do while)
  int fibonacciLoop(int n)
  {
    if(n == 0) return 0;
    if(n == 1) return 1;
    int fib0  = 0;
    int fib1  = 1;
    int fibn  = fib1;
    --n;
    do {
      fibn += fib0;
      fib0 = fib1;
      fib1 = fibn;
    } while(--n);
    return fibn;
  }
  
  // loop (for)
  int fibonacciForLoop(int n)
  {
    if(n <= 0) return 0;
    if(n == 1) return 1;
    int term0 = 0;
    int term1 = 1;
    int termn = 0;
    for(int i=1; i<n; ++i){
      termn = term0 + term1;
      term0 = term1;
      term1 = termn;
    }
    return termn;
  }
  
  // loop (while)
  int fibonacciWhile(int n)
  {
    if(n <= 0) return 0;
    if(n == 1) return 1;
    int fib0 = 0;
    int fib1 = 1;
    int tmp  = fib1;
    --n;
    while(--n)
    {
      tmp  = fib1;
      fib1 += fib0;
      fib0 = tmp;
    }
    return fib0 + fib1;
  }


  // recursive
  int fibonacciR(int n)
  {
    if(n == 0) return 0;
    if(n == 1) return 1;
    return fibonacciR(n-2) + fibonacciR(n-1);
  }

}// namespace ddd
