#include "heading.h"
char* Personnel::GetName(){
    return name;
}
int Personnel::GetWorkshopNumber(){
    return workshop_number;
}
int Personnel::GetRank() {
    return rank;
}
void Personnel::SetName(const char* n) {
    delete[] name;
    name = new char[strlen(n) + 1];
    strcpy(name, n);
}
void Personnel::SetWorkshopNumber(int wn) {
    workshop_number = wn;
}
void Personnel::SetRank(int r) {
    rank = r;
}
void Personnel::Set(const char* n, int wn, int r) {
    SetName(n);
    workshop_number = wn;
    rank = r;
}
void Personnel::Show() {
    cout << name << workshop_number << rank << endl;
}