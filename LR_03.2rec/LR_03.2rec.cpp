#include <iostream>
#include <Windows.h>
using namespace std;

struct Elem
{
    Elem* link;
    int info;
};
typedef int Info;

void enqueue(Elem*& first, Elem*& last, Info value)
{
    Elem* tmp = new Elem;  //1
    tmp->info = value;    //2
    tmp->link = NULL;   //3
    if (last != NULL)   //4
        last->link = tmp;  //5
    last = tmp;     //6
    if (first == NULL)  //7
        first = tmp;   //8
}

Info dequeue(Elem*& first, Elem*& last)
{
    Elem* tmp = first->link; //1
    Info value = first->info; //2
    delete first; //3
    first = tmp; //4
    if (first == NULL) //5
        last = NULL; //6
    return value;   //7
}

void reverseList(Elem*& first, Elem*& last, Elem* current = NULL, Elem* prev = NULL)
{
    if (current == NULL) {
        if (first == NULL) return;
        current = first;
        last = first;
    }

    Elem* next = current->link;
    current->link = prev;

    if (next == NULL) {
        first = current;
        return;
    }

    reverseList(first, last, next, current);
}

void printList(Elem* first)
{
    if (first == NULL) {
        cout << endl;
        return;
    }
    cout << first->info << " ";
    printList(first->link);
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Elem* first = NULL, * last = NULL;

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