#include <iostream>
#include <string>

struct A {
	int i;
	std::string s;
	struct A1 {
		char c;
		float f;
	} a1;
};

A get() {
	return { 1, "struct", { 'a', 3.14f } };
}

void print(const A& a) {
	std::cout << a.i << std::endl
		<< a.s << std::endl
		<< "\t" << a.a1.c << std::endl
		<< "\t" << a.a1.f << std::endl;
}

int main(int argc, char* argv[]) {
	std::cout << "std::string is POD? " << std::is_pod<std::string>::value << std::endl;
	std::cout << "A is POD? " << (std::is_pod<A>::value ? "Yes" : "No") << std::endl;
	A a = { 2, "Hello", { 'c', 2.717f } };
	print(get());
	return 0;
}
