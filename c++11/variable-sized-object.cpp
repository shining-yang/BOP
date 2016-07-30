// @file variable-sized-object.cpp
// Initialization of variable sized array in C++11. (ubuntu 16.04, g++ 5.4)
#include <iostream>
#include <vector>
#include <string>

int TaskMain(int argc, char* argv[]) {
  std::cout << "TaskMain() argc: " << argc << std::endl;
  for (int i = 0; i < argc; i++) {
    std::cout << "\t> " << argv[i] << std::endl;
  }
  return 0;
}

void TestVaribleSizedObject(const std::vector<std::string>& vec_strings) {
  const char* args[vec_strings.size()] = {};
  int n;
  for (n = 0; n < vec_strings.size(); n++) {
    args[n] = vec_strings[n].c_str();
  }

  int rc = TaskMain(n, const_cast<char**>(args));
  (void)rc;
}

int main()
{
  TestVaribleSizedObject({});
  TestVaribleSizedObject({ "echo", "bash!" });
  TestVaribleSizedObject({ "sonar", "start", "-D", "/dev/tty-4" });
  return 0;
}
