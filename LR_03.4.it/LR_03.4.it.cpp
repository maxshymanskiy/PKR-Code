#include <iostream>
#include <Windows.h>
using namespace std;

typedef int Info;
struct Elem {
    Elem* link;
    Info info;
};

void insert(Elem*& L, Info value) {
    Elem* tmp = new Elem;
    tmp->info = value;
    if (L != NULL) {
        Elem* T = L;
        while (T->link != L)
            T = T->link;
        T->link = tmp;
    }
    else {
        L = tmp;
    }
    tmp->link = L;  // Новий елемент посилається на початок списку, утворюючи кільце
}

void insertBeforeV1(Elem*& head, Info V1, Info V2) {
    if (!head) return;

    Elem* last = head;
    while (last->link != head)  // Шукаємо останній елемент (який посилається на head)
        last = last->link;

    Elem* current = head;
    Elem* prev = last;
    bool isFirst = true;

    while (isFirst || current != head) {
        isFirst = false;

        if (current->info == V1) {
            Elem* newNode = new Elem;
            newNode->info = V2;
            newNode->link = current;
            prev->link = newNode;

            if (current == head) {
                head = newNode;
                last->link = head;
            }

            prev = newNode;
            current = current->link;  // переходимо далі, щоб уникнути повторної вставки перед тією ж 3
        }
        else {
            prev = current;
            current = current->link;
        }
    }
}



void remove(Elem*& L) {
    if (L == NULL) return;

    Elem* first = L;
    Elem* current = L->link;

    while (current != first) { // Видаляємо всі елементи, поки не повернемося до початку
        Elem* temp = current;
        current = current->link;
        delete temp;
    }

    delete first;
    L = NULL;
}

void display(Elem* L) {
    if (L == NULL) {
        cout << "Список порожній" << endl;
        return;
    }

    Elem* tmp = L;
    do {
        cout << tmp->info << " ";
        tmp = tmp->link;
    } while (tmp != L);     // Цикл продовжується, поки не повернемося до початку
    cout << endl;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

    Elem* L = NULL;

    insert(L, 5);
    insert(L, 2);
    insert(L, 6);
    insert(L, 3);
    insert(L, 5);
    insert(L, 3);
    insert(L, 2);
    insert(L, 4);
    insert(L, 1);
    insert(L, 5);

    cout << "Початковий список: ";
    display(L);

    insertBeforeV1(L, 3, 9);

    cout << "Після вставки 9 перед кожним 3: ";
    display(L);

    remove(L);

    cout << "Список після видалення: ";
    display(L);

    return 0;
}
