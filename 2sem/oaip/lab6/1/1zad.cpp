#include <iostream>
#include <cstdlib>
#include <climits>
using namespace std;
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};
struct StackNode {
    TreeNode* treeNode;
    int depth;
    StackNode* next;
    StackNode(TreeNode* node, int d) : treeNode(node), depth(d), next(nullptr) {}
};
struct ListNode {
    int value;
    ListNode* next;
    ListNode(int val) : value(val), next(nullptr) {}
};
class Stack {
private:
    StackNode* top;
public:
    Stack() : top(nullptr) {}
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }
    void push(TreeNode* node, int depth) {
        StackNode* newNode = new StackNode(node, depth);
        newNode->next = top;
        top = newNode;
    }
    void pop() {
        if (top == nullptr) return;
        StackNode* temp = top;
        top = top->next;
        delete temp;
    }
    StackNode* peek() {
        return top;
    }
    bool isEmpty() {
        return top == nullptr;
    }
};
class LinkedList {
private:
    ListNode* head;
public:
    LinkedList() : head(nullptr) {}
    ~LinkedList() {
        while (head != nullptr) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void add_to_begin(int value) {
        ListNode* newNode = new ListNode(value);
        newNode->next = head;
        head = newNode;
    }
    void add_to_end(int value) {
        ListNode* newNode = new ListNode(value);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        ListNode* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    void display() {
        if (head == nullptr) {
            cout << "Список пуст." << endl;
            return;
        }
        ListNode* current = head;
        while (current != nullptr) {
            cout << current->value << " ";
            current = current->next;
        }
        cout << endl;
    }
    bool isEmpty() {
        return head == nullptr;
    }
    ListNode* get_head() {
        return head;
    }
};
class BinaryTree {
private:
    TreeNode* root;
    void freeTree(TreeNode* node) {
        if (node == nullptr) return;
        freeTree(node->left);
        freeTree(node->right);
        delete node;
    }
    void inorder(TreeNode* node) {
        if (node == nullptr) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }
    int count_nodes(TreeNode* node) {
        if (node == nullptr) return 0;
        return 1 + count_nodes(node->left) + count_nodes(node->right);
    }
    void collectToArray(TreeNode* node, int* arr, int* index) {
        if (node == nullptr) return;
        collectToArray(node->left, arr, index);
        arr[(*index)++] = node->data;
        collectToArray(node->right, arr, index);
    }
    TreeNode* buildBalancedTree(int* arr, int start, int end) {
        if (start > end) return nullptr;
        int mid = (start + end) / 2;
        TreeNode* node = new TreeNode(arr[mid]);
        node->left = buildBalancedTree(arr, start, mid - 1);
        node->right = buildBalancedTree(arr, mid + 1, end);
        return node;
    }
    TreeNode* findMin(TreeNode* node) {
        while (node->left != nullptr) node = node->left;
        return node;
    }
    TreeNode* deleteNode(TreeNode* node, int key) {
        if (node == nullptr) return nullptr;
        if (key < node->data)
            node->left = deleteNode(node->left, key);
        else if (key > node->data)
            node->right = deleteNode(node->right, key);
        else {
            if (node->left == nullptr) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }
            TreeNode* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }
        return node;
    }
public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree() {
        freeTree(root);
    }
    void createTree() {
        int n, val;
        cout << "Сколько элементов добавить в дерево? ";
        cin >> n;
        for (int i = 0; i < n; i++) {
            cout << "Введите число: ";
            cin >> val;
            insert(val);
        }
        cout << "Дерево создано." << endl;
    }
    void insert(int data) {
        root = insertRec(root, data);
    }
    TreeNode* insertRec(TreeNode* node, int data) {
        if (node == nullptr)
            return new TreeNode(data);
        if (data < node->data)
            node->left = insertRec(node->left, data);
        else if (data > node->data)
            node->right = insertRec(node->right, data);
        return node;
    }
    void display() {
        if (root == nullptr) {
            cout << "Дерево пусто." << endl;
            return;
        }
        cout << "Дерево (симметричный обход): ";
        inorder(root);
        cout << endl;
    }
    int shortest_path_length(int E) {
        if (root == nullptr) return -1;
        Stack stack;
        stack.push(root, 0);
        while (!stack.isEmpty()) {
            StackNode* current = stack.peek();
            stack.pop();
            TreeNode* node = current->treeNode;
            int depth = current->depth;
            delete current;
            if (node->data == E) {
                return depth;
            }
            if (node->right != nullptr)
                stack.push(node->right, depth + 1);
            if (node->left != nullptr)
                stack.push(node->left, depth + 1);
        }
        return -1;
    }
    void demonstrateList() {
        LinkedList myList;
        myList.add_to_end(10);
        myList.add_to_end(20);
        myList.add_to_end(30);
        myList.add_to_begin(5);
        cout << "Список (демонстрация работы со списком): ";
        myList.display();
    }
    void sortTree() {
        if (root == nullptr) {
            cout << "Дерево пусто." << endl;
            return;
        }
        int n = count_nodes(root);
        int* arr = new int[n];
        int index = 0;
        collectToArray(root, arr, &index);
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
        freeTree(root);
        root = buildBalancedTree(arr, 0, n - 1);
        delete[] arr;
        cout << "Дерево упорядочено" << endl;
    }
    void delete_element(int key) {
        if (root == nullptr) {
            cout << "Дерево пусто." << endl;
            return;
        }
        root = deleteNode(root, key);
        cout << "Удаление выполнено (если элемент существовал)." << endl;
    }
    bool isEmpty() {
        return root == nullptr;
    }
};
int main() {
    BinaryTree tree;
    int choice, value, pathLen;
    do {
        cout << "1. Создать дерево" << endl;
        cout << "2. Вывести содержимое дерева" << endl;
        cout << "3. Найти длину пути до элемента E" << endl;
        cout << "4. Работа со списком (демонстрация)" << endl;
        cout << "5. Упорядочить элементы в дереве" << endl;
        cout << "6. Удалить элемент из дерева" << endl;
        cout << "7. Выйти" << endl;
        cout << "Выберите пункт: ";
        cin >> choice;
        switch (choice) {
            case 1:
                tree.createTree();
                break;
            case 2:
                tree.display();
                break;
            case 3:
                if (tree.isEmpty()) {
                    cout << "Дерево пусто. Сначала создайте дерево." << endl;
                } else {
                    cout << "Введите элемент E для поиска: ";
                    cin >> value;
                    pathLen = tree.shortest_path_length(value);
                    if (pathLen == -1)
                        cout << "Элемент " << value << " не найден в дереве." << endl;
                    else
                        cout << "Длина пути от корня до ближайшего элемента " << value << ": " << pathLen << endl;
                }
                break;
            case 4:
                tree.demonstrateList();
                break;
            case 5:
                if (tree.isEmpty()) {
                    cout << "Дерево пусто. Сначала создайте дерево." << endl;
                } else {
                    tree.sortTree();
                }
                break;
            case 6:
                if (tree.isEmpty()) {
                    cout << "Дерево пусто. Сначала создайте дерево." << endl;
                } else {
                    cout << "Введите значение для удаления: ";
                    cin >> value;
                    tree.delete_element(value);
                }
                break;
            case 7:
                cout << "Выход из программы" << endl;
                break;
            default:
                cout << "Неверный выбор" << endl;
        }
    } while (choice != 7);
    return 0;
}