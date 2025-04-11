#include <iostream>
#include <string>
#include <Windows.h>

struct Train {
    int trainNumber;    
    int hours;        
    int minutes;       
    int platform;       
    Train* next;       
};

Train* createTrainNode(int trainNumber, int hours, int minutes, int platform = 0) {
    Train* newNode = new Train;
    newNode->trainNumber = trainNumber;
    newNode->hours = hours;
    newNode->minutes = minutes;
    newNode->platform = platform;
    newNode->next = nullptr;
    return newNode;
}

Train* appendTrain(Train* head, int trainNumber, int hours, int minutes, int platform = 0) {
    Train* newNode = createTrainNode(trainNumber, hours, minutes, platform);

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

void printTrainList(Train* head, bool showPlatform) {
    std::cout << "=== " << (showPlatform ? "Відфільтрований список потягів" : "Список всіх потягів") << " ===" << std::endl;

    if (head == nullptr) {
        std::cout << "Список порожній" << std::endl;
        return;
    }

    std::cout << "Номер потягу\tЧас прибуття";
    if (showPlatform) {
        std::cout << "\tНомер колії";
    }
    std::cout << std::endl;

    Train* current = head;
    while (current != nullptr) {
        std::cout << current->trainNumber << "\t\t"
            << current->hours << ":"
            << (current->minutes < 10 ? "0" : "") << current->minutes;

        if (showPlatform) {
            std::cout << "\t\t" << current->platform;
        }

        std::cout << std::endl;
        current = current->next;
    }
    std::cout << std::endl;
}

bool isTimeInRange(int hours, int minutes, int startHours, int startMinutes, int endHours, int endMinutes) {
    int time = hours * 60 + minutes;
    int startTime = startHours * 60 + startMinutes;
    int endTime = endHours * 60 + endMinutes;

    return time >= startTime && time <= endTime;
}

Train* filterTrainsByTimeRange(Train* head, int startHours, int startMinutes, int endHours, int endMinutes) {
    Train* filteredList = nullptr;
    int platformCounter = 1; // Починаємо нумерацію колій з 1

    Train* current = head;
    while (current != nullptr) {
        // Перевірка, чи входить час прибуття в заданий діапазон
        if (isTimeInRange(current->hours, current->minutes, startHours, startMinutes, endHours, endMinutes)) {
            // Додаємо потяг до відфільтрованого списку з номером колії
            filteredList = appendTrain(filteredList, current->trainNumber,
                current->hours, current->minutes, platformCounter);
            platformCounter++; // Збільшуємо номер колії для наступного потягу
        }
        current = current->next;
    }

    return filteredList;
}

void deleteList(Train* head) {
    while (head != nullptr) {
        Train* temp = head;
        head = head->next;
        delete temp;
    }
}

void readTime(const std::string& prompt, int& hours, int& minutes) {
    std::cout << prompt;
    char colon; // для читання двокрапки між годинами і хвилинами
    std::cin >> hours >> colon >> minutes;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Train* trainList = nullptr;

    trainList = appendTrain(trainList, 101, 8, 30);
    trainList = appendTrain(trainList, 202, 9, 15);
    trainList = appendTrain(trainList, 303, 10, 45);
    trainList = appendTrain(trainList, 404, 12, 0);
    trainList = appendTrain(trainList, 505, 14, 20);
    trainList = appendTrain(trainList, 606, 16, 30);
    trainList = appendTrain(trainList, 707, 18, 45);
    trainList = appendTrain(trainList, 808, 20, 10);

    printTrainList(trainList, false);

    std::cout << "Введіть діапазон часу для фільтрації потягів (формат ГГ:ХХ)" << std::endl;
    int startHours, startMinutes, endHours, endMinutes;

    readTime("Початковий час: ", startHours, startMinutes);
    readTime("Кінцевий час: ", endHours, endMinutes);

    Train* filteredList = filterTrainsByTimeRange(trainList, startHours, startMinutes, endHours, endMinutes);

    printTrainList(filteredList, true);

    deleteList(trainList);
    deleteList(filteredList);

    return 0;
}