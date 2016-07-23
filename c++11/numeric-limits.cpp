// @file numeric-limits.cpp
// Examine limits of some numeric values
#include <iostream>
#include <limits>

int main(int argc, char** argv) {
  std::cout << std::numeric_limits<short>::max() << std::endl;
  std::cout << std::numeric_limits<int>::max() << std::endl;
  std::cout << std::numeric_limits<int64_t>::max() << std::endl;
  std::cout << std::numeric_limits<double>::max() << std::endl;
  return 0;
}
