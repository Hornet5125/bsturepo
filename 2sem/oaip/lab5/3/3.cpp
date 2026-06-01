#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
float** FreeMemory(unsigned n, unsigned m) {
    float** matrix = new float*[n];
    for (unsigned i = 0; i < n; i++) {
        matrix[i] = new float[m];
    }
    return matrix;
}
void FreeMatrix(float** matrix, unsigned n) {
    for (unsigned i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}
void InitMatrix(float** matrix, unsigned n, unsigned m) {
    for (unsigned i = 0; i < n; i++) {
        for (unsigned j = 0; j < m; j++) {
            matrix[i][j] = (float)(rand() % 20 - 10);
        }
    }
}
void DisplayMatrix(float** matrix, unsigned n, unsigned m) {
    for (unsigned i = 0; i < n; i++) {
        for (unsigned j = 0; j < m; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}
void WriteMatrixToFile(ofstream& file, float** matrix, unsigned n, unsigned m) {
    for (unsigned i = 0; i < n; i++) {
        for (unsigned j = 0; j < m; j++) {
            file.write((char*)&matrix[i][j], sizeof(float));
        }
    }
}
void ReadMatrixFromFile(ifstream& file, float** matrix, unsigned n, unsigned m) {
    for (unsigned i = 0; i < n; i++) {
        for (unsigned j = 0; j < m; j++) {
            file.read((char*)&matrix[i][j], sizeof(float));
        }
    }
}
void CreateFile(char* filename, unsigned count, unsigned n, unsigned m) {
    ofstream file(filename, ios::binary);
    if (!file) {
        cout << "Error creating file!" << endl;
        return;
    }
    for (unsigned k = 0; k < count; k++) {
        float** matrix = FreeMemory(n, m);
        InitMatrix(matrix, n, m);
        WriteMatrixToFile(file, matrix, n, m);
        FreeMatrix(matrix, n);
    }
    file.close();
}
void DisplayFile(char* filename, unsigned n, unsigned m) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }
    file.seekg(0, ios::end);
    long size = file.tellg();
    unsigned matrixSize = n * m * sizeof(float);
    unsigned count = size / matrixSize;
    file.seekg(0, ios::beg);
    for (unsigned k = 0; k < count; k++) {
        float** matrix = FreeMemory(n, m);
        ReadMatrixFromFile(file, matrix, n, m);
        cout << "Matrix " << k + 1 << ":" << endl;
        DisplayMatrix(matrix, n, m);
        FreeMatrix(matrix, n);
    }
    file.close();
}
void ProcessAndTransfer(char* file1, char* file2, unsigned n, unsigned m) {
    ifstream f1(file1, ios::binary);
    if (!f1) {
        cout << "Error opening first file!" << endl;
        return;
    }
    f1.seekg(0, ios::end);
    long size1 = f1.tellg();
    unsigned matrixSize = n * m * sizeof(float);
    unsigned count1 = size1 / matrixSize;
    f1.seekg(0, ios::beg);
    float*** matrices1 = new float**[count1];
    bool* transfer = new bool[count1];
    for (unsigned k = 0; k < count1; k++) {
        matrices1[k] = FreeMemory(n, m);
        ReadMatrixFromFile(f1, matrices1[k], n, m);
        transfer[k] = (matrices1[k][0][0] == 0);
    }
    f1.close();
    ifstream f2(file2, ios::binary);
    if (!f2) {
        cout << "Error opening second file!" << endl;
        delete[] transfer;
        for (unsigned k = 0; k < count1; k++) {
            FreeMatrix(matrices1[k], n);
        }
        delete[] matrices1;
        return;
    }
    f2.seekg(0, ios::end);
    long size2 = f2.tellg();
    unsigned count2 = size2 / matrixSize;
    f2.seekg(0, ios::beg);
    float*** matrices2 = new float**[count2];
    for (unsigned k = 0; k < count2; k++) {
        matrices2[k] = FreeMemory(n, m);
        ReadMatrixFromFile(f2, matrices2[k], n, m);
    }
    f2.close();
    ofstream f1out(file1, ios::binary);
    ofstream f2out(file2, ios::binary);
    unsigned transferred = 0;
    for (unsigned k = 0; k < count1; k++) {
        if (!transfer[k]) {
            WriteMatrixToFile(f1out, matrices1[k], n, m);
        } else {
            transferred++;
        }
    }
    for (unsigned k = 0; k < count2; k++) {
        WriteMatrixToFile(f2out, matrices2[k], n, m);
    }
    for (unsigned k = 0; k < count1; k++) {
        if (transfer[k]) {
            WriteMatrixToFile(f2out, matrices1[k], n, m);
        }
    }
    f1out.close();
    f2out.close();
    for (unsigned k = 0; k < count1; k++) {
        FreeMatrix(matrices1[k], n);
    }
    delete[] matrices1;
    delete[] transfer;
    for (unsigned k = 0; k < count2; k++) {
        FreeMatrix(matrices2[k], n);
    }
    delete[] matrices2;
}
int main() {
    unsigned k, l, n, m;
    cout << "Введите количество матриц в первом файле (k): ";
    cin >> k;
    cout << "Введите количество матриц во втором файле (l): ";
    cin >> l;
    cout << "Введите размерность матриц (n m): ";
    cin >> n >> m;
    char file1[] = "matrices1.dat";
    char file2[] = "matrices2.dat";
    CreateFile(file1, k, n, m);
    CreateFile(file2, l, n, m);
    cout << "Первый файл до преобразования" << endl;
    DisplayFile(file1, n, m);
    cout << "Второй файл до преобразования" << endl;
    DisplayFile(file2, n, m);
    ProcessAndTransfer(file1, file2, n, m);
    cout << "Первый файл после преобразования" << endl;
    DisplayFile(file1, n, m);
    cout << "Второй файл после преобразования" << endl;
    DisplayFile(file2, n, m);
    return 0;
}