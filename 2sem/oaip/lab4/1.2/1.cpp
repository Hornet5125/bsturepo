#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;
typedef void (*MenuFunc)();
int* arr = nullptr;
int arrsize = 0;
int search_with_barrier(int* arr, int n, int key) {
    if (n == 0){
         return -1;
    }
    int last = arr[n - 1];
    arr[n - 1] = key;
    int i = 0;
    while (arr[i] != key) {
        i++;
    }
    arr[n - 1] = last;
    if (i < n - 1 || arr[n - 1] == key) {
        return i;
    }
    return -1;
}
void menu_search_with_barrier() {
    cout << "Текущий массив: ";
    for (int i = 0; i < arrsize; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    int key;
    cout << "Введите элемент для поиска: ";
    cin >> key;
    int* temp_arr = new int[arrsize];
    for (int i = 0; i < arrsize; i++) {
        temp_arr[i] = arr[i];
    }
    int index = search_with_barrier(temp_arr, arrsize, key);
    cout << "Позиция искомого элемента: " << index;
    delete[] temp_arr;
}
void heapify(int* arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}
void heap_sort(int* arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
void menu_input_manual() {
    if (arr != nullptr) {
        delete[] arr;
        arr = nullptr;
    }
    cout << "Введите размер массива: ";
    cin >> arrsize;
    arr = new int[arrsize];
    cout << "Введите массив: ";
    for (int i = 0; i < arrsize; i++) {
        cin >> arr[i];
    }
}
void menu_input_random() {
    cout << "Введите размер массива: ";
    cin >> arrsize;
    arr = new int[arrsize];
    srand(time(nullptr));
    for (int i = 0; i < arrsize; i++) {
        arr[i] = rand() % 100;
    }
    cout << "Сгенерирован массив: ";
    for (int i = 0; i < arrsize; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
void menu_input_from_file() {
    string filename;
    cout << "Введите имя файла: ";
    cin >> filename;
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл " << filename << endl;
        return;
    }
    if (arr != nullptr) {
        delete[] arr;
        arr = nullptr;
    }
    file >> arrsize;
    arr = new int[arrsize];
    for (int i = 0; i < arrsize; i++) {
        file >> arr[i];
    }
    file.close();
    cout << "Массив: ";
    for (int i = 0; i < arrsize; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
void menu_display_array() {
    cout << "Текущий массив: " << endl;
    for (int i = 0; i < arrsize; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
void menu_heap_sort() {
    cout << "Исходный массив: ";
    for (int i = 0; i < arrsize; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    heap_sort(arr, arrsize);
    cout << "Отсортированный массив: ";
    for (int i = 0; i < arrsize; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
void menu_save_to_file() {
    string filename;
    cout << "Введите имя файла для сохранения: ";
    cin >> filename;
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка: не удалось создать файл " << filename << endl;
        return;
    }
    file << arrsize << endl;
    for (int i = 0; i < arrsize; i++) {
        file << arr[i] << " ";
    }
    file << endl;
    file.close();
}
void menu_exit() {
    if (arr != nullptr) {
        delete[] arr;
        arr = nullptr;
    }
    exit(0);
}
MenuFunc menuFunctions[] = {
    menu_input_manual,
    menu_input_random,
    menu_input_from_file,
    menu_display_array,
    menu_heap_sort,
    menu_save_to_file,
    menu_search_with_barrier,
    menu_exit
};
const char* menuNames[] = {
    "Ввод массива вручную",
    "Генерация случайного массива",
    "Загрузка массива из файла",
    "Вывод массива",
    "Пирамидальная сортировка",
    "Сохранить массив в файл",
    "Поиск с барьером",
    "Выход"
};
const int menu_size = 8;
void print_menu() {
    cout << "Пирамидальная сортировка" << endl;
    for (int i = 0; i < menu_size; i++) {
        cout << "  " << i + 1 << ". " << menuNames[i] << endl;
    }
    cout << "Выберите пункт меню: ";
}
int main() {
    while (true) {
        print_menu();
        int choice;
        cin >> choice;
        if (choice >= 1 && choice <= menu_size) {
            menuFunctions[choice - 1]();
        } else {
            return 0;
        }
    }
    return 0;
}