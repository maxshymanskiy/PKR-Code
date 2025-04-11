#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <windows.h> 
using namespace std;

struct Student {
	std::string surname;
	double averageScore;
	int scholarship;
	Student* next;
	Student* prev;
};

void addStudent(Student*& head, const std::string& surname, double averageScore, int scholarship) {
	Student* newStudent = new Student{ surname, averageScore, scholarship, nullptr, nullptr };
	if (!head) {
		head = newStudent;
	}
	else {
		Student* temp = head;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = newStudent;
		newStudent->prev = temp;
	}
}

void printList(const Student* head) {
	const Student* temp = head;
	while (temp) {
		cout << "Прізвище: " << temp->surname
			<< ", Середній бал: " << fixed << std::setprecision(2) << temp->averageScore
			<< ", Стипендія: " << temp->scholarship << endl;
		temp = temp->next;
	}
}

void findStudentsByAverage(const Student* head, double targetAverage) {
	const Student* curr = head;
	bool found = false;
	cout << "Студенти із середнім балом " << fixed << setprecision(2) << targetAverage << ":" << endl;
	while (curr != nullptr) {
		if (curr->averageScore == targetAverage) {
			std::cout << "Прізвище: " << curr->surname
				<< ", Середній бал: " << curr->averageScore
				<< ", Стипендія: " << curr->scholarship << endl;
			found = true;
		}
		curr = curr->next;
	}
	if (!found) {
		cout << "Студентів із заданим середнім балом не знайдено." << endl;
	}
}

void removeNonScholarship(Student*& head) {
	Student* curr = head;
	while (curr != nullptr) {
		Student* nextNode = curr->next;
		if (curr->scholarship == 0) {
			if (curr->prev) {
				curr->prev->next = curr->next;
			}
			else {
				head = curr->next;
			}
			if (curr->next) {
				curr->next->prev = curr->prev;
			}
			delete curr;
		}
		curr = nextNode;
	}
}

void readStudentsFromFile(const std::string& filename, Student*& head) {
	std::ifstream file(filename);
	if (file.is_open()) {
		std::string surname;
		double averageScore;
		int scholarship;
		while (file >> surname >> averageScore >> scholarship) {
			addStudent(head, surname, averageScore, scholarship);
		}
		file.close();
	}
	else {
		cerr << "Не вдалося відкрити файл" << endl;
	}
}

void clearList(Student*& head) {
	Student* curr = head;
	while (curr != nullptr) {
		Student* next = curr->next;
		delete curr;
		curr = next;
	}
	head = nullptr;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Student* students = nullptr;
	std::string filename = "students.txt";

	readStudentsFromFile(filename, students);
	cout << "Початковий список:" << endl;
	printList(students);
	double targetAverage;
	cout << "Введіть цільовий середній бал: ";
	cin >> targetAverage;

	findStudentsByAverage(students, targetAverage);

	removeNonScholarship(students);

	cout << "Список після видалення студентів без стипендії:" << endl;
	printList(students);

	clearList(students);

	return 0;
}
