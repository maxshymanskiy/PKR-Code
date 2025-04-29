#include <iostream>
#include <iomanip>
#include <Windows.h>
using namespace std;

typedef int Info;
struct Node
{
    Node* left,
        * right;
    Info info;
};

void PrintTree(Node* root, int level)
{
    if (root != NULL)
    {
        PrintTree(root->right, level + 1);
        for (int i = 1; i <= level; i++)
            cout << "    ";
        cout << root->info << endl;
        PrintTree(root->left, level + 1);
    }
}

// Виведення бінарного дерева з виділенням певного елемента
void PrintTreeWithHighlight(Node* root, int level, Node* highlight_node)
{
    if (root == NULL)
        return;

    const int INDENT = 4;
    level += INDENT;

    PrintTreeWithHighlight(root->right, level, highlight_node);

    cout << endl;
    for (int i = INDENT; i < level; i++)
        cout << " ";

    if (root == highlight_node) { // Порівнюємо адреси вузлів
        cout << "[" << root->info << "]";
    }
    else {
        cout << root->info;
    }

    PrintTreeWithHighlight(root->left, level, highlight_node);
}

int Height(Node* root)
{
    if (root == NULL)
        return 0;
    int hL = Height(root->left);
    int hR = Height(root->right);
    return (hL > hR ? hL : hR) + 1;
}

// Обчислення фактора балансування
int BFactor(Node* root)
{
    return Height(root->right) - Height(root->left);
}

// Функція правої ротації
void RightRotation(Node*& root)
{
    Node* tmp1 = root->left;
    Node* tmp2 = tmp1->right;
    tmp1->right = root;
    root->left = tmp2;
    root = tmp1;
}

// Функція лівої ротації
void LeftRotation(Node*& root)
{
    Node* tmp1 = root->right;
    Node* tmp2 = tmp1->left;
    tmp1->left = root;
    root->right = tmp2;
    root = tmp1;
}

Node* FindMax(Node* root)
{
    if (root->right != NULL)
        return FindMax(root->right);
    else
        return root;
}

void DeleteTree(Node*& root)
{
    if (root != NULL)
    {
        DeleteTree(root->left);
        DeleteTree(root->right);
        delete root;
        root = NULL;
    }
}

// Постфіксний обхід з виділенням елемента
void PostfixOrderWithHighlight(Node* root, Node* highlight_node)
{
    if (root != NULL)
    {
        PostfixOrderWithHighlight(root->left, highlight_node);
        PostfixOrderWithHighlight(root->right, highlight_node);

        if (root == highlight_node) { // Порівнюємо адреси вузлів
            cout << "[" << root->info << "] ";
        }
        else {
            cout << root->info << " ";
        }
    }
}

// Постфіксний обхід для пошуку першого максимального елемента
void PostfixOrderWithMax(Node* root, Node*& maxNode)
{
    if (root != NULL) {
        // Спочатку ліве піддерево
        PostfixOrderWithMax(root->left, maxNode);

        // Потім праве піддерево
        PostfixOrderWithMax(root->right, maxNode);

        // Нарешті корінь (постфіксний порядок)
        if (maxNode == NULL || root->info > maxNode->info) {
            maxNode = root;
        }
    }
}

// ПУНКТ 1: Функція для створення бінарного дерева із заданою кількістю елементів
Node* CreateTree(int nodeCount)
{
    if (nodeCount == 0)
        return NULL;
    else
    {
        Node* newNode = new Node;
        cout << " Введіть значення вузла: ";
        cin >> newNode->info;
        int leftCount = nodeCount / 2;
        int rightCount = nodeCount - leftCount - 1;
        newNode->left = CreateTree(leftCount);
        newNode->right = CreateTree(rightCount);
        return newNode;
    }
}

// ПУНКТ 3, 4: Функція для додавання елемента до бінарного дерева пошуку
Node* BinarySearchInsert(Node*& root, Info value, bool& found)
{
    if (root == NULL)
    {
        root = new Node;
        root->info = value;
        root->left = NULL;
        root->right = NULL;
        found = false;
        return root;
    }
    else
        if (value == root->info)
        {
            found = true;
            return root;
        }
        else
            if (value < root->info)
                return BinarySearchInsert(root->left, value, found);
            else
                return BinarySearchInsert(root->right, value, found);
}

