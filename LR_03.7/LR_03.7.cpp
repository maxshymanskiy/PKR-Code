#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

// Структура для оригінального списку (без колії)
struct Train {
    int trainNumber;    // Номер потягу
    int hours;          // Години прибуття
    int minutes;        // Хвилини прибуття
    Train* next;        // Вказівник на наступний елемент
};

// Структура для фільтрованого списку (з колією)
struct FilteredTrain {
    int trainNumber;
    int hours;
    int minutes;
    int platform;       // Номер колії (додається тільки тут)
    FilteredTrain* next;
};

// Функція для створення вузла оригінального списку
Train* createTrainNode(int trainNumber, int hours, int minutes) {
    Train* newNode = new Train;
    newNode->trainNumber = trainNumber;
    newNode->hours = hours;
    newNode->minutes = minutes;
    newNode->next = nullptr;
    return newNode;
}

// Функція для додавання потягу в кінець оригінального списку
Train* appendTrain(Train* head, int trainNumber, int hours, int minutes) {
    Train* newNode = createTrainNode(trainNumber, hours, minutes);

    if (head == nullptr) {
        return newNode;
    }

    Train* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = newNode;
    return head;
}

// Функція для створення вузла фільтрованого списку
FilteredTrain* createFilteredNode(int trainNumber, int hours, int minutes, int platform) {
    FilteredTrain* newNode = new FilteredTrain;
    newNode->trainNumber = trainNumber;
    newNode->hours = hours;
    newNode->minutes = minutes;
    newNode->platform = platform;
    newNode->next = nullptr;
    return newNode;
}

// Функція для додавання потягу в кінець фільтрованого списку
FilteredTrain* appendFilteredTrain(FilteredTrain* head, int trainNumber, int hours, int minutes, int platform) {
    FilteredTrain* newNode = createFilteredNode(trainNumber, hours, minutes, platform);

    if (head == nullptr) {
        return newNode;
    }

    FilteredTrain* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = newNode;
    return head;
}

// Функція для виведення оригінального списку
void printOriginalList(Train* head) {
    cout << "=== Список всіх потягів ===" << endl;
    cout << "Номер потягу\tЧас прибуття" << endl;

    Train* current = head;
    while (current != nullptr) {
        cout << current->trainNumber << "\t\t"
            << current->hours << ":"
            << (current->minutes < 10 ? "0" : "") << current->minutes << endl;
        current = current->next;
    }
    cout << endl;
}

// Функція для виведення фільтрованого списку
void printFilteredList(FilteredTrain* head) {
    cout << "=== Відфільтрований список потягів ===" << endl;
    cout << "Номер потягу\tЧас прибуття\tНомер колії" << endl;

    FilteredTrain* current = head;
    while (current != nullptr) {
        cout << current->trainNumber << "\t\t"
            << current->hours << ":"
            << (current->minutes < 10 ? "0" : "") << current->minutes
            << "\t\t" << current->platform << endl;
        current = current->next;
    }
    cout << endl;
}

// Функція для перевірки часу в діапазоні
bool isTimeInRange(int hours, int minutes, int startHours, int startMinutes, int endHours, int endMinutes) {
    int totalMinutes = hours * 60 + minutes;
    int startTotal = startHours * 60 + startMinutes;
    int endTotal = endHours * 60 + endMinutes;
    return (totalMinutes >= startTotal) && (totalMinutes <= endTotal);
}

// Функція для фільтрації потягів
FilteredTrain* filterTrains(Train* head, int startHours, int startMinutes, int endHours, int endMinutes) {
    FilteredTrain* filteredList = nullptr;
    int platformNumber = 1; // Нумерація колій починається з 1

    Train* current = head;
    while (current != nullptr) {
        if (isTimeInRange(current->hours, current->minutes, startHours, startMinutes, endHours, endMinutes)) {
            filteredList = appendFilteredTrain(filteredList, current->trainNumber,
                current->hours, current->minutes,
                platformNumber);
            platformNumber++;
        }
        current = current->next;
    }
    return filteredList;
}

// Функція для видалення списку
void deleteList(Train* head) {
    while (head != nullptr) {
        Train* temp = head;
        head = head->next;
        delete temp;
    }
}

void deleteFilteredList(FilteredTrain* head) {
    while (head != nullptr) {
        FilteredTrain* temp = head;
        head = head->next;
        delete temp;
    }
}

// Функція для зчитування часу
void readTime(const string& prompt, int& hours, int& minutes) {
    cout << prompt;
    char colon;
    cin >> hours >> colon >> minutes;
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    Train* trainList = nullptr;

    // Додавання потягів до оригінального списку (без колій)
    trainList = appendTrain(trainList, 101, 8, 30);
    trainList = appendTrain(trainList, 202, 9, 15);
    trainList = appendTrain(trainList, 303, 10, 45);
    trainList = appendTrain(trainList, 404, 12, 0);
    trainList = appendTrain(trainList, 505, 14, 20);
    trainList = appendTrain(trainList, 606, 16, 30);
    trainList = appendTrain(trainList, 707, 18, 45);
    trainList = appendTrain(trainList, 808, 20, 10);

    printOriginalList(trainList);

    cout << "Введіть діапазон часу для фільтрації потягів (формат ГГ:ХХ)" << endl;
    int startHours, startMinutes, endHours, endMinutes;

    readTime("Початковий час: ", startHours, startMinutes);
    readTime("Кінцевий час: ", endHours, endMinutes);

    FilteredTrain* filteredList = filterTrains(trainList, startHours, startMinutes, endHours, endMinutes);

    printFilteredList(filteredList);

    deleteList(trainList);
    deleteFilteredList(filteredList);

    return 0;
}