#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
struct Node {
    int data;
    Node* next;
};
void addToBeginningFlag(Node*& head, int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = head;
    head = newNode;
    cout << "Элемент " << value << " добавлен в начало списка" << endl;
}
void addToEnd(Node*& head, int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = NULL;
    if (head == NULL) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    cout << "Элемент " << value << " добавлен в конец списка" << endl;
}
void createListByBeginning(Node*& head, int size) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    cout << "Создание списка путем добавления элементов в начало:" << endl;
    for (int i = 0; i < size; i++) {
        int value = rand() % 100;
        addToBeginningFlag(head, value);
    }
    cout << "Список успешно создан!" << endl;
}
void createListByEnd(Node*& head, int size) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    cout << "Создание списка путем добавления элементов в конец:" << endl;
    for (int i = 0; i < size; i++) {
        int value = rand() % 100; // случайное число от 0 до 99
        addToEnd(head, value);
    }
    cout << "Список успешно создан!" << endl;
}
void displayList(Node* head) {
    if (head == NULL) {
        cout << "Список пуст!" << endl;
        return;
    }
    cout << "Содержимое списка: ";
    Node* current = head;
    while (current != NULL) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}
double calculateAverage(Node* head) {
    if (head == NULL) {
        cout << "Ошибка: список пуст!" << endl;
        return 0.0;
    }
    int sum = 0;
    int count = 0;
    Node* current = head;
    while (current != NULL) {
        sum += current->data;
        count++;
        current = current->next;
    }
    return static_cast<double>(sum) / count;
}
void freeList(Node*& head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}
void manualInput(Node*& head, bool toBeginning) {
    int n, value;
    cout << "Сколько элементов вы хотите добавить? ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "Введите элемент " << i + 1 << ": ";
        cin >> value;
        if (toBeginning) {
            addToBeginningFlag(head, value);
        } else {
            addToEnd(head, value);
        }
    }
}
void showMenu() {
    cout << "1. Создать список (добавление в начало)" << endl;
    cout << "2. Создать список (добавление в конец)" << endl;
    cout << "3. Добавить элемент в начало" << endl;
    cout << "4. Добавить элемент в конец" << endl;
    cout << "5. Показать список" << endl;
    cout << "6. Вычислить среднее арифметическое" << endl;
    cout << "7. Ручной ввод элементов (в начало)" << endl;
    cout << "8. Ручной ввод элементов (в конец)" << endl;
    cout << "9. Очистить список" << endl;
    cout << "0. Выход" << endl;
    cout << "Выберите действие: ";
}
int main() {
    srand(time(NULL));
    Node* head = NULL;
    int choice, size;
    do {
        showMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Введите количество элементов для списка: ";
                cin >> size;
                if (size > 0) {
                    createListByBeginning(head, size);
                    displayList(head);
                } else {
                    cout << "Ошибка: размер должен быть положительным!" << endl;
                }
                break;
            case 2:
                cout << "Введите количество элементов для списка: ";
                cin >> size;
                if (size > 0) {
                    createListByEnd(head, size);
                    displayList(head);
                } else {
                    cout << "Ошибка: размер должен быть положительным!" << endl;
                }
                break;
            case 3:
                {
                    int value;
                    cout << "Введите значение для добавления в начало: ";
                    cin >> value;
                    addToBeginningFlag(head, value);
                    displayList(head);
                }
                break;
            case 4:
                {
                    int value;
                    cout << "Введите значение для добавления в конец: ";
                    cin >> value;
                    addToEnd(head, value);
                    displayList(head);
                }
                break;
            case 5:
                displayList(head);
                break;
            case 6:
            {
                 double avg = calculateAverage(head);
                    if (head != NULL) {
                        cout << "Среднее арифметическое элементов списка: " << avg << endl;
                    }
            }
                break;
            case 7:
                manualInput(head, true);
                displayList(head);
                break;
            case 8:
                manualInput(head, false);
                displayList(head);
                break;
            case 9:
                freeList(head);
                cout << "Список очищен" << endl;
                break;
            case 0:
                cout << "Выход из программы" << endl;
                break;
            default:
                cout << "Ошибка неверный выбор" << endl;
                break;
        }
    } while (choice != 0);
    freeList(head);
    return 0;
}