#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main() {
    string filename;
    int K;
    cout << "Введите имя файла: ";
    cin >> filename;
    cout << "Введите номер строки K: ";
    cin >> K;
    ifstream fin(filename);
    if (!fin) {
        cout << "Ошибка: файл не найден!" << endl;
        return 1;
    }
    ofstream fout("temp.txt");
    string line;
    int currentLine = 1;
    bool lineExists = false;
    while (getline(fin, line)) {
        fout << line << endl;
        if (currentLine == K) {
            fout << endl;
            lineExists = true;
        }
        currentLine++;
    }
    fin.close();
    fout.close();
    if (!lineExists) {
        remove("temp.txt");
        return 0;
    }
    remove(filename.c_str());
    rename("temp.txt", filename.c_str());
    cout << "Пустая строка вставлена после строки " << K << endl;
    return 0;
}