#include <iostream>
#include <windows.h>
using namespace std;

struct Elem
{
	Elem* link;
	int info;
};

typedef int Info;

void enqueue(Elem*& first, Elem*& last, Info value)
{
	Elem* tmp = new Elem; // 1
	tmp->info = value; // 2
	tmp->link = NULL; // 3
	if (last != NULL)
		last->link = tmp; // 4
	last = tmp; // 5
	if (first == NULL)
		first = tmp; // 6
}

Info dequeue(Elem*& first, Elem*& last)
{
	Elem* tmp = first->link; // 1
	Info value = first->info; // 2
	delete first; // 3
	first = tmp; // 4
	if (first == NULL)
		last = NULL; // 5
	return value; // 6
}

void reverseList(Elem*& first, Elem*& last)
{
	Elem* prev = NULL;
	Elem* current = first;
	Elem* next = NULL;

	Elem* newFirst = last;

	while (current != NULL) {
		next = current->link;
		current->link = prev;
		prev = current;
		current = next;
	}
	last = first;
	first = newFirst;
}	

void printList(Elem* first)
{
	Elem* current = first;
	while (current != NULL) {
		cout << current->info << " ";
		current = current->link;
	}
	cout << endl;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Elem* first = NULL,
		* last = NULL;

	for (int i = 1; i <= 10; i++)
		enqueue(first, last, i);

	cout << "Початковий список: ";
	printList(first);

	reverseList(first, last);
	cout << "Реверсований список: ";
	printList(first);

	cout << "Виведення при видаленні: ";
	while (first != NULL)
		cout << dequeue(first, last) << " ";

	return 0;
}