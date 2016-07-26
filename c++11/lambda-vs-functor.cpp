// @file lambda-vs-functor.cpp
// Lambda function vs. functor
#include <iostream>

class SimpleFunctor {
public:
  SimpleFunctor() = default;
  SimpleFunctor(int n) : num_(n) {}
  ~SimpleFunctor() = default;

public:
  int operator()() {
    return num_ * num_;
  }

  int operator()(int times) {
    return num_ * times;
  }

private:
  int num_ = 0;
};

int main() {
  SimpleFunctor sf(2);
  std::cout << "Functor> no param: " << sf()
            << ", with param: " << sf(3)
            << std::endl;

  int n = 2;
  auto lambda0 = [=]() { return n * n; };
  auto lambda1 = [=](int times) -> int { return n * times; };
  auto lambda2 = [&](int times) -> int { return n * times; };

  n = 100;
  std::cout << "Lambda> no param: " << lambda0()
          << ", with param: " << lambda1(3)
          << ", caputure ref: " << lambda2(3)
          << std::endl;

  return 0;
}

