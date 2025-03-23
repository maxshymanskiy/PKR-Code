#include <iostream>
#include <Windows.h>

using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;
};

Node* createNode(int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->prev = nullptr;
    newNode->next = nullptr;
    return newNode;
}

void append(Node*& head, int value) {
    if (head == nullptr) {
        head = createNode(value);
    }
    else if (head->next == nullptr) {
        Node* newNode = createNode(value);
        head->next = newNode;
        newNode->prev = head;
    }
    else {
        append(head->next, value);
    }
}

void printList(Node* head) {
    if (head == nullptr) {
        cout << endl;
        return;
    }
    cout << head->data << " ";
    printList(head->next);
}

int countNegativeElements(Node* head) {
    if (head == nullptr) {
        return 0;
    }
    return (head->data < 0 ? 1 : 0) + countNegativeElements(head->next);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Node* head = nullptr;

    append(head, 10);
    append(head, -20);
    append(head, 30);
    append(head, -40);
    append(head, -15);
    append(head, 25);

    cout << "Список: ";
    printList(head);

    int count = countNegativeElements(head);
    cout << "Кількість елементів з від'ємними значеннями: " << count << endl;

    return 0;
}