//
// Circular linked list
//
#include "CircularLinkedList.h"

int main(int argc, char* argv[])
{
	CircularLinkedList<int> list;
	list.Add(1).Add(2).Add(3);
	std::cout << "The list is:\n" << list << std::endl;

	CircularLinkedList<int> list2;
	list.Clone(list2);
	std::cout << "list2 is:\n" << list2 << std::endl;

	CircularLinkedList<int> list3(list2);
	std::cout << "list3 is:\n" << list3 << std::endl;

	CircularLinkedList<int> list4;
	list4.Add(8);
	list4 = list;
	std::cout << "list4 is:\n" << list4 << std::endl;

	return 0;
}
