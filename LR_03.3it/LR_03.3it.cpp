#include <iostream>
#include <Windows.h>
using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;
};

Node* createNode(int value) {
    Node* newNode = new Node(); //1
	newNode->data = value; //2
	newNode->prev = nullptr; //3
	newNode->next = nullptr; //4
    return newNode;
}

void append(Node*& head, int value) {
    Node* newNode = createNode(value);
    if (head == nullptr) {
        head = newNode;
    }
    else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
}
void printList(Node* head) {
	Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << std::endl;
}

int countNegativeElements(Node* head) {
    int count = 0;
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data < 0) {
            count++;
        }
        temp = temp->next;
    }
    return count;
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