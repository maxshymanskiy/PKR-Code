#include <iostream>
#include <Windows.h>
using namespace std;

typedef int Info;
struct Elem {
    Elem* link;
    Info info;
};

// Рекурсивна вставка в кінець кільцевого списку
void insert(Elem*& L, Info value, Elem* first = nullptr, Elem* current = nullptr) {
    if (L == nullptr) {
        Elem* tmp = new Elem;
        tmp->info = value;
        tmp->link = tmp;  // Кільцевий список: єдиний елемент посилається сам на себе
        L = tmp;
        return;
    }

    if (first == nullptr) {
        first = L;
        current = L;
    }

    // Умова виходу: якщо наступний елемент - перший (кільце замикається)
    if (current->link == first) {  // Перевірка кільцевої структури
        Elem* tmp = new Elem;
        tmp->info = value;
        tmp->link = first;  // Новий елемент посилається на початок
        current->link = tmp;
        return;
    }

    insert(L, value, first, current->link);
}

// Рекурсивний пошук останнього елемента (заміна while)
Elem* findLastRecursive(Elem* start, Elem* current) {
    if (current->link == start) return current;  // Знайшли останній (посилається на start)
    return findLastRecursive(start, current->link);
}

// Рекурсивна вставка перед заданим значенням
void insertBeforeV1(Elem*& head, Info V1, Info V2, Elem* current = nullptr,
    Elem* prev = nullptr, Elem* first = nullptr) {
    if (head == nullptr) return;

    if (current == nullptr) {
        current = head;
        prev = findLastRecursive(head, head);  // Рекурсивно знаходимо останній елемент
        first = head;
    }

    if (current->info == V1) {
        Elem* newNode = new Elem;
        newNode->info = V2;
        newNode->link = current;
        prev->link = newNode;

        if (current == head) {
            head = newNode;
            // Рекурсивно оновлюємо посилання останнього елемента
            Elem* last = findLastRecursive(head, head);
            last->link = head;  // Замикаємо кільце
        }

        insertBeforeV1(head, V1, V2, current->link, newNode, first);
    }
    else {
        // Умова виходу: повернулись на початок
        if (current->link == first) return;  // Перевірка кільцевої структури
        insertBeforeV1(head, V1, V2, current->link, current, first);
    }
}

// Рекурсивне видалення кільцевого списку
void remove(Elem*& L, Elem* current = nullptr, Elem* first = nullptr) {
    if (L == nullptr) return;

    if (current == nullptr) {
        first = L;
        current = L->link;
    }
    else if (current == first) {  // Умова виходу: обійшли все кільце
        delete first;
        L = nullptr;
        return;
    }

    Elem* next = current->link;
    delete current;
    remove(L, next, first);
}

// Рекурсивний вивід кільцевого списку
void display(Elem* L, Elem* current = nullptr, bool firstPass = true) {
    if (L == nullptr) {
        cout << "Список порожній" << endl;
        return;
    }

    if (current == nullptr) {
        current = L;
    }

    cout << current->info << " ";

    // Умова виходу: наступний елемент - початок (не перший прохід)
    if (current->link == L && !firstPass) {  // Перевірка кільцевої структури
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