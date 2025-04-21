#include <iostream>
#include <fstream>
#include <limits.h>
#include <iomanip>
using namespace std;

typedef int Info;
struct Node
{
    Node* left,
        * right;
    Info info;
};

// Функція для виведення дерева
void PrintTree(Node* root, int level)
{
    if (root == NULL)
        return;

    // Збільшуємо відступ для наступного рівня
    const int INDENT = 4;
    level += INDENT;

    // Спочатку виводимо праве піддерево (воно буде зверху)
    PrintTree(root->right, level);

    // Потім виводимо сам корінь
    cout << endl;
    for (int i = INDENT; i < level; i++)
        cout << " ";
    cout << root->info;

    // Нарешті виводимо ліве піддерево (воно буде знизу)
    PrintTree(root->left, level);
}

// Функція для додавання вузла в бінарне дерево пошуку
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

// Функція пошуку максимального значення
Node* FindMax(Node* root)
{
    if (root->right != NULL)
        return FindMax(root->right);
    else
        return root;
}

// Функція пошуку мінімального значення
Node* FindMin(Node* root)
{
    if (root->left != NULL)
        return FindMin(root->left);
    else
        return root;
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

// Функція обчислення висоти дерева
int Height(Node* root)
{
    if (root == NULL)
        return 0;
    int hL = Height(root->left);
    int hR = Height(root->right);
    return (hL > hR ? hL : hR) + 1;
}

// Функція обчислення фактора балансування
int BFactor(Node* root)
{
    return Height(root->right) - Height(root->left);
}

// Функція балансування дерева
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

// Функція видалення вузла з бінарного дерева пошуку
Node* BinarySearchDelete(Node* root, Info value)
{
    if (NULL == root) return NULL;
    if (root->info == value)
    {
        if (NULL == root->left && NULL == root->right)
        {
            delete root;
            return NULL;
        }
        if (NULL == root->right && root->left != NULL)
        {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        if (NULL == root->left && root->right != NULL)
        {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        root->info = FindMax(root->left)->info;
        root->left = BinarySearchDelete(root->left, root->info);
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

// Функція для видалення всього дерева
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

// Префіксний обхід для пошуку першого максимального елемента
void PrefixOrderWithMax(Node* root, Node*& maxNode)
{
    if (root != NULL) {
        // Перше відвідуємо корінь
        if (maxNode == NULL || root->info > maxNode->info) {
            maxNode = root;
        }

        // Потім ліве піддерево
        PrefixOrderWithMax(root->left, maxNode);

        // Потім праве піддерево
        PrefixOrderWithMax(root->right, maxNode);
    }
}

// Функція виведення дерева з виділенням елемента (графічно)
void PrintTreeWithHighlight(Node* root, int level, int highlight_value)
{
    if (root == NULL)
        return;

    // Збільшуємо відступ для наступного рівня
    const int INDENT = 4;
    level += INDENT;

    // Спочатку виводимо праве піддерево (воно буде зверху)
    PrintTreeWithHighlight(root->right, level, highlight_value);

    // Потім виводимо сам корінь
    cout << endl;
    for (int i = INDENT; i < level; i++)
        cout << " ";

    if (root->info == highlight_value) {
        cout << "[" << root->info << "]";
    }
    else {
        cout << root->info;
    }

    // Нарешті виводимо ліве піддерево (воно буде знизу)
    PrintTreeWithHighlight(root->left, level, highlight_value);
}

// Префіксний обхід з виділенням елемента
void PrefixOrderWithHighlight(Node* root, int highlight_value)
{
    if (root != NULL)
    {
        // Префіксний обхід: корінь -> ліве піддерево -> праве піддерево
        if (root->info == highlight_value) {
            cout << "[" << root->info << "] ";
        }
        else {
            cout << root->info << " ";
        }
        PrefixOrderWithHighlight(root->left, highlight_value);
        PrefixOrderWithHighlight(root->right, highlight_value);
    }
}

// Декоратор для знаходження першого максимального елемента
void FindFirstMax(Node* root)
{
    Node* maxNode = NULL;
    PrefixOrderWithMax(root, maxNode);

    if (maxNode != NULL) {
        cout << "Перший елемент з максимальним значенням: " << maxNode->info << endl;
        cout << "Дерево з виділеним елементом: ";
        PrintTreeWithHighlight(root, 0, maxNode->info);

        cout << "\nПрефіксний обхід з виділеним елементом: ";
        PrefixOrderWithHighlight(root, maxNode->info);
        cout << endl;
    }
    else {
        cout << "Бінарне дерево порожнє" << endl;
    }
}

// Префіксний обхід дерева (для виведення)
void PrefixOrder(Node* root)
{
    if (root != NULL)
    {
        cout << root->info << " ";
        PrefixOrder(root->left);
        PrefixOrder(root->right);
    }
}

// Меню для користувача
void showMenu() {
    cout << "\n======== Меню операцій з бінарним деревом ========\n";
    cout << "1. Створити нове бінарне дерево пошуку\n";
    cout << "2. Додати новий елемент\n";
    cout << "3. Вивести дерево\n";
    cout << "4. Збалансувати дерево\n";
    cout << "5. Видалити елемент\n";
    cout << "6. Знайти перший елемент з максимальним значенням\n";
    cout << "7. Вивести дерево в префіксному порядку\n";
    cout << "0. Вийти\n";
    cout << "Ваш вибір: ";
}

int main()
{
    Node* root = NULL;
    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            // Створення бінарного дерева
            if (root != NULL) {
                cout << "Увага: попереднє дерево буде видалено!" << endl;
                DeleteTree(root); // Очищаємо попереднє дерево
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

            cout << "\nБінарне дерево створено:\n";
            PrintTree(root, 0);
            break;
        }
        case 2: {
            // Додавання нового елемента
            int value;
            cout << "Введіть значення для вставки: ";
            cin >> value;

            bool found = false;
            BinarySearchInsert(root, value, found);

            cout << "\nОновлене дерево:\n";
            PrintTree(root, 0);
            break;
        }
        case 3: {
            // Виведення дерева
            if (root == NULL) {
                cout << "\nДерево порожнє.\n";
            }
            else {
                cout << "\nБінарне дерево:\n";
                PrintTree(root, 0);
            }
            break;
        }
        case 4: {
            // Збалансування дерева
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
        case 5: {
            // Видалення елемента
            if (root == NULL) {
                cout << "\nДерево порожнє. Нічого видаляти.\n";
            }
            else {
                int value;
                cout << "Введіть значення для видалення: ";
                cin >> value;

                root = BinarySearchDelete(root, value);

                cout << "\nОновлене дерево після видалення:\n";
                if (root == NULL) {
                    cout << "Дерево порожнє.\n";
                }
                else {
                    PrintTree(root, 0);
                }
            }
            break;
        }
        case 6: {
            // Знаходження першого елемента з максимальним значенням
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
        case 7: {
            // Виведення дерева в префіксному порядку
            if (root == NULL) {
                cout << "\nДерево порожнє.\n";
            }
            else {
                cout << "\nПрефіксний обхід дерева: ";
                PrefixOrder(root);
                cout << "\n";
            }
            break;
        }
        case 0:
            // Очищення пам'яті перед виходом
            DeleteTree(root);
            cout << "Програма завершена.\n";
            break;
        default:
            cout << "Невірний вибір. Спробуйте ще раз.\n";
        }

    } while (choice != 0);

    return 0;
}