#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
using namespace std;

typedef string Info;
struct Elem {
    Elem* link;
    Info info;
};

void enqueue(Elem*& first, Elem*& last, const Info& value) {
    Elem* tmp = new Elem;
    tmp->info = value;
    tmp->link = NULL;
    if (last != NULL)
        last->link = tmp;
    last = tmp;
    if (first == NULL)
        first = tmp;
}

Info dequeue(Elem*& first, Elem*& last) {
    if (first == NULL) {
        cerr << "Помилка: Неможливо видалити елемент з порожньої черги!" << endl;
        return "";
    }
    Elem* tmp = first->link;
    Info value = first->info;
    delete first;
    first = tmp;
    if (first == NULL)
        last = NULL;
    return value;
}

void printQueue(Elem* first) {
    Elem* current = first;
    while (current != NULL) {
        cout << current->info << " ";
        current = current->link;
    }
    cout << endl;
}

bool areQueuesEqual(Elem* first1, Elem* first2) {
    while (first1 != NULL && first2 != NULL) {
        if (first1->info != first2->info)
            return false;
        first1 = first1->link;
        first2 = first2->link;
    }
    return first1 == NULL && first2 == NULL;
}

void destroyQueue(Elem*& first, Elem*& last) {
    while (first != NULL) {
        Elem* tmp = first->link;
        delete first;
        first = tmp;
    }
    last = NULL;
}

void mergeQueues(Elem*& first1, Elem*& last1, Elem*& first2, Elem*& last2, Elem*& first3, Elem*& last3) {
    while (first1 != NULL) {
        enqueue(first3, last3, dequeue(first1, last1));
    }
    while (first2 != NULL) {
        enqueue(first3, last3, dequeue(first2, last2));
    }
}

// Розбиття рядка на слова
void processWords(const string& str, Elem*& queueFirst, Elem*& queueLast) {
    string word;
    for (size_t i = 0; i < str.length(); i++) {
        char ch = str[i];
        if (ch == ' ') {
            if (!word.empty()) {
                enqueue(queueFirst, queueLast, word);
                word.clear();
            }
        }
        else {
            word += ch;
        }
    }
    if (!word.empty()) {
        enqueue(queueFirst, queueLast, word);
    }
}

void processFile(const string& filename, Elem*& evenQueueFirst, Elem*& evenQueueLast, Elem*& oddQueueFirst, Elem*& oddQueueLast) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Не вдалося відкрити файл: " << filename << endl;
        return;
    }

    string line;
    int lineNumber = 1;
    while (getline(file, line)) {
        if (lineNumber % 2 == 0) {
            processWords(line, evenQueueFirst, evenQueueLast);
        }
        else {
            processWords(line, oddQueueFirst, oddQueueLast);
        }
        lineNumber++;
    }
    file.close();
}

void printFileContent(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Не вдалося відкрити файл: " << filename << endl;
        return;
    }

    cout << "===== ВМІСТ ФАЙЛУ =====" << endl;
    string line;
    int lineNumber = 1;
    while (getline(file, line)) {
        cout << lineNumber << ": " << line << endl;
        lineNumber++;
    }
    cout << "=======================" << endl;
    file.close();
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Elem* evenQueueFirst = NULL, * evenQueueLast = NULL;
    Elem* oddQueueFirst = NULL, * oddQueueLast = NULL;
    Elem* mergedQueueFirst = NULL, * mergedQueueLast = NULL;

    const string filename = "input.txt";
    processFile(filename, evenQueueFirst, evenQueueLast, oddQueueFirst, oddQueueLast);

    printFileContent(filename);

    cout << "Черга парних рядків: ";
    printQueue(evenQueueFirst);
    cout << "Черга непарних рядків: ";
    printQueue(oddQueueFirst);

    if (areQueuesEqual(evenQueueFirst, oddQueueFirst)) {
        cout << "Черги однакові. Видаляємо чергу непарних рядків." << endl;
        destroyQueue(oddQueueFirst, oddQueueLast);
    }
    else {
        cout << "Черги різні. Об'єднуємо черги." << endl;
        mergeQueues(evenQueueFirst, evenQueueLast, oddQueueFirst, oddQueueLast, mergedQueueFirst, mergedQueueLast);
        cout << "Об'єднана черга: ";
        printQueue(mergedQueueFirst);
    }

    destroyQueue(evenQueueFirst, evenQueueLast);
    destroyQueue(oddQueueFirst, oddQueueLast);
    destroyQueue(mergedQueueFirst, mergedQueueLast);

    return 0;
}
