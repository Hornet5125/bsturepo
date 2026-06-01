#include <iostream>
#include <fstream>
#include <string>
using namespace std;
bool isRedLine(const string& s) {
    return !s.empty() && (s[0] == ' ' || s[0] == '\t');
}
int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    if (!fin.is_open() || !fout.is_open()) {
        cerr << "Ошибка открытия файлов" << endl;
        return 1;
    }
    string prev, curr;
    bool first = true;
    while (getline(fin, curr)) {
        if (!first && isRedLine(prev) && isRedLine(curr)) {
            fout << endl;
        }
        fout << curr << endl;
        prev = curr;
        first = false;
    }
    fin.close();
    fout.close();
    return 0;
}