#ifndef Personnel_H
#define Personnel_H
#include <iostream>
#include <cstring>
using namespace std;
class Personnel{              // объявляем класс 
    char* name;               // имя
    int workshop_number;      // номер цеха 
    int rank;                 // разряд
    public:                   // поле типа public для описания методов 
    // конструктор без параметров 
    Personnel() : workshop_number(0), rank(0) {
        name = new char[1];
        name[0] = '\0';
        cout << "Конструктор без параметров" << endl;
    }
    // конструктор с параметрами
    Personnel(char* n, int wn, int r) : workshop_number(wn), rank(r) { 
        name = new char[strlen(n) + 1];
        strcpy(name, n);
        cout << "Конструктор с параметрами вызван для объекта "  << this << endl;  
    }
    // конструктор копирования
    Personnel(const Personnel& chel): workshop_number(chel.workshop_number), rank(chel.rank){
        name = new char [strlen(chel.name)+1];
        strcpy(name, chel.name);
        cout << "Конструктор копирования" << endl;
    }
    // деструктор
    ~Personnel(){
        delete[] name;
    }
    // геттеры
    char* GetName();
    int GetWorkshopNumber() const;
    int GetRank();
    // сеттеры
    void SetName(const char* n);
    void SetWorkshopNumber(int wn);
    void SetRank(int r);
    void Set(const char* n, int wn, int r);
    void Show();
};
#endif