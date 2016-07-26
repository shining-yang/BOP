// @file template-constructor.cpp
//
// Template constructors are usually provided to enable implicit type
// conversions when objects are copied. Note that a template constructor
// does not suppress the implicit declaration of the copy constructor.
// If the type matches exactly, the implicit copy constructor is generated
// and called.
#include <iostream>
#include <bitset>

template <typename T>
class MyClass {
public:
  MyClass() {
    std::cout << "Default constructor" << std::endl;
  }

  MyClass(const MyClass<T>& obj) {
    std::cout << "Copy constructor" << std::endl;
  }

  template <typename U>
  MyClass(const MyClass<U>& obj) {
    std::cout << "MyClass(const MyClass<U>&)" << std::endl;
  }
};

int main() {
  MyClass<int> mi;
  MyClass<int> mi2(mi);
  MyClass<double> md(mi);
  MyClass<std::bitset<32>> mbs(mi2);
  return 0;
}

