#include <iostream>
#include <cstring>
using namespace std;
string user(char* argv[]){
    char* imya = new char[100];
    strcpy(imya, argv[1]);
    strcat(imya, " ");
    strcat(imya, argv[2]);
    string result = imya;
    delete[] imya;
    return result;
}
struct rabotyaga{
    private:
        char* scnd_name;
        char* name;
        char* surname;
        struct adress{
            private:
                int index;
                char* country;
                char* region;
                char* rayone;
                char* city;
                char* street;
                int house;
                int flat;
            public:
                adress() {
                    index = 0;
                    country = new char[50];
                    region = new char[50];
                    rayone = new char[50];
                    city = new char[50];
                    street = new char[50];
                    strcpy(country, "");
                    strcpy(region, "");
                    strcpy(rayone, "");
                    strcpy(city, "");
                    strcpy(street, "");
                }
                ~adress() {
                    delete[] country;
                    delete[] region;
                    delete[] rayone;
                    delete[] city;
                    delete[] street;
                }
        }addr;
        struct data_stareniya{
            int chislo;
            int mesyats;
            int god;
        }birth_date;
    public:
        rabotyaga() {
            scnd_name = new char[50];
            name = new char[50];
            surname = new char[50];
            strcpy(scnd_name, "");
            strcpy(name, "");
            strcpy(surname, "");
            birth_date.chislo = 0;
            birth_date.mesyats = 0;
            birth_date.god = 0;
        }
        ~rabotyaga() {
            delete[] scnd_name;
            delete[] name;
            delete[] surname;
        }
};
int main(int argc,char* argv[]){
    if (argc >= 3) {
        cout << "вас зовут: " << user(argv) << endl;
    }
    int n;
    cout << "Введите количество работяг ";
    cin >> n; 
    rabotyaga* arr = new rabotyaga[n];
    delete[] arr;
    return 0;
}