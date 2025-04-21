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

// ������� ��� ��������� ������
void PrintTree(Node* root, int level)
{
    if (root == NULL)
        return;

    // �������� ������ ��� ���������� ����
    const int INDENT = 4;
    level += INDENT;

    // �������� �������� ����� �������� (���� ���� ������)
    PrintTree(root->right, level);

    // ���� �������� ��� �����
    cout << endl;
    for (int i = INDENT; i < level; i++)
        cout << " ";
    cout << root->info;

    // ������ �������� ��� �������� (���� ���� �����)
    PrintTree(root->left, level);
}

// ������� ��� ��������� ����� � ������ ������ ������
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

// ������� ������ ������������� ��������
Node* FindMax(Node* root)
{
    if (root->right != NULL)
        return FindMax(root->right);
    else
        return root;
}

// ������� ������ ���������� ��������
Node* FindMin(Node* root)
{
    if (root->left != NULL)
        return FindMin(root->left);
    else
        return root;
}

// ������� ����� �������
void RightRotation(Node*& root)
{
    Node* tmp1 = root->left;
    Node* tmp2 = tmp1->right;
    tmp1->right = root;
    root->left = tmp2;
    root = tmp1;
}

// ������� ��� �������
void LeftRotation(Node*& root)
{
    Node* tmp1 = root->right;
    Node* tmp2 = tmp1->left;
    tmp1->left = root;
    root->right = tmp2;
    root = tmp1;
}

// ������� ���������� ������ ������
int Height(Node* root)
{
    if (root == NULL)
        return 0;
    int hL = Height(root->left);
    int hR = Height(root->right);
    return (hL > hR ? hL : hR) + 1;
}

// ������� ���������� ������� ������������
int BFactor(Node* root)
{
    return Height(root->right) - Height(root->left);
}

// ������� ������������ ������
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

// ������� ��������� ����� � �������� ������ ������
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

// ������� ��� ��������� ������ ������
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

// ���������� ����� ��� ������ ������� ������������� ��������
void PrefixOrderWithMax(Node* root, Node*& maxNode)
{
    if (root != NULL) {
        // ����� ������� �����
        if (maxNode == NULL || root->info > maxNode->info) {
            maxNode = root;
        }

        // ���� ��� ��������
        PrefixOrderWithMax(root->left, maxNode);

        // ���� ����� ��������
        PrefixOrderWithMax(root->right, maxNode);
    }
}

// ������� ��������� ������ � ��������� �������� (��������)
void PrintTreeWithHighlight(Node* root, int level, int highlight_value)
{
    if (root == NULL)
        return;

    // �������� ������ ��� ���������� ����
    const int INDENT = 4;
    level += INDENT;

    // �������� �������� ����� �������� (���� ���� ������)
    PrintTreeWithHighlight(root->right, level, highlight_value);

    // ���� �������� ��� �����
    cout << endl;
    for (int i = INDENT; i < level; i++)
        cout << " ";

    if (root->info == highlight_value) {
        cout << "[" << root->info << "]";
    }
    else {
        cout << root->info;
    }

    // ������ �������� ��� �������� (���� ���� �����)
    PrintTreeWithHighlight(root->left, level, highlight_value);
}

// ���������� ����� � ��������� ��������
void PrefixOrderWithHighlight(Node* root, int highlight_value)
{
    if (root != NULL)
    {
        // ���������� �����: ����� -> ��� �������� -> ����� ��������
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

// ��������� ��� ����������� ������� ������������� ��������
void FindFirstMax(Node* root)
{
    Node* maxNode = NULL;
    PrefixOrderWithMax(root, maxNode);

    if (maxNode != NULL) {
        cout << "������ ������� � ������������ ���������: " << maxNode->info << endl;
        cout << "������ � �������� ���������: ";
        PrintTreeWithHighlight(root, 0, maxNode->info);

        cout << "\n���������� ����� � �������� ���������: ";
        PrefixOrderWithHighlight(root, maxNode->info);
        cout << endl;
    }
    else {
        cout << "������� ������ ������" << endl;
    }
}

// ���������� ����� ������ (��� ���������)
void PrefixOrder(Node* root)
{
    if (root != NULL)
    {
        cout << root->info << " ";
        PrefixOrder(root->left);
        PrefixOrder(root->right);
    }
}

// ���� ��� �����������
void showMenu() {
    cout << "\n======== ���� �������� � ������� ������� ========\n";
    cout << "1. �������� ���� ������ ������ ������\n";
    cout << "2. ������ ����� �������\n";
    cout << "3. ������� ������\n";
    cout << "4. ������������ ������\n";
    cout << "5. �������� �������\n";
    cout << "6. ������ ������ ������� � ������������ ���������\n";
    cout << "7. ������� ������ � ����������� �������\n";
    cout << "0. �����\n";
    cout << "��� ����: ";
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
            // ��������� �������� ������
            if (root != NULL) {
                cout << "�����: �������� ������ ���� ��������!" << endl;
                DeleteTree(root); // ������� �������� ������
            }

            int N;
            cout << "ʳ������ �����: ";
            cin >> N;

            if (N <= 0) {
                cout << "ʳ������ ����� ������� ���� ����� 0!" << endl;
                break;
            }

            Info value;
            bool found = false;

            for (int i = 0; i < N; i++) {
                cout << "�������� #" << i + 1 << ": ";
                cin >> value;
                BinarySearchInsert(root, value, found);
            }

            cout << "\n������� ������ ��������:\n";
            PrintTree(root, 0);
            break;
        }
        case 2: {
            // ��������� ������ ��������
            int value;
            cout << "������ �������� ��� �������: ";
            cin >> value;

            bool found = false;
            BinarySearchInsert(root, value, found);

            cout << "\n�������� ������:\n";
            PrintTree(root, 0);
            break;
        }
        case 3: {
            // ��������� ������
            if (root == NULL) {
                cout << "\n������ ������.\n";
            }
            else {
                cout << "\n������� ������:\n";
                PrintTree(root, 0);
            }
            break;
        }
        case 4: {
            // ������������� ������
            if (root == NULL) {
                cout << "\n������ ������. ͳ���� �����������.\n";
            }
            else {
                BalanceHeight(root);
                cout << "\n������������ ������:\n";
                PrintTree(root, 0);
            }
            break;
        }
        case 5: {
            // ��������� ��������
            if (root == NULL) {
                cout << "\n������ ������. ͳ���� ��������.\n";
            }
            else {
                int value;
                cout << "������ �������� ��� ���������: ";
                cin >> value;

                root = BinarySearchDelete(root, value);

                cout << "\n�������� ������ ���� ���������:\n";
                if (root == NULL) {
                    cout << "������ ������.\n";
                }
                else {
                    PrintTree(root, 0);
                }
            }
            break;
        }
        case 6: {
            // ����������� ������� �������� � ������������ ���������
            if (root == NULL) {
                cout << "\n������ ������. ��������� ������ ������������ �������.\n";
            }
            else {
                cout << "\n";
                FindFirstMax(root);
                cout << "\n";
            }
            break;
        }
        case 7: {
            // ��������� ������ � ����������� �������
            if (root == NULL) {
                cout << "\n������ ������.\n";
            }
            else {
                cout << "\n���������� ����� ������: ";
                PrefixOrder(root);
                cout << "\n";
            }
            break;
        }
        case 0:
            // �������� ���'�� ����� �������
            DeleteTree(root);
            cout << "�������� ���������.\n";
            break;
        default:
            cout << "������� ����. ��������� �� ���.\n";
        }

    } while (choice != 0);

    return 0;
}