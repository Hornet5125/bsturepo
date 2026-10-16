#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
struct CarOwner {
    char last_name[50];
    char first_name[50];
    char middle_name[50];
    char phone[20];
    char address[200];
    char car_brand[50];
    char car_number[15];
    char tech_passport[20];
};
void init_file(const char* file_name, long n);
void display_file(const char* file_name);
void add_to_file_end(const char* file_name, long n);
void erase_element_by_position(const char* file_name, long position);
void erase_element_by_key(const char* file_name, const char* key);
void sort_file_by_selection(const char* file_name, int field_type);
void display_person(const CarOwner& person);
CarOwner input_person();
int compare_by_field(const CarOwner& a, const CarOwner& b, int field_type);
const int BY_LAST_NAME = 1;
const int BY_CAR_BRAND = 2;
const int BY_CAR_NUMBER = 3;
CarOwner input_person() {
    CarOwner person;
    cout << "Введите фамилию: ";
    cin.getline(person.last_name, 50);
    cout << "Введите имя: ";
    cin.getline(person.first_name, 50);
    cout << "Введите отчество: ";
    cin.getline(person.middle_name, 50);
    cout << "Введите номер телефона: ";
    cin.getline(person.phone, 20);
    cout << "Введите домашний адрес: ";
    cin.getline(person.address, 200);
    cout << "Введите марку автомобиля: ";
    cin.getline(person.car_brand, 50);
    cout << "Введите номер автомобиля: ";
    cin.getline(person.car_number, 15);
    cout << "Введите номер техпаспорта: ";
    cin.getline(person.tech_passport, 20);
    return person;
}
void display_person(const CarOwner& person) {
    cout << "Фамилия: " << person.last_name << endl;
    cout << "Имя: " << person.first_name << endl;
    cout << "Отчество: " << person.middle_name << endl;
    cout << "Телефон: " << person.phone << endl;
    cout << "Адрес: " << person.address << endl;
    cout << "Марка авто: " << person.car_brand << endl;
    cout << "Номер авто: " << person.car_number << endl;
    cout << "Техпаспорт: " << person.tech_passport << endl;
}
void init_file(const char* file_name, long n) {
    ofstream file(file_name, ios::binary);
    if (!file) {
        cerr << "Ошибка создания файла!" << endl;
        return;
    }
    for (long i = 0; i < n; i++) {
        cout << "Ввод данных владельца " << i + 1 << endl;
        CarOwner person = input_person();
        file.write(reinterpret_cast<char*>(&person), sizeof(CarOwner));
    }
    file.close();
}
void add_to_file_end(const char* file_name, long n) {
    ofstream file(file_name, ios::binary | ios::app);
    if (!file) {
        cerr << "Ошибка открытия файла!" << endl;
        return;
    }
    for (long i = 0; i < n; i++) {
        cout << "Добавление владельца " << i + 1 << endl;
        CarOwner person = input_person();
        file.write(reinterpret_cast<char*>(&person), sizeof(CarOwner));
    }
    file.close();
}
void display_file(const char* file_name) {
    ifstream file(file_name, ios::binary);
    if (!file) {
        cerr << "Ошибка открытия файла!" << endl;
        return;
    }
    CarOwner person;
    long count = 0;
    while (file.read(reinterpret_cast<char*>(&person), sizeof(CarOwner))) {
        cout << "Запись №" << ++count;
        display_person(person);
    }
    if (count == 0) {
        cout << "Файл пуст." << endl;
    } else {
        cout << "Всего записей: " << count << endl;
    }
    file.close();
}
void erase_element_by_position(const char* file_name, long position) {
    ifstream inFile(file_name, ios::binary);
    if (!inFile) {
        cerr << "Ошибка открытия файла!" << endl;
        return;
    }
    inFile.seekg(0, ios::end);
    long file_size = inFile.tellg();
    long recordCount = file_size / sizeof(CarOwner);
    inFile.seekg(0, ios::beg);
    if (position < 1 || position > recordCount) {
        cerr << "Неверный номер позиции!" << endl;
        inFile.close();
        return;
    }
    const char* tempFile = "temp.dat";
    ofstream outFile(tempFile, ios::binary);
    CarOwner person;
    long currentPos = 1;
    while (inFile.read(reinterpret_cast<char*>(&person), sizeof(CarOwner))) {
        if (currentPos != position) {
            outFile.write(reinterpret_cast<char*>(&person), sizeof(CarOwner));
        }
        currentPos++;
    }
    inFile.close();
    outFile.close();
    remove(file_name);
    rename(tempFile, file_name);
    cout << "Запись с номером " << position << " успешно удалена." << endl;
}
void erase_element_by_key(const char* file_name, const char* key) {
    ifstream inFile(file_name, ios::binary);
    if (!inFile) {
        cerr << "Ошибка открытия файла!" << endl;
        return;
    }
    const char* tempFile = "temp.dat";
    ofstream outFile(tempFile, ios::binary);
    CarOwner person;
    bool found = false;
    int deletedCount = 0;
    while (inFile.read(reinterpret_cast<char*>(&person), sizeof(CarOwner))) {
        if (strcmp(person.last_name, key) != 0) {
            outFile.write(reinterpret_cast<char*>(&person), sizeof(CarOwner));
        } else {
            found = true;
            deletedCount++;
            cout << "Удалена запись: " << person.last_name << " " 
                 << person.first_name << " " << person.middle_name << endl;
        }
    }
    inFile.close();
    outFile.close();
    if (found) {
        remove(file_name);
        rename(tempFile, file_name);
        cout << "Удалено записей: " << deletedCount << endl;
    } else {
        remove(tempFile);
        cout << "Запись с фамилией " << key << " не найдена." << endl;
    }
}
int compare_by_field(const CarOwner& a, const CarOwner& b, int field_type) {
    switch (field_type) {
        case BY_LAST_NAME:
            return strcmp(a.last_name, b.last_name);
        case BY_CAR_BRAND:
            return strcmp(a.car_brand, b.car_brand);
        case BY_CAR_NUMBER:
            return strcmp(a.car_number, b.car_number);
        default:
            return 0;
    }
}
void sort_file_by_selection(const char* file_name, int field_type) {
    ifstream inFile(file_name, ios::binary);
    if (!inFile) {
        cerr << "Ошибка открытия файла!" << endl;
        return;
    }
    inFile.seekg(0, ios::end);
    long fileSize = inFile.tellg();
    long recordCount = fileSize / sizeof(CarOwner);
    inFile.seekg(0, ios::beg);
    if (recordCount == 0) {
        cout << "Файл пуст, сортировка не требуется." << endl;
        inFile.close();
        return;
    }
    CarOwner* arr = new CarOwner[recordCount];
    for (long i = 0; i < recordCount; i++) {
        inFile.read(reinterpret_cast<char*>(&arr[i]), sizeof(CarOwner));
    }
    inFile.close();
    for (long i = 0; i < recordCount - 1; i++) {
        long minIndex = i;
        for (long j = i + 1; j < recordCount; j++) {
            if (compare_by_field(arr[j], arr[minIndex], field_type) < 0) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            CarOwner temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
    ofstream outFile(file_name, ios::binary);
    for (long i = 0; i < recordCount; i++) {
        outFile.write(reinterpret_cast<char*>(&arr[i]), sizeof(CarOwner));
    }
    outFile.close();
    delete[] arr;
    const char* field_name = "";
    switch (field_type) {
        case BY_LAST_NAME: field_name = "фамилии"; break;
        case BY_CAR_BRAND: field_name = "марке автомобиля"; break;
        case BY_CAR_NUMBER: field_name = "номеру автомобиля"; break;
    }
    cout << "Файл отсортирован по " << field_name << " методом выбора" << endl;
}
int main() {
    const char* file_name = "car_owners.dat";
    int choice;
    long n, position;
    char key[50];
    int field_type;
    void (*menuFunctions[7])() = {NULL};
    do {
        cout << "1. Создание файла" << endl;
        cout << "2. Добавление элемента в конец файла" << endl;
        cout << "3. Вывод содержимого файла" << endl;
        cout << "4. Удаление элемента с заданным номером" << endl;
        cout << "5. Удаление элемента с заданной фамилией" << endl;
        cout << "6. Сортировка файла (выбором)" << endl;
        cout << "0. Выход" << endl;
        cout << "Ваш выбор: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1:
                cout << "Сколько записей создать? ";
                cin >> n;
                init_file(file_name, n);
                break;
            case 2:
                cout << "Сколько записей добавить? ";
                cin >> n;
                add_to_file_end(file_name, n);
                break;
            case 3:
                display_file(file_name);
                break;
            case 4:
                cout << "Введите номер удаляемой записи: ";
                cin >> position;
                erase_element_by_position(file_name, position);
                break;
            case 5:
                cout << "Введите фамилию для удаления: ";
                cin.getline(key, 50);
                erase_element_by_key(file_name, key);
                break;
            case 6:
                cout << "Сортировка по:" << endl;
                cout << "1 - фамилии" << endl;
                cout << "2 - марке автомобиля" << endl;
                cout << "3 - номеру автомобиля" << endl;
                cout << "Ваш выбор: ";
                cin >> field_type;
                sort_file_by_selection(file_name, field_type);
                break;
            case 0:
                cout << "До свидания!" << endl;
                break;
            default:
                cout << "Неверный выбор! Попробуйте снова." << endl;
        }
    } while (choice != 0);
    return 0;
}