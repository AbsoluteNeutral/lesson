#include "string.h"
#include<cstring>

namespace ddd {
  // function
  size_t strlen(const char* s){
    const char* start = s;
    while(*start){
      ++start;
    }
    return start-s;
  }
  void strcpy(char* dest, const char* s){
    char* cpy = dest;
    const char* start = s;
    while(*s){
      *cpy = *s;
      ++cpy;
      ++s;
    }
    *cpy = *s;
  }
  
  void strncpy(char* dest, const char* s, size_t num){
    char* 			cpy 	= dest;
    const char* begin = s;
    while(num--)
    {
      *cpy = *begin;
      ++begin;
      ++cpy;
    }
  }
    
  // class
  string::string() noexcept
    :buffer(nullptr), sz(0)
  {}
    
  string::string(const char* s) throw()
    :buffer(nullptr), sz(0) 
  {
    char* tmp;
    sz = std::strlen(s);
    try {
       tmp = new char[sz + 1];
    } catch(...) {
      sz = 0;
      throw;
    }
    std::strcpy(tmp, s);
    buffer = tmp;
  }
    
  string::string(const string& str) throw()
    :buffer(nullptr), sz(str.sz)
  {
    try {
       buffer = new char[sz + 1];
    } catch(...) {
      sz = 0;
      throw;
    }
    std::strcpy(buffer, str.buffer);
  }
  
  string::string(string&& str) noexcept
    :buffer(str.buffer), sz(str.sz)
  {
    str.buffer = nullptr;
    str.sz = 0;
  }
  
  string& string::operator=(const char* s)
  {
    size_t len = std::strlen(s);
    char* tmp = new char[len + 1];
    std::strcpy(tmp, s);
    delete[] buffer;
    buffer = tmp;
    sz = len;
    return *this;
  }
  
  string& string::operator=(const string& str)
  {
    char* tmp = new char[str.sz + 1];
    std::strcpy(tmp, str.buffer);
    delete[] buffer;
    buffer = tmp;
    sz = str.sz;
    return *this;
  }
  
  string& string::operator=(string&& str)
  {
    delete[] buffer;
    buffer = str.buffer;
    sz = str.sz;
    str.buffer = nullptr;
    str.sz = 0;
    return *this;
  }
  
  string::~string()
  {
    clear();
  }
  
  // element access
  const char& string::operator[](size_t pos) const{
    return buffer[pos];
  }
  char& string::operator[](size_t pos){
    return buffer[pos];
  }
  char& string::at(size_t pos)
  {
    return operator[](pos);
  }
	const char& string::at(size_t pos) const
  { 
    return operator[](pos);
  } 
  char&	string::back()
  {
    return *(buffer + sz - 1);
  }
	const char& string::back() const
  {
    return *(buffer + sz - 1);
  }
  char& string::front()
  {
    return *buffer;
  }
	const char& string::front() const
  {
    return *buffer;
  }  
  
  // operator overload
  
  
  string& string::operator+=(const char* s)
  {
    size_t getsz = std::strlen(s);
    char* tmp = new char[sz + getsz + 1];
    std::strncpy(tmp, buffer, sz);
    std::strcpy(tmp + sz, s);
    delete[] buffer;
    buffer = tmp;
    sz = sz + getsz;
    return *this;
  }
  
  string& string::operator+=(const string& str){
    return operator+=(str.buffer);
  }
  

    
  // member function
  string& string::append(const char* s)
  {
    return operator+=(s);
  }
  string& string::append(const string& str)
  {
    return operator+=(str.buffer);
  }
  string& string::append(const string& str, size_t subpos, size_t sublen)
  {
    char* tmp = new char[sz + sublen + 1];
    std::strncpy(tmp, buffer, sz);
    std::strncpy(tmp + sz, str.buffer + subpos, sublen);

    delete[] buffer;
    buffer = tmp;
    sz = sz + sublen;
    buffer[sz] = '\0';
    return *this;
  }
  

    
  const char* string::c_str() const 
  {
    return buffer;
  }

  void string::clear() 
  {
    delete[] buffer;
    buffer = nullptr;
    sz = 0;
  }
  

    
  void string::push_back(char c)
  {
    char* tmp = new char[sz + 2];
    std::strcpy(tmp, buffer);
    tmp[sz] = c;
    tmp[sz + 1] = '\0';
    
    delete[] buffer;
    buffer = tmp;
    ++sz;
  }

  size_t string::size() const
  {
    return sz; 
  }
  
  size_t string::length() const
  {
    return size();
  }
  
  std::ostream& operator<<(std::ostream& os, const string& str)
  {
    return os << (str.buffer == nullptr ? "" : str.buffer);
  }
  
} // namespace ddd
