#include <iostream>
#include <Windows.h>
using namespace std;

typedef int Info;
struct Elem {
    Elem* link;
    Info info;
};

// Рекурсивна вставка в кінець списку
void insert(Elem*& L, Info value, Elem* first = nullptr, Elem* current = nullptr) {
    if (L == nullptr) {
        Elem* tmp = new Elem;
        tmp->info = value;
        tmp->link = tmp;
        L = tmp;
        return;
    }

    if (first == nullptr) {
        first = L;
        current = L;
    }

    if (current->link == first) {
        Elem* tmp = new Elem;
        tmp->info = value;
        tmp->link = first;
        current->link = tmp;
        return;
    }

    insert(L, value, first, current->link);
}

// Рекурсивна вставка перед заданим значенням
void insertBeforeV1(Elem*& head, Info V1, Info V2, Elem* current = nullptr,
    Elem* prev = nullptr, Elem* first = nullptr) {
    if (head == nullptr) return;

    if (current == nullptr) {
        current = head;
        prev = head;
        // Знаходимо останній елемент
        while (prev->link != head) {
            prev = prev->link;
        }
        first = head;
    }

    if (current->info == V1) {
        Elem* newNode = new Elem;
        newNode->info = V2;
        newNode->link = current;
        prev->link = newNode;

        if (current == head) {
            head = newNode;
            // Оновлюємо посилання останнього елемента
            Elem* last = head;
            while (last->link != current) {
                last = last->link;
            }
            last->link = head;
        }

        insertBeforeV1(head, V1, V2, current->link, newNode, first);
    }
    else {
        if (current->link == first) return;
        insertBeforeV1(head, V1, V2, current->link, current, first);
    }
}

// Рекурсивне видалення списку
void remove(Elem*& L, Elem* current = nullptr, Elem* first = nullptr) {
    if (L == nullptr) return;

    if (current == nullptr) {
        first = L;
        current = L->link;
    }
    else if (current == first) {
        delete first;
        L = nullptr;
        return;
    }

    Elem* next = current->link;
    delete current;
    remove(L, next, first);
}

// Рекурсивний вивід списку
void display(Elem* L, Elem* current = nullptr, bool firstPass = true) {
    if (L == nullptr) {
        cout << "Список порожній" << endl;
        return;
    }

    if (current == nullptr) {
        current = L;
    }

    cout << current->info << " ";

    if (current->link == L && !firstPass) {
        cout << endl;
        return;
    }

    display(L, current->link, false);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Elem* L = nullptr;

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