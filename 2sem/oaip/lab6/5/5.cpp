#include <iostream>
using namespace std;
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};
void RemoveAfterEach(Node*& head, int E) {
    if (head == nullptr) return;
    Node* current = head;
    while (current != nullptr) {
        if (current->data == E && current->next != nullptr) {
            if (current->next->data != E) {
                Node* toDelete = current->next;
                current->next = current->next->next;
                delete toDelete;
            }
        }
        current = current->next;
    }
}
void Append(Node*& head, int value) {
    Node* newNode = new Node(value);
    if (head == nullptr) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
}
void PrintList(Node* head) {
    if (head == nullptr) {
        cout << "Список пуст" << endl;
        return;
    }
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}
void ClearList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}
int main() {
    setlocale(LC_ALL, "Russian");
    Node* head = nullptr;
    int arr[] = {1, 2, 3, 2, 4, 2, 5, 2, 6};
    for (int i = 0; i < 9; i++) {
        Append(head, arr[i]);
    }
    cout << "Исходный список: ";
    PrintList(head);
    int E;
    cout << "Введите элемент E: ";
    cin >> E;
    RemoveAfterEach(head, E);
    cout << "Список после удаления: ";
    PrintList(head);
    ClearList(head);
    return 0;
}