#include<iostream>
#include<utility>
#include "string.h"

int main(){
  ddd::string str1{"ABC"};
  ddd::string str2{"DEF"};
  ddd::string str3{str1};
  
  std::cout << "ctor:" << str1 << std::endl;
  std::cout << "cpyctor:" << str3 << std::endl;
  
  ddd::string str4{std::move(str3)};
  std::cout << "mctor:" << str3 << std::endl;
  std::cout << "mctor:" << str4 << std::endl;
  
  str3 = str1;
  std::cout << "=:" << str3 << std::endl;
  str3 += str2;
  std::cout << "+=:" << str3 << std::endl;
  str3.push_back('1');
  std::cout << "push_back:" << str3 << std::endl;
  std::cout << "size:" << str3.size() << std::endl;
  std::cout << "length:" << str3.length() << std::endl;
  
  std::cout << "[0][1]:" << str3[0] << str3[1] << std::endl;
  std::cout << "at2:" << str3.at(2) << std::endl;
  std::cout << "front:" << str3.front() << std::endl;
  std::cout << "back:" << str3.back() << std::endl;

  str3.clear();
  std::cout << "clear:" << str3 << std::endl;
  str3.append(str1, 1, 1);
  std::cout << "append:" << str3 << std::endl;
  str3.append(str2, 0, 3);
  std::cout << "append:" << str3 << std::endl;
  std::cout << "size:" << str3.size() << std::endl;

  
  return 0;
}