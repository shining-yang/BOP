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
  std::shared_ptr<std::string> sp { new std::string("lambda-deleter"),
    [](std::string* ptr){
      std::cout << "shared_ptr<> gets destroyed" << std::endl;
      delete ptr;
    }};
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
