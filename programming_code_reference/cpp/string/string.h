#ifndef DDD_STRING_H_
#define DDD_STRING_H_

#include <iostream>

namespace ddd {
  // function
  size_t strlen	(const char* source);
  void strcpy		(char* dest, const char* source);
  void strncpy	(char* dest, const char* source, size_t num);
    
  // class
  class string {
  public:
    string  ()                  noexcept; // default ctor
    string  (const char* s)     throw();  // ctor
    string  (const string& rhs) throw();  // cpy ctor
    string  (string&& rhs)      noexcept; // move ctor
    string& operator=(const char* s);     // cpy operator
    string& operator=(const string& rhs); // cpy operator
    string& operator=(string&& rhs);      // move operator
    ~string ();                           // dtor
  
    // element access
    const char& operator[](size_t pos) const;
    char& operator[]      (size_t pos);
    char&				at	      (size_t pos);
		const char& at	      (size_t pos) const;
    char&				back	    ();
		const char& back	    () const;
     char& 			front     ();
		const char& front     () const;
    
    // operator overload
    string& operator+=	  (const char* source);
    string& operator+=	  (const string& rhs);
    
    
    // modifiers
    string& append (const char* s);
    string& append (const string& str);
    string& append (const string& str, size_t subpos, size_t sublen);
    
    const char* c_str () const;
    void        clear ();
    void        push_back(char c);
    size_t      size  () const;
    size_t      length() const;
    
    friend std::ostream& operator<<(std::ostream& os, const string& string_);
  private:
    char* buffer;
    size_t sz;
  };
}

#endif // DDD_STRING_H_