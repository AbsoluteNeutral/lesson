#include<stdio.h>



// loop
int fibonacci_loop(int n){
  if(n <= 0)
    return 0;
  else if(n == 1)
    return 1;
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

// recursive
int fibonacci(int n){
  if(n <= 0)
    return 0;
  else if(n == 1)
    return 1;
  return fibonacci(n-2) + fibonacci(n-1);
}

// meta programming
template<int n> 
struct fib
{
    static constexpr int value = fib<n-2>::value + fib<n-1>::value;
};
template<> 
struct fib<0>
{
    static constexpr int value = 0;
};
template<> 
struct fib<1>
{
    static constexpr int value = 1;
};

// main
int main(){
  printf("fiA: %d\n", fibArray[10]);
  printf("fiL: %d\n", fibonacci_loop(10));
  printf("fiR: %d\n", fibonacci(10));
  printf("fiM: %d\n", fib<10>::value);
  //printf("fib: %d\n", fib<-1>::value); // compile error control
  return 0;  
}
