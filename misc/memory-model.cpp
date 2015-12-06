//
//
#include <iostream>
#include <thread>
#include <atomic>

std::atomic_int a { 0 };
std::atomic<int> b { 0 };

void update(int)
{
	int i = 1;
	a = i;
	b = 2;
}

void show(int)
{
	for (int i = 0; i < 10; i++)
	std::cout << "a = " << a << ", b = " << b << std::endl;
}

int main(int argc, char* argv[])
{
	std::thread t1(update, 0);
	std::thread t2(show, 0);
	t1.join();
	t2.join();
	std::cout << "Finally, a = " << a << ", b = " << b << std::endl;
	return 0;
}
