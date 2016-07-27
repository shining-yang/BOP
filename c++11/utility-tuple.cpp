// @file utility-tuple.cpp
// Sample usage on std::tuple.
// Using template metaprogramming, partial specialization.
#include <iostream>
#include <tuple>
#include <string>

template <int IDX, int MAX, typename... Args>
struct PrintTuple {
  static void Print(std::ostream& os, const std::tuple<Args...>& t) {
    os << std::get<IDX>(t) << ((IDX + 1 == MAX) ? "" : ", ");
    PrintTuple<IDX + 1, MAX, Args...>::Print(os, t);
  }
};

template <int MAX, typename... Args>
struct PrintTuple<MAX, MAX, Args...> {
  static void Print(std::ostream& os, const std::tuple<Args...>& t) {
  }
};

template <typename... Args>
std::ostream& operator<<(std::ostream& os, const std::tuple<Args...>& t) {
  std::cout << "[ ";
  PrintTuple<0, sizeof...(Args), Args...>::Print(os, t);
  std::cout << " ]";
  return os;
}

int main(int, char**) {
  auto t = std::make_tuple(3.14f, std::string(R"(RAW-STRING)"));
  std::cout << "t: " << t << std::endl;
  return 0;
}