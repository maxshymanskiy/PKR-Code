#include <iostream>
#include <fstream>
#include <string>
using namespace std;

typedef string Info;
struct Elem {
    Elem* link;
    Info info;
};

Elem* push(Elem* top, Info value) {
    Elem* tmp = new Elem;
    tmp->info = value;
    tmp->link = top;
    top = tmp;
    return top;
}

Elem* pop(Elem* top, Info& value) {
    if (top == nullptr) {
        cerr << "The stack is empty" << endl;
        return nullptr;
    }
    Elem* tmp = top->link;
    Info value = top->info;
    delete top;
    return tmp;
}

Elem* createStackFromFile(string filename) {
    Elem* top = nullptr;
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Unable to open file " << filename << endl;
        exit(1);
    }
    string word;
    while (inFile >> word) {
        top = push(top, word);
    }
    inFile.close();
    return top;
}

void printStack(Elem* top) {
    if (top == nullptr) {
        cout << "The stack is empty" << endl;
        return;
    }
    Elem* tmp = top;
    while (tmp != nullptr) {
        cout << tmp->info << " ";
        tmp = tmp->link;
    }
    cout << endl;
}

int stackLength(Elem* top) {
    int k = 0;
    while (top != NULL)
    {
        k++;
        top = top->link;
    }
    return k;
}

void splitStack(Elem** original, int half, Elem** stack1, Elem** stack2) {
    for (int i = 0; i < half; ++i) {
        Info value;
        *original = pop(*original, value);
        *stack1 = push(*stack1, value);
    }
    for (int i = 0; i < half; ++i) {
        Info value;
        *original = pop(*original, value);
        *stack2 = push(*stack2, value);
    }
}

Elem* duplicateStack(Elem* original) {
    Elem* duplicate = nullptr;
    Elem* tmp = original;

    Elem* tempStack = nullptr;
    while (tmp != nullptr) {
        tempStack = push(tempStack, tmp->info);
        tmp = tmp->link;
    }

    while (tempStack != nullptr) {
        Info value;
        tempStack = pop(tempStack, value);
        duplicate = push(duplicate, value);
    }

    return duplicate;
}

int main() {
    Elem* originalStack = createStackFromFile("input.txt");
    cout << "Original stack: ";
    printStack(originalStack);

    int count = stackLength(originalStack);
	cout << "Stack length: " << count << endl;
	if (count == 0) {
		cout << "The stack is empty" << endl;
		return 0;
	}

    if (count % 2 == 0) {
        int half = count / 2;
        Elem* stack1 = nullptr;
        Elem* stack2 = nullptr;
        splitStack(&originalStack, half, &stack1, &stack2);
        cout << "Stack 1: ";
        printStack(stack1);
        cout << "Stack 2: ";
        printStack(stack2);
    }
    else {
        Elem* duplicate = duplicateStack(originalStack);
        cout << "Original stack: ";
        printStack(originalStack);
        cout << "Duplicate stack: ";
        printStack(duplicate);
    }

    return 0;
}