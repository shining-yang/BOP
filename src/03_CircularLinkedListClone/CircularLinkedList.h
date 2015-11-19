//
// Singular & circular linked list
//

#pragma once
#include <iostream>

template<typename T>
class CircularLinkedList {
public:
	struct Node {
		T data;
		Node* next;
		Node() {}
		Node(const T& d) : data(d), next(NULL) {}
	};

private:
	Node* head = NULL;
	Node* tail = NULL;

public:
	CircularLinkedList(const CircularLinkedList<T>& list) {
		list.Clone(*this);
	}
		
	CircularLinkedList& operator=(const CircularLinkedList<T>& list) {
		if (this != &list) {
			list.Clone(*this);
		}
		return *this;
	}

public:
	CircularLinkedList() {}
	~CircularLinkedList() {
		Clear();
	}

	void Clear() {
		if (tail) {
			tail->next = NULL;

			Node* p = head;
			while (p) {
				Node* q = p->next;
				delete(p);
				p = q;
			}

			head = tail = NULL;
		}
	}

	CircularLinkedList<T>& Add(const T& data) {
		Node* p = new Node(data);
		if (tail) {
			tail->next = p;
		} else {
			head = p;
		}
		tail = p;
		tail->next = head;
		return *this;
	}

	void Print(std::ostream& os) const {
		for (Node* p = head; p; p = p->next) {
			os << p->data << ", ";
			if (p == tail) {
				break;
			}
		}
	}

	void Clone(CircularLinkedList<T>& list) const {
		list.Clear();
		for (Node* p = head; p; p = p->next) {
			list.Add(p->data);
			if (p == tail) {
				break;
			}
		}
	}

	template<typename Ty>
	friend std::ostream& operator<<(std::ostream& os, const CircularLinkedList<Ty>& list);
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const CircularLinkedList<T>& l)
{
	l.Print(os);
	return os;
}
