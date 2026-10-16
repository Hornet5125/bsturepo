#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
struct StackNode {
    string data;
    StackNode* next;
    StackNode(const string& value) : data(value), next(nullptr) {}
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
    bool isEmpty() const {
        return top == nullptr;
    }
    void push(const string& value) {
        StackNode* newNode = new StackNode(value);
        newNode->next = top;
        top = newNode;
    }
    string pop() {
        if (isEmpty()) {
            return "";
        }
        string value = top->data;
        StackNode* temp = top;
        top = top->next;
        delete temp;
        return value;
    }
};
void createWordsFile(const string& filename, const string words[], int count) {
    ofstream file(filename.c_str());
    if (!file.is_open()) {
        cerr << "Ошибка создания файла " << filename << endl;
        return;
    }
    for (int i = 0; i < count; i++) {
        file << words[i];
        if (i < count - 1) file << " ";
    }
    file.close();
}
void createNumbersFile(const string& filename, const int numbers[], int count) {
    ofstream file(filename.c_str());
    if (!file.is_open()) {
        cerr << "Ошибка создания файла " << filename << endl;
        return;
    }
    for (int i = 0; i < count; i++) {
        file << numbers[i];
        if (i < count - 1) file << " ";
    }
    file.close();
}
void readWordsFromFile(const string& filename, string words[], int& count) {
    ifstream file(filename.c_str());
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла " << filename << endl;
        count = 0;
        return;
    }
    string line;
    getline(file, line);
    file.close();
    stringstream ss(line);
    string word;
    count = 0;
    while (ss >> word) {
        words[count++] = word;
    }
}
void readNumbersFromFile(const string& filename, int numbers[], int& count) {
    ifstream file(filename.c_str());
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла " << filename << endl;
        count = 0;
        return;
    }
    string line;
    getline(file, line);
    file.close();
    stringstream ss(line);
    int number;
    count = 0;
    while (ss >> number) {
        numbers[count++] = number;
    }
}
string intToString(int num) {
    stringstream ss;
    ss << num;
    return ss.str();
}
int main() {
    const int MAX_SIZE = 100;
    const string words[] = {"apple", "banana", "cherry", "date", "elderberry"};
    const int numbers[] = {10, 20, 30, 40, 50};
    int itemCount = 5;
    string wordsFile = "words.txt";
    string numbersFile = "numbers.txt";
    createWordsFile(wordsFile, words, itemCount);
    createNumbersFile(numbersFile, numbers, itemCount);
    cout << "Файлы " << wordsFile << " и " << numbersFile << " созданы." << endl;
    string readWords[MAX_SIZE];
    int readNumbers[MAX_SIZE];
    int wordCount = 0, numberCount = 0;
    readWordsFromFile(wordsFile, readWords, wordCount);
    readNumbersFromFile(numbersFile, readNumbers, numberCount);
    if (wordCount != numberCount) {
        cerr << "Ошибка: количество слов и чисел не совпадает!" << endl;
        return 1;
    }
    cout << "Прочитано слов: " << wordCount << endl;
    cout << "Прочитано чисел: " << numberCount << endl;
    Stack stack;
    for (int i = itemCount - 1; i >= 0; i--) {
        stack.push(readWords[i]);
        stack.push(intToString(readNumbers[i]));
    }
    string resultFile = "result.txt";
    ofstream result(resultFile.c_str());
    
    if (!result.is_open()) {
        cerr << "Ошибка создания файла " << resultFile << endl;
        return 1;
    }
    cout << "Содержимое результирующего файла:" << endl;
    while (!stack.isEmpty()) {
        string element = stack.pop();
        result << element << " ";
        cout << element << " ";
    }
    result.close();
    cout << endl << "Файл " << resultFile << " создан" << endl;
    return 0;
}