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

// ��������� �������� ������ � ��������� ������� ��������
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

    if (root == highlight_node) { // ��������� ������ �����
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

// ���������� ������� ������������
int BFactor(Node* root)
{
    return Height(root->right) - Height(root->left);
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

// ����������� ����� � ��������� ��������
void PostfixOrderWithHighlight(Node* root, Node* highlight_node)
{
    if (root != NULL)
    {
        PostfixOrderWithHighlight(root->left, highlight_node);
        PostfixOrderWithHighlight(root->right, highlight_node);

        if (root == highlight_node) { // ��������� ������ �����
            cout << "[" << root->info << "] ";
        }
        else {
            cout << root->info << " ";
        }
    }
}

// ����������� ����� ��� ������ ������� ������������� ��������
void PostfixOrderWithMax(Node* root, Node*& maxNode)
{
    if (root != NULL) {
        // �������� ��� ��������
        PostfixOrderWithMax(root->left, maxNode);

        // ���� ����� ��������
        PostfixOrderWithMax(root->right, maxNode);

        // ������ ����� (����������� �������)
        if (maxNode == NULL || root->info > maxNode->info) {
            maxNode = root;
        }
    }
}

// ����� 1: ������� ��� ��������� �������� ������ �� ������� ������� ��������
Node* CreateTree(int nodeCount)
{
    if (nodeCount == 0)
        return NULL;
    else
    {
        Node* newNode = new Node;
        cout << " ������ �������� �����: ";
        cin >> newNode->info;
        int leftCount = nodeCount / 2;
        int rightCount = nodeCount - leftCount - 1;
        newNode->left = CreateTree(leftCount);
        newNode->right = CreateTree(rightCount);
        return newNode;
    }
}

// ����� 3, 4: ������� ��� ��������� �������� �� �������� ������ ������
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

// ����� 5: ������� ������������ �������� ������ ������
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

// ����� 6, 7, 8: ������� ��������� ����� � �������� ������ ������
Node* BinarySearchDelete(Node* root, Info value)
{
    if (NULL == root) return NULL;
    if (root->info == value)
    {
        // ����� 6: ��������� ��������� ����� (��� �������)
        if (NULL == root->left && NULL == root->right)
        {
            delete root;
            return NULL;
        }
        // ����� 7: ��������� ����� � ����� ������� (����)
        if (NULL == root->right && root->left != NULL)
        {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        // ����� 7: ��������� ����� � ����� ������� (������)
        if (NULL == root->left && root->right != NULL)
        {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        // ����� 8: ��������� ����� � ����� ��������
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

// ����� 10: ��������� ��� ����������� ������� ������������� ��������
void FindFirstMax(Node* root)
{
    Node* maxNode = NULL;
    PostfixOrderWithMax(root, maxNode);

    if (maxNode != NULL) {
        cout << "������ ������� � ������������ ���������: " << maxNode->info << endl;
        cout << "������ � �������� ���������: ";
        PrintTreeWithHighlight(root, 0, maxNode); // �������� ����� ��� �����������

        cout << "\n����������� ����� � �������� ���������: ";
        PostfixOrderWithHighlight(root, maxNode); // �������� �����
        cout << endl;
    }
    else {
        cout << "������� ������ ������" << endl;
    }
}

// ������� ��� ����������� ����
void showMenu() {
    cout << "\n======== ���� �������� � ������� ������� ========\n";
    cout << "1. �������� ���� ������ ������ � �������� ������� ��������\n";
    cout << "2. ³��������� ������ ������\n";
    cout << "3. �������� ������ ������ ������ � �������� ������� ��������\n";
    cout << "4. ������ ����� ������� �� �������� ������ ������\n";
    cout << "5. ������������ ������ ������ ������\n";
    cout << "6. �������� �������� ����� (��� �������)\n";
    cout << "7. �������� ����� � ����� �������\n";
    cout << "8. �������� ����� � ����� ��������\n";
    cout << "9. �������� ����� � ���� ���� �������� (�������� ��������)\n";
    cout << "10. ������ ������ ������� � ������������ ��������� (����������� �����)\n";
    cout << "0. �����\n";
    cout << "��� ����: ";
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
            // ����� 1: ��������� ������ �������� ������
            if (root != NULL) {
                cout << "�����: �������� ������ ���� ��������!" << endl;
                DeleteTree(root); // �������� ������������ ������
                root = NULL;
            }

            int N;
            cout << "ʳ������ �����: ";
            cin >> N;

            if (N <= 0) {
                cout << "ʳ������ ����� ������� ���� ����� 0!" << endl;
                break;
            }

            root = CreateTree(N);
            cout << "\n������� ������ ��������:\n";
            PrintTree(root, 0);
            break;
        }
        case 2: {
            // ����� 2: ��������� �������� ������
            if (root == NULL) {
                cout << "\n������ ������.\n";
            }
            else {
                cout << "\n������� ������:\n";
                PrintTree(root, 0);
            }
            break;
        }
        case 3: {
            // ����� 3: ��������� �������� ������ ������
            if (root != NULL) {
                cout << "�����: �������� ������ ���� ��������!" << endl;
                DeleteTree(root); // �������� ������������ ������
                root = NULL;
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

            cout << "\n������� ������ ������ ��������:\n";
            PrintTree(root, 0);
            break;
        }
        case 4: {
            // ����� 4: ��������� ������ ��������
            int value;
            cout << "������ �������� ��� �������: ";
            cin >> value;

            bool found = false;
            BinarySearchInsert(root, value, found);

            cout << "\n�������� ������:\n";
            PrintTree(root, 0);
            break;
        }
        case 5: {
            // ����� 5: ������������� ������
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
        case 6: {
            // ����� 6: ��������� ��������� �����
            if (root == NULL) {
                cout << "\n������ ������. ͳ���� ��������.\n";
            }
            else {
                int value;
                cout << "������ �������� ��� ��������� (�� ���� �������� ������): ";
                cin >> value;

                // �������� �� � ����� ��������
                Node* current = root;
                Node* parent = NULL;
                bool found = false;
                bool isLeaf = false;

                // ����� ����� �� ���� ������������ �����
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
                    cout << "\n����� � ��������� " << value << " �� ��������.\n";
                }
                else if (!isLeaf) {
                    cout << "\n����� � ��������� " << value << " �� � ��������.\n";
                }
                else {
                    root = BinarySearchDelete(root, value);
                    cout << "\n�������� ����� ��������. �������� ������:\n";
                    PrintTree(root, 0);
                }
            }
            break;
        }
        case 7: {
            // ����� 7: ��������� ����� � ����� �������
            if (root == NULL) {
                cout << "\n������ ������. ͳ���� ��������.\n";
            }
            else {
                int value;
                cout << "������ �������� ��� ��������� (�� ���� ���� ������ ����������): ";
                cin >> value;

                // �������� �� �� ����� ���� ������ ����������
                Node* current = root;
                Node* parent = NULL;
                bool found = false;
                bool hasOneChild = false;

                // ����� ����� �� ���� ������������ �����
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
                    cout << "\n����� � ��������� " << value << " �� ��������.\n";
                }
                else if (!hasOneChild) {
                    cout << "\n����� � ��������� " << value << " �� �� ���� ������ ����������.\n";
                }
                else {
                    root = BinarySearchDelete(root, value);
                    cout << "\n����� � ����� ������� ��������. �������� ������:\n";
                    PrintTree(root, 0);
                }
            }
            break;
        }
        case 8: {
            // ����� 8: ��������� ����� � ����� ��������
            if (root == NULL) {
                cout << "\n������ ������. ͳ���� ��������.\n";
            }
            else {
                int value;
                cout << "������ �������� ��� ��������� (�� ���� ��� �������): ";
                cin >> value;

                // �������� �� �� ����� ��� �������
                Node* current = root;
                Node* parent = NULL;
                bool found = false;
                bool hasTwoChildren = false;

                // ����� ����� �� ���� ������������ �����
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
                    cout << "\n����� � ��������� " << value << " �� ��������.\n";
                }
                else if (!hasTwoChildren) {
                    cout << "\n����� � ��������� " << value << " �� �� ���� �������.\n";
                }
                else {
                    root = BinarySearchDelete(root, value);
                    cout << "\n����� � ����� �������� ��������. �������� ������:\n";
                    PrintTree(root, 0);
                }
            }
            break;
        }
        case 9: {
            // ����� 9: ��������� ����� � ���� ���� �������� (��������� ��������)
            if (root == NULL) {
                cout << "\n������ ������. ͳ���� ��������.\n";
            }
            else {
                int value;
                cout << "������ �������� (����� �� ��� ���� �������� ���� ��������): ";
                cin >> value;

                // ����� �����
                Node* current = root;
                Node* parent = NULL;
                bool found = false;

                // ����� ����� �� ���� ������������ �����
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
                    cout << "\n����� � ��������� " << value << " �� ��������.\n";
                }
                else {
                    // ���� �� ��������� �����, ��������� ��� ������
                    if (parent == NULL) {
                        DeleteTree(root);
                        root = NULL;
                        cout << "\n��� ������ ��������.\n";
                    }
                    else {
                        // ���� �� ���� �������, ��������� ��� ��������
                        if (parent->left != NULL && parent->left->info == value) {
                            DeleteTree(parent->left);
                            parent->left = NULL;
                        }
                        // ���� �� ������ �������, ��������� ����� ��������
                        else if (parent->right != NULL && parent->right->info == value) {
                            DeleteTree(parent->right);
                            parent->right = NULL;
                        }
                        cout << "\nϳ������� ��������. �������� ������:\n";
                        PrintTree(root, 0);
                    }
                }
            }
            break;
        }
        case 10: {
            // ����� 10: ����������� ������� �������� � ������������ ��������� � ������������ �����
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
        case 0:
            // �������� ���'�� ����� �������
            if (root != NULL) {
                DeleteTree(root);
                root = NULL;
            }
            cout << "�������� ���������.\n";
            break;
        default:
            cout << "������� ����. ��������� �� ���.\n";
        }

    } while (choice != 0);

    return 0;
}