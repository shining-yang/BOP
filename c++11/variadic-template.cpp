// @file variadic-template.cpp
// Variadic template
#include <iostream>

#if 0
void Print() {
  std::cout << "Called Print()" << std::endl;
}
#else
template <typename T>
void Print(const T& arg) {
  std::cout << arg << std::endl;
}
#endif

template <typename T, typename... Types>
void Print(const T& first, const Types&... args) {
  std::cout << first << " [ " << sizeof...(Types) << " ]" << std::endl;
  Print(args...);
}

int main(int, char**) {
  Print(1, 3.14, 'a', "String");
  return 0;
}
