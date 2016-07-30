// @file smart-ptr.cpp
// shared_ptr<>, unique_ptr<>, weak_ptr<>
#include <iostream>
#include <iomanip>
#include <string>
#include <memory>

#define SUCCEEDED(rc) (rc == 0)

int RunCaseConstruct() {
  //std::shared_ptr<std::string> sp = new std::string("Hello"); // ERROR, implicit conversion
  std::shared_ptr<std::string> sp1(new std::string("Hello"));
  std::shared_ptr<std::string> sp2 {sp1};
  std::shared_ptr<std::string> sp3 = std::make_shared<std::string>("C++11");
  return 0;
}

int RunCaseDeleter() {
  //----------------------------------------------------------------------------
  std::shared_ptr<std::string> sp1 { new std::string("lambda-deleter"),
    [](std::string* ptr){
      // std::cout << "shared_ptr<> gets destroyed" << std::endl;
      delete ptr;
    }
  };

  //----------------------------------------------------------------------------
  // Creating a shared_ptr for an array is possible but wrong
  //
  // If you use new[] to create an array of objects you have to define your
  // own deleter. You can do that by passing a function, function object,
  // or lambda, which calls delete[] for the passed ordinary pointer.
  std::shared_ptr<int> sp2 { new int[5] { 1, 3, 5, 7, 9 },
    [](int* p) {
      delete[] p;
    }
  };

  //----------------------------------------------------------------------------
  std::unique_ptr<int[]> up(new int[10]); // OK
  //std::shared_ptr<int[]> sp(new int[10]); // ERROR: does not compile

  //----------------------------------------------------------------------------
  // For unique_ptrs, you have to specify a second template argument to
  // specify your own deleter
  std::unique_ptr<double, void (*)(double*)> up2 { new double(3.1415),
    [](double* ptr) {
      delete ptr;
    }
  };

  return 0;
}

int PrintRunningResult(int result, const std::string& running_case) {
  std::cout << "[ " << std::setw(8)
    << (SUCCEEDED(result) ? "OK" : "Failure") << " ]  "
    << running_case << std::endl;
  return 0;
}

int main() {
  PrintRunningResult(RunCaseConstruct(), "RunCaseConstruct");
  PrintRunningResult(RunCaseDeleter(), "RunCaseDeleter");
  return 0;
}
