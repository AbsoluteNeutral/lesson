#include<stdio.h>
#include<iostream>
#include "fibonacci.h"
#include "factorial.h"

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
  // test fibonacci
  printf("fiA: %d\n", ddd::fibonacciArray[10]);
  printf("fidoL: %d\n", ddd::fibonacciLoop(10));
  printf("fiforL: %d\n", ddd::fibonacciForLoop(10));
  printf("fiWL: %d\n", ddd::fibonacciWhile(10));
  printf("fiR: %d\n", ddd::fibonacciR(10));
  printf("fiM: %d\n", ddd::FibonacciM<10>::value);
  
  auto get = ddd::getFibonacciSequence(10);
  PrintVector(get);
  
  //
  printf("Running factorial.cpp...\n\n");

  std::cout << "TFactorial " << "FactorialR "  << "FactorialF" << std::endl;
  std::cout << ddd::TFactorial<0>::val  << " " << ddd::FactorialR(0)  << " " << " " << ddd::FactorialF(0) << std::endl;
	std::cout << ddd::TFactorial<1>::val  << " " << ddd::FactorialR(1)  << " " << " " << ddd::FactorialF(1) << std::endl;
  std::cout << ddd::TFactorial<2>::val  << " " << ddd::FactorialR(2)  << " " << " " << ddd::FactorialF(2) << std::endl;	
  std::cout << ddd::TFactorial<3>::val  << " " << ddd::FactorialR(3)  << " " << " " << ddd::FactorialF(3) << std::endl;	
  std::cout << ddd::TFactorial<10>::val << " " << ddd::FactorialR(10) << " " << " " << ddd::FactorialF(10) << std::endl;
  std::cout << std::endl;

  std::cout << "GetBinomialSequence Test:" << std::endl;
  PrintVector(ddd::GetBinomialSequence(0));
  PrintVector(ddd::GetBinomialSequence(1));
  PrintVector(ddd::GetBinomialSequence(2));
  PrintVector(ddd::GetBinomialSequence(3));
  PrintVector(ddd::GetBinomialSequence(4));
  PrintVector(ddd::GetBinomialSequence(5));
  PrintVector(ddd::GetBinomialSequence(6));
  PrintVector(ddd::GetBinomialSequence(7));
  PrintVector(ddd::GetBinomialSequence(8));
  PrintVector(ddd::GetBinomialSequence(9));
  PrintVector(ddd::GetBinomialSequence(10));
  std::cout << std::endl;
  
  std::cout << "TnCr Test:" << std::endl;
  std::cout << ddd::TnCr<0, 0>::val << std::endl;
  std::cout << ddd::TnCr<1, 0>::val << " " << ddd::TnCr<1, 1>::val << std::endl;
  std::cout << ddd::TnCr<2, 0>::val << " " << ddd::TnCr<2, 1>::val << " " << ddd::TnCr<2, 2>::val << std::endl;
  std::cout << ddd::TnCr<3, 0>::val << " " << ddd::TnCr<3, 1>::val << " " << ddd::TnCr<3, 2>::val << " " << ddd::TnCr<3, 3>::val << std::endl;
  std::cout << ddd::TnCr<4, 0>::val << " " << ddd::TnCr<4, 1>::val << " " << ddd::TnCr<4, 2>::val << " " << ddd::TnCr<4, 3>::val << " " << ddd::TnCr<4, 4>::val << std::endl;
  std::cout << std::endl;
  
  std::cout << "nCr Test:" << std::endl;
  std::cout << ddd::nCr(0, 0) << std::endl;
  std::cout << ddd::nCr(1, 0) << " " << ddd::nCr(1, 1) << std::endl;
  std::cout << ddd::nCr(2, 0) << " " << ddd::nCr(2, 1) << " " << ddd::nCr(2, 2) << std::endl;
  std::cout << ddd::nCr(3, 0) << " " << ddd::nCr(3, 1) << " " << ddd::nCr(3, 2) << " " << ddd::nCr(3, 3) << std::endl;
  std::cout << ddd::nCr(4, 0) << " " << ddd::nCr(4, 1) << " " << ddd::nCr(4, 2) << " " << ddd::nCr(4, 3) << " " << ddd::nCr(4, 4) << std::endl;
}