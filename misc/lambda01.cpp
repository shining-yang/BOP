//

#include <iostream>

void print(int a)
{
	std::cout << "Value: " << a << std::endl;
}

void foo()
{
	int val = 1;

	//auto const_val_lambda = [=]() { val = 2; };
	//const_val_lambda();
	print(val);

	auto mutable_val_lambda = [=]() mutable { val = 3; };
	mutable_val_lambda();
	print(val);

	auto const_ref_lambda = [&] { val = 4; };
	const_ref_lambda();
	print(val);

	auto const_param_lambda = [&](int v) { v = 5; };
	const_param_lambda(val);
	print(val);
}

int main()
{
	foo();
}

