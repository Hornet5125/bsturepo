#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;
int main() {
    string input_filename = "input.txt";
    string output_filename = "output.txt";
    ifstream infile(input_filename);
    if (!infile.is_open()) {
        cerr << "Ошибка не удалось открыть файл " << input_filename << std::endl;
        return 1;
    }
    ofstream outfile(output_filename);
    if (!outfile.is_open()) {
        cerr << "Ошибка не удалось создать файл " << output_filename << std::endl;
        return 1;
    }
    string line;
    while (std::getline(infile, line)) {
        int sum = 0;
        int current_number = 0;
        bool in_number = false;
        bool is_negative = false;
        for (int i = 0; i <= line.length(); i++) {
            char ch = (i < line.length()) ? line[i] : '\0';
            if (i < line.length() && isdigit(ch)) {
                if (!in_number) {
                    in_number = true;
                    current_number = 0;
                    is_negative = false;
                    if (i > 0 && line[i-1] == '-') {
                        is_negative = true;
                    }
                }
                current_number = current_number * 10 + (ch - '0');
            } 
            else {
                if (in_number) {
                    if (is_negative) {
                        current_number = -current_number;
                    }
                    sum += current_number;
                    in_number = false;
                }
            }
        }
        outfile << sum << endl;
    }
    infile.close();
    outfile.close();
    return 0;
}