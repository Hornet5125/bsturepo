#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;
void createFile(const char* filename, int count) {
    ofstream outFile(filename);
    if (!outFile) return;
    srand(time(0));
    for (int i = 0; i < count; i++) {
        outFile << (rand() % 100) << " ";
    }
    outFile.close();
}
int* readFileToArray(const char* filename, int& size) {
    ifstream inFile(filename);
    if (!inFile) return nullptr;
    int* arr = new int[1000];
    size = 0;
    while (inFile >> arr[size]) {
        size++;
    }
    inFile.close();
    return arr;
}
int calculateSum(int* arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}
void addSumToArray(int*& arr, int& size, int sum) {
    int* newArr = new int[size + 1];
    for (int i = 0; i < size; i++) {
        newArr[i] = arr[i];
    }
    newArr[size] = sum;
    delete[] arr;
    arr = newArr;
    size++;
}
void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
int main() {
    const char* filename = "numbers.txt";
    int size = 0;
    createFile(filename, 10);
    int* numbers = readFileToArray(filename, size);
    if (numbers == nullptr) {
        cout << "Error reading file" << endl;
        return 1;
    }
    cout << "оригинальный массив: ";
    printArray(numbers, size);
    int sum = calculateSum(numbers, size);
    addSumToArray(numbers, size, sum);
    cout << "массив с суммой: ";
    printArray(numbers, size);
    delete[] numbers;
    return 0;
}