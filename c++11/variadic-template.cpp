// @file variadic-template.cpp
// Variadic template
#include <iostream>

void Print() {
  std::cout << "Finished printing." << std::endl;
}

template <typename T, typename... Types>
void Print(const T& first, const Types&... args) {
  std::cout << first << std::endl;
  Print(args...);
}

int main(int, char**) {
  Print(1, 3.14, 'a', "String");
  return 0;
}