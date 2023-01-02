#include "fibonacci.h"

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
