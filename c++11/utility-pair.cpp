// @file utility-pair.cpp
// std utility - pair
#include <iostream>
#include <utility>

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
  os << "[" << p.first << ", " << std::get<1>(p) << "]" << std::endl;
  return os;
}

// std::pair copy constructor allows implicit type conversions
// Since C++11, a pair<> using a type that has only a nonconstant copy
// constructor will no longer compile
// {{
class A {
public:
  A() { std::cout << "A()" << std::endl; }
};

class B {
public:
  B() { std::cout << "B()" << std::endl; }
  B(const A&) { std::cout << "B(const A&)" << std::endl; }
};

void Foo(const std::pair<int, B>& p) {
}

void Bar() {
  std::pair<int, A> pa;
  Foo(pa);
};
// }}

int main() {
  std::cout << std::make_pair(3.14f, std::string("Hi"));

  std::pair<int, float> p1 { 1, 2.7172 };

  int arr[std::tuple_size<std::pair<int, float>>::value];

  std::cout << "element number of arr: "
            << sizeof(arr) / sizeof(arr[0])
            << std::endl;

  std::cout << "std::tuple_element<0> size: "
            << sizeof(std::tuple_element<0, std::pair<double, int>>::type)
            << std::endl;

  Bar();
  return 0;
}