// ПУНКТ 5: Функція балансування бінарного дерева пошуку
void BalanceHeight(Node*& root)
{
    if (root != NULL)
    {
        while (BFactor(root) >= 2)
        {
            if (BFactor(root->right) < 0)
                RightRotation(root->right);
            LeftRotation(root);
        }
        while (BFactor(root) <= -2)
        {
            if (BFactor(root->left) > 0)
                LeftRotation(root->left);
            RightRotation(root);
        }
        BalanceHeight(root->left);
        BalanceHeight(root->right);
    }
}

// ПУНКТ 6, 7, 8: Функція видалення вузла з бінарного дерева пошуку
Node* BinarySearchDelete(Node* root, Info value)
{
    if (NULL == root) return NULL;
    if (root->info == value)
    {
        // ПУНКТ 6: Видалення листового вузла (без дочірніх)
        if (NULL == root->left && NULL == root->right)
        {
            delete root;
            return NULL;
        }
        // ПУНКТ 7: Видалення вузла з одним дочірнім (лівим)
        if (NULL == root->right && root->left != NULL)
        {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        // ПУНКТ 7: Видалення вузла з одним дочірнім (правим)
        if (NULL == root->left && root->right != NULL)
        {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        // ПУНКТ 8: Видалення вузла з двома дочірніми
        Info maxValue = FindMax(root->left)->info;
        root->info = maxValue;
        root->left = BinarySearchDelete(root->left, maxValue);
        return root;
    }

    if (value < root->info)
    {
        root->left = BinarySearchDelete(root->left, value);
        return root;
    }
    if (value > root->info)
    {
        root->right = BinarySearchDelete(root->right, value);
        return root;
    }
    return root;
}

// ПУНКТ 10: Декоратор для знаходження першого максимального елемента
void FindFirstMax(Node* root)
{
    Node* maxNode = NULL;
    PostfixOrderWithMax(root, maxNode);

    if (maxNode != NULL) {
        cout << "Перший елемент з максимальним значенням: " << maxNode->info << endl;
        cout << "Дерево з виділеним елементом: ";
        PrintTreeWithHighlight(root, 0, maxNode); // Передаємо вузол для підсвічування

        cout << "\nПостфіксний обхід з виділеним елементом: ";
        PostfixOrderWithHighlight(root, maxNode); // Передаємо вузол
        cout << endl;
    }
    else {
        cout << "Бінарне дерево порожнє" << endl;
    }
}

// Функція для відображення меню
void showMenu() {
    cout << "\n======== Меню операцій з бінарним деревом ========\n";
    cout << "1. Створити нове бінарне дерево з вказаною кількістю елементів\n";
    cout << "2. Відобразити бінарне дерево\n";
    cout << "3. Створити бінарне дерево пошуку з вказаною кількістю елементів\n";
    cout << "4. Додати новий елемент до бінарного дерева пошуку\n";
    cout << "5. Збалансувати бінарне дерево пошуку\n";
    cout << "6. Видалити листовий вузол (без дочірніх)\n";
    cout << "7. Видалити вузол з одним дочірнім\n";
    cout << "8. Видалити вузол з двома дочірніми\n";
    cout << "9. Видалити вузол з усіма його дочірніми (видалити піддерево)\n";
    cout << "10. Знайти перший елемент з максимальним значенням (постфіксний обхід)\n";
    cout << "0. Вихід\n";
    cout << "Ваш вибір: ";
}

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    Node* root = NULL;
    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            // ПУНКТ 1: Створення нового бінарного дерева
            if (root != NULL) {
                cout << "Увага: Попереднє дерево буде видалено!" << endl;
                DeleteTree(root); // Очищення попереднього дерева
                root = NULL;
            }

            int N;
            cout << "Кількість вузлів: ";
            cin >> N;

            if (N <= 0) {
                cout << "Кількість вузлів повинна бути більше 0!" << endl;
                break;
            }

            root = CreateTree(N);
            cout << "\nБінарне дерево створено:\n";
            PrintTree(root, 0);
            break;
        }
        case 2: {
            // ПУНКТ 2: Виведення бінарного дерева
            if (root == NULL) {
                cout << "\nДерево порожнє.\n";
            }
            else {
                cout << "\nБінарне дерево:\n";
                PrintTree(root, 0);
            }
            break;
        }
        case 3: {
            // ПУНКТ 3: Створення бінарного дерева пошуку
            if (root != NULL) {
                cout << "Увага: Попереднє дерево буде видалено!" << endl;
                DeleteTree(root); // Очищення попереднього дерева
                root = NULL;
            }

            int N;
            cout << "Кількість вузлів: ";
            cin >> N;

            if (N <= 0) {
                cout << "Кількість вузлів повинна бути більше 0!" << endl;
                break;
            }

            Info value;
            bool found = false;

            for (int i = 0; i < N; i++) {
                cout << "Значення #" << i + 1 << ": ";
                cin >> value;
                BinarySearchInsert(root, value, found);
            }

            cout << "\nБінарне дерево пошуку створено:\n";
            PrintTree(root, 0);
            break;
        }
        case 4: {
            // ПУНКТ 4: Додавання нового елемента
            int value;
            cout << "Введіть значення для вставки: ";
            cin >> value;

            bool found = false;
            BinarySearchInsert(root, value, found);

            cout << "\nОновлене дерево:\n";
            PrintTree(root, 0);
            break;
        }
        case 5: {
            // ПУНКТ 5: Збалансування дерева
            if (root == NULL) {
                cout << "\nДерево порожнє. Нічого балансувати.\n";
            }
            else {
                BalanceHeight(root);
                cout << "\nЗбалансоване дерево:\n";
                PrintTree(root, 0);
            }
            break;
        }
        case 6: {
            // ПУНКТ 6: Видалення листового вузла
            if (root == NULL) {
                cout << "\nДерево порожнє. Нічого видаляти.\n";
            }
            else {
                int value;
                cout << "Введіть значення для видалення (має бути листовим вузлом): ";
                cin >> value;

                // Перевірка чи є вузол листовим
                Node* current = root;
                Node* parent = NULL;
                bool found = false;
                bool isLeaf = false;

                // Пошук вузла та його батьківського вузла
                while (current != NULL && !found) {
                    if (current->info == value) {
                        found = true;
                        if (current->left == NULL && current->right == NULL) {
                            isLeaf = true;
                        }
                    }
                    else {
                        parent = current;
                        if (value < current->info) {
                            current = current->left;
                        }
                        else {
                            current = current->right;
                        }
                    }
                }

                if (!found) {
                    cout << "\nВузол зі значенням " << value << " не знайдено.\n";
                }
                else if (!isLeaf) {
                    cout << "\nВузол зі значенням " << value << " не є листовим.\n";
                }
                else {
                    root = BinarySearchDelete(root, value);
                    cout << "\nЛистовий вузол видалено. Оновлене дерево:\n";
                    PrintTree(root, 0);
                }
            }
            break;
        }
        case 7: {
            // ПУНКТ 7: Видалення вузла з одним дочірнім
            if (root == NULL) {
                cout << "\nДерево порожнє. Нічого видаляти.\n";
            }
            else {
                int value;
                cout << "Введіть значення для видалення (має мати рівно одного дочірнього): ";
                cin >> value;

                // Перевірка чи має вузол рівно одного дочірнього
                Node* current = root;
                Node* parent = NULL;
                bool found = false;
                bool hasOneChild = false;

                // Пошук вузла та його батьківського вузла
                while (current != NULL && !found) {
                    if (current->info == value) {
                        found = true;
                        if ((current->left == NULL && current->right != NULL) ||
                            (current->left != NULL && current->right == NULL)) {
                            hasOneChild = true;
                        }
                    }
                    else {
                        parent = current;
                        if (value < current->info) {
                            current = current->left;
                        }
                        else {
                            current = current->right;
                        }
                    }
                }

                if (!found) {
                    cout << "\nВузол зі значенням " << value << " не знайдено.\n";
                }
                else if (!hasOneChild) {
                    cout << "\nВузол зі значенням " << value << " не має рівно одного дочірнього.\n";
                }
                else {
                    root = BinarySearchDelete(root, value);
                    cout << "\nВузол з одним дочірнім видалено. Оновлене дерево:\n";
                    PrintTree(root, 0);
                }
            }
            break;
        }
        case 8: {
            // ПУНКТ 8: Видалення вузла з двома дочірніми
            if (root == NULL) {
                cout << "\nДерево порожнє. Нічого видаляти.\n";
            }
            else {
                int value;
                cout << "Введіть значення для видалення (має мати два дочірніх): ";
                cin >> value;

                // Перевірка чи має вузол два дочірніх
                Node* current = root;
                Node* parent = NULL;
                bool found = false;
                bool hasTwoChildren = false;

                // Пошук вузла та його батьківського вузла
                while (current != NULL && !found) {
                    if (current->info == value) {
                        found = true;
                        if (current->left != NULL && current->right != NULL) {
                            hasTwoChildren = true;
                        }
                    }
                    else {
                        parent = current;
                        if (value < current->info) {
                            current = current->left;
                        }
                        else {
                            current = current->right;
                        }
                    }
                }

                if (!found) {
                    cout << "\nВузол зі значенням " << value << " не знайдено.\n";
                }
                else if (!hasTwoChildren) {
                    cout << "\nВузол зі значенням " << value << " не має двох дочірніх.\n";
                }
                else {
                    root = BinarySearchDelete(root, value);
                    cout << "\nВузол з двома дочірніми видалено. Оновлене дерево:\n";
                    PrintTree(root, 0);
                }
            }
            break;
        }
        case 9: {
            // ПУНКТ 9: Видалення вузла з усіма його дочірніми (видалення піддерева)
            if (root == NULL) {
                cout << "\nДерево порожнє. Нічого видаляти.\n";
            }
            else {
                int value;
                cout << "Введіть значення (вузол та все його піддерево буде видалено): ";
                cin >> value;

                // Пошук вузла
                Node* current = root;
                Node* parent = NULL;
                bool found = false;

                // Пошук вузла та його батьківського вузла
                while (current != NULL && !found) {
                    if (current->info == value) {
                        found = true;
                    }
                    else {
                        parent = current;
                        if (value < current->info) {
                            current = current->left;
                        }
                        else {
                            current = current->right;
                        }
                    }
                }

                if (!found) {
                    cout << "\nВузол зі значенням " << value << " не знайдено.\n";
                }
                else {
                    // Якщо це кореневий вузол, видаляємо все дерево
                    if (parent == NULL) {
                        DeleteTree(root);
                        root = NULL;
                        cout << "\nВсе дерево видалено.\n";
                    }
                    else {
                        // Якщо це лівий дочірній, видаляємо ліве піддерево
                        if (parent->left != NULL && parent->left->info == value) {
                            DeleteTree(parent->left);
                            parent->left = NULL;
                        }
                        // Якщо це правий дочірній, видаляємо праве піддерево
                        else if (parent->right != NULL && parent->right->info == value) {
                            DeleteTree(parent->right);
                            parent->right = NULL;
                        }
                        cout << "\nПіддерево видалено. Оновлене дерево:\n";
                        PrintTree(root, 0);
                    }
                }
            }
            break;
        }
        case 10: {
            // ПУНКТ 10: Знаходження першого елемента з максимальним значенням у постфіксному обході
            if (root == NULL) {
                cout << "\nДерево порожнє. Неможливо знайти максимальний елемент.\n";
            }
            else {
                cout << "\n";
                FindFirstMax(root);
                cout << "\n";
            }
            break;
        }
        case 0:
            // Очищення пам'яті перед виходом
            if (root != NULL) {
                DeleteTree(root);
                root = NULL;
            }
            cout << "Програма завершена.\n";
            break;
        default:
            cout << "Невірний вибір. Спробуйте ще раз.\n";
        }

    } while (choice != 0);

    return 0;
}