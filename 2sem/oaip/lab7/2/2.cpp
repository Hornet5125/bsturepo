#include <iostream>
using namespace std;
struct Node {
    double data;
    Node* left;
    Node* right;
    Node(double val) : data(val), left(nullptr), right(nullptr) {}
};
Node* insert(Node* root, double val) {
    if (root == nullptr) {
        return new Node(val);
    }
    if (val < root->data) {
        root->left = insert(root->left, val);
    } else if (val > root->data) {
        root->right = insert(root->right, val);
    }
    return root;
}
struct QueueNode {
    Node* treeNode;
    int level;
};
class Queue {
private:
    QueueNode* arr;
    int capacity;
    int frontIdx;
    int rearIdx;
    int count;
public:
    Queue(int size) {
        capacity = size;
        arr = new QueueNode[size];
        frontIdx = 0;
        rearIdx = -1;
        count = 0;
    }
    ~Queue() {
        delete[] arr;
    }
    void push(Node* node, int level) {
        if (count == capacity) return;
        rearIdx = (rearIdx + 1) % capacity;
        arr[rearIdx].treeNode = node;
        arr[rearIdx].level = level;
        count++;
    }
    void pop() {
        if (count == 0) return;
        frontIdx = (frontIdx + 1) % capacity;
        count--;
    }
    QueueNode front() {
        return arr[frontIdx];
    }
    bool empty() {
        return count == 0;
    }
};
void countLevels(Node* root) {
    if (root == nullptr) {
        cout << "Дерево пустое" << endl;
        return;
    }
    Queue q(100);
    q.push(root, 0);
    int currentLevel = 0;
    int countOnLevel = 0;
    cout << "Количество элементов на уровнях:" << endl;
    while (!q.empty()) {
        QueueNode qNode = q.front();
        q.pop();
        Node* current = qNode.treeNode;
        int level = qNode.level;  
        if (level > currentLevel) {
            cout << "Уровень " << currentLevel << ": " << countOnLevel << " элементов" << endl;
            currentLevel = level;
            countOnLevel = 1;
        } else {
            countOnLevel++;
        }
        if (current->left) q.push(current->left, level + 1);
        if (current->right) q.push(current->right, level + 1);
    }
    cout << "Уровень " << currentLevel << ": " << countOnLevel << " элементов" << endl;
}
Node* findMin(Node* root) {
    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}
Node* deleteNode(Node* root, double key) {
    if (root == nullptr) return nullptr;
    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } 
    else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } 
    else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } 
        else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* minNode = findMin(root->right);
        root->data = minNode->data;
        root->right = deleteNode(root->right, minNode->data);
    }
    return root;
}
void inorderPrint(Node* root) {
    if (root == nullptr) return;
    inorderPrint(root->left);
    cout << root->data << " ";
    inorderPrint(root->right);
}
void deleteTree(Node* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}
int main() {
    Node* root = nullptr;
    int n;
    double value;
    cout << "Введите количество элементов: ";
    cin >> n;
    cout << "Введите " << n << " вещественных чисел: ";
    for (int i = 0; i < n; i++) {
        cin >> value;
        root = insert(root, value);
    }
    cout << "Дерево: ";
    inorderPrint(root);
    cout << endl;
    countLevels(root);
    int m;
    cout << "Введите количество элементов для удаления: ";
    cin >> m;
    for (int i = 0; i < m; i++) {
        cout << "Введите значение для удаления: ";
        cin >> value;
        root = deleteNode(root, value);
        cout << "После удаления " << value << ": ";
        inorderPrint(root);
        cout << endl;
    }
    cout << "Итоговое дерево:" << endl;
    countLevels(root);
    deleteTree(root);
    return 0;
}