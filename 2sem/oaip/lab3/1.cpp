#include <iostream>
#include <cstring>
#include <initializer_list>
using namespace std;
string user(char* argv[]){
    string result = string(argv[1]) + " " + argv[2];
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
                int get_index(){
                    return index;
                }
                char* get_country(){
                    return country;
                }
                char* get_region(){
                    return region;
                }
                char* get_rayone(){
                    return rayone;
                }
                char* get_city() {
                    return city;
                }
                char* get_street() {
                    return street;
                }
                int get_house() {
                    return house;
                }
                int get_flat() {
                    return flat;
                }
                void set_index(int i){
                    index = i;
                }
                void set_country(const char* c){
                    strcpy(country, c);
                }
                void set_region(const char* r){
                    strcpy(region, r);
                }
                void set_rayone(const char* r){
                    strcpy(rayone, r);
                }
                void set_city(const char* c) { 
                    strcpy(city, c);
                }
                void set_street(const char* s) {
                    strcpy(street, s);
                }
                void set_house(int h) {
                    house = h;
                }
                void set_flat(int f) {
                    flat = f;
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
        adress& get_addr() {
            return addr;
        }
        int get_birth_day() {
            return birth_date.chislo;
        }
        int get_birth_month() {
            return birth_date.mesyats;
        }
        int get_birth_year() {
            return birth_date.god;
        }
        char* get_scnd_name() {
            return scnd_name;
        }
        char* get_name() {
            return name; 
        }
        char* get_surname() {
            return surname;
        }
        void setScnd_name(const char* value) {
            strcpy(scnd_name, value);
        }
        void setName(const char* value) {
            strcpy(name, value); 
        }
        void setSurname(const char* value) { 
            strcpy(surname, value); 
        }
        void set_birth_date(int d, int m, int y) {
            birth_date.chislo = d;
            birth_date.mesyats = m;
            birth_date.god = y;
        }
};
rabotyaga* create_arr(int number_of_rabotyags){
    rabotyaga* arr = new rabotyaga[number_of_rabotyags];
    return arr;
}
void poisk_po_parametru_rabotyagi(rabotyaga* arr, int choice, int number_of_rabotyags){
    char search_str[100];
    int search_int;
    switch(choice) {
        case 1:
            cout << "Введите фамилию для поиска: " << endl;
            cin >> search_str;
            for (int i = 0; i < number_of_rabotyags; i++) {
                if (strcmp(arr[i].get_scnd_name(), search_str) == 0) {
                    cout << "Найден работяга №" << i+1 << endl;
                    cout << "Фамилия: " << arr[i].get_scnd_name() << endl;
                    cout << "Имя: " << arr[i].get_name() << endl;
                }
            }
            break;
        case 2:
            cout << "Введите имя для поиска: ";
            cin >> search_str;
            for (int i = 0; i < number_of_rabotyags; i++) {
                if (strcmp(arr[i].get_name(), search_str) == 0) {
                    cout << "Найден работяга №" << i+1 << endl;
                    cout << "Фамилия: " << arr[i].get_scnd_name() << endl;
                    cout << "Имя: " << arr[i].get_name() << endl;
                }
            }
            break;
        case 3:
            cout << "Введите отчество для поиска: ";
            cin >> search_str;
            for (int i = 0; i < number_of_rabotyags; i++) {
                if (strcmp(arr[i].get_surname(), search_str) == 0) {
                    cout << "Найден работяга №" << i+1 << endl;
                    cout << "Фамилия: " << arr[i].get_scnd_name() << endl;
                    cout << "Имя: " << arr[i].get_name() << endl;
                }
            }
            break;
        case 4:
            cout << "Введите индекс для поиска: " << endl;
            cin >> search_int;
            for (int i = 0; i < number_of_rabotyags; i++) {
                if (arr[i].get_addr().get_index() == search_int ) {
                    cout << "Найден работяга №" << i+1 << endl;
                    cout << "Фамилия: " << arr[i].get_scnd_name() << endl;
                    cout << "Имя: " << arr[i].get_name() << endl;
                    cout << "Индекс: " << arr[i].get_addr().get_index() << endl;
                }
            }
            break;
        case 5:
            cout << "Введите страну для поиска: " << endl;
            cin >> search_str;
            for (int i = 0; i < number_of_rabotyags; i++) {
                if (strcmp(arr[i].get_addr().get_country(), search_str) == 0) {
                    cout << "Найден работяга №" << i+1 << endl;
                    cout << "Фамилия: " << arr[i].get_scnd_name() << endl;
                    cout << "Имя: " << arr[i].get_name() << endl;
                    cout << "Страна: " << arr[i].get_addr().get_country() << endl;
                }
            }
            break;
        case 6:
            cout << "Введите город для поиска: " << endl;
            cin >> search_str;
            for (int i = 0; i < number_of_rabotyags; i++) {
                if (strcmp(arr[i].get_addr().get_city(), search_str) == 0) {
                    cout << "Найден работяга №" << i+1 << endl;
                    cout << "Фамилия: " << arr[i].get_scnd_name() << endl;
                    cout << "Имя: " << arr[i].get_name() << endl;
                    cout << "Город: " << arr[i].get_addr().get_city() << endl;
                }
            }
            break;
        case 7:
            cout << "Введите регион для поиска: " << endl;
            cin >> search_str;
            for (int i = 0; i < number_of_rabotyags; i++) {
                if (strcmp(arr[i].get_addr().get_region(), search_str) == 0) {
                    cout << "Найден работяга №" << i+1 << endl;
                    cout << "Фамилия: " << arr[i].get_scnd_name() << endl;
                    cout << "Имя: " << arr[i].get_name() << endl;
                    cout << "Регион: " << arr[i].get_addr().get_region() << endl;
                }
            }
            break;
        case 8:
            cout << "Введите район для поиска: " << endl;
            cin >> search_str;
            for (int i = 0; i < number_of_rabotyags; i++) {
                if (strcmp(arr[i].get_addr().get_rayone(), search_str) == 0) {
                    cout << "Найден работяга №" << i+1 << endl;
                    cout << "Фамилия: " << arr[i].get_scnd_name() << endl;
                    cout << "Имя: " << arr[i].get_name() << endl;
                    cout << "Район: " << arr[i].get_addr().get_rayone() << endl;
                }
            }
            break;
        case 9:
            cout << "Введите улицу для поиска: " << endl;
            cin >> search_str;
            for (int i = 0; i < number_of_rabotyags; i++) {
                if (strcmp(arr[i].get_addr().get_street(), search_str) == 0) {
                    cout << "Найден работяга №" << i+1 << endl;
                    cout << "Фамилия: " << arr[i].get_scnd_name() << endl;
                    cout << "Имя: " << arr[i].get_name() << endl;
                    cout << "Улица: " << arr[i].get_addr().get_street() << endl;
                }
            }
            break;
        case 10:
            cout << "Введите номер дома для поиска: " << endl;
            cin >> search_int;
            for (int i = 0; i < number_of_rabotyags; i++) {
                if (arr[i].get_addr().get_house() == search_int) {
                    cout << "Найден работяга №" << i+1 << endl;
                    cout << "Фамилия: " << arr[i].get_scnd_name() << endl;
                    cout << "Имя: " << arr[i].get_name() << endl;
                    cout << "Дом: " << arr[i].get_addr().get_house() << endl;
                }
            }
            break;
        case 11:
            cout << "Введите номер квартиры для поиска: " << endl;
            cin >> search_int;
            for (int i = 0; i < number_of_rabotyags; i++) {
                if (arr[i].get_addr().get_flat() == search_int) {
                    cout << "Найден работяга №" << i+1 << endl;
                    cout << "Фамилия: " << arr[i].get_scnd_name() << endl;
                    cout << "Имя: " << arr[i].get_name() << endl;
                    cout << "Квартира: " << arr[i].get_addr().get_flat() << endl;
                }
            }
            break;
    case 12:
        cout << "Введите день рождения для поиска: " << endl;
        cin >> search_int;
        for (int i = 0; i < number_of_rabotyags; i++) {
            if (arr[i].get_birth_day() == search_int) {
                cout << "Найден работяга №" << i+1 << endl;
                cout << "Фамилия: " << arr[i].get_scnd_name() << endl;
                cout << "Имя: " << arr[i].get_name() << endl;
                cout << "День рождения: " << arr[i].get_birth_day() << endl;
            }
        }
        break;
    case 13:
        cout << "Введите месяц рождения для поиска: " << endl;
        cin >> search_int;
        for (int i = 0; i < number_of_rabotyags; i++) {
            if (arr[i].get_birth_month() == search_int) {
                cout << "Найден работяга №" << i+1 << endl;
                cout << "Фамилия: " << arr[i].get_scnd_name() << endl;
                cout << "Имя: " << arr[i].get_name() << endl;
                cout << "Месяц рождения: " << arr[i].get_birth_month() << endl;
            }
        }
        break;
    case 14:
        cout << "Введите год рождения для поиска: " << endl;
        cin >> search_int;
        for (int i = 0; i < number_of_rabotyags; i++) {
            if (arr[i].get_birth_year() == search_int) {
                cout << "Найден работяга №" << i+1 << endl;
                cout << "Фамилия: " << arr[i].get_scnd_name() << endl;
                cout << "Имя: " << arr[i].get_name() << endl;
                cout << "Год рождения: " << arr[i].get_birth_year() << endl;
            }
        }
        break;
    }
}
void dobavit_rabotyag(rabotyaga*& arr, int& number_of_rabotyags, int add = 1){
    int old_count = number_of_rabotyags;
    number_of_rabotyags = number_of_rabotyags + add;
    rabotyaga* temp_arr = create_arr(number_of_rabotyags);
    for (int i = 0; i < old_count; i++){
        temp_arr[i] = arr[i];
    }
    delete[] arr;
    arr = temp_arr;
}
void udaleet_rabotyagu(rabotyaga*& arr, int num, int& number_of_rabotyags, int decrease = 1){
    if (number_of_rabotyags <= decrease) {
        delete[] arr;
        arr = nullptr;
        number_of_rabotyags = 0;
        return;
    }
    rabotyaga* temp_arr = create_arr(number_of_rabotyags - decrease);
    int j = 0;
    for (int i = 0; i < number_of_rabotyags; i++){
        if (i < (num - 1) || i >= (num - 1 + decrease)){
            temp_arr[j] = arr[i];
            j++;
        }
    }
    delete[] arr;
    arr = temp_arr;
    number_of_rabotyags -= decrease;
}
void naznachit_rabotyagu(rabotyaga* arr,int num){
    int index = num - 1;
    char buffer[100];
    cout << "Введите фамилию: ";
    cin >> buffer;
    arr[index].setScnd_name(buffer);
    cout << "Введите имя: ";
    cin >> buffer;
    arr[index].setName(buffer);
    cout << "Введите отчество: ";
    cin >> buffer;
    arr[index].setSurname(buffer);
    int d, m, y;
    cout << "Введите день рождения: ";
    cin >> d;
    cout << "Введите месяц рождения: ";
    cin >> m;
    cout << "Введите год рождения: ";
    cin >> y;
    arr[index].set_birth_date(d, m, y);
    int temp_int;
    cout << "Введите индекс: ";
    cin >> temp_int;
    arr[index].get_addr().set_index(temp_int);
    cout << "Введите страну: ";
    cin >> buffer;
    arr[index].get_addr().set_country(buffer);
    cout << "Введите регион: ";
    cin >> buffer;
    arr[index].get_addr().set_region(buffer);
    cout << "Введите город: ";
    cin >> buffer;
    arr[index].get_addr().set_city(buffer);
    cout << "Введите район: ";
    cin >> buffer;
    arr[index].get_addr().set_rayone(buffer);
    cout << "Введите улицу: ";
    cin >> buffer;
    arr[index].get_addr().set_street(buffer);
    cout << "Введите дом: ";
    cin >> temp_int;
    arr[index].get_addr().set_house(temp_int);
    cout << "Введите квартиру: ";
    cin >> temp_int;
    arr[index].get_addr().set_flat(temp_int);
}
void show_rabotyag(rabotyaga* arr,int number_of_rabotyags){
    for (int i = 0; i<number_of_rabotyags; i++){
        cout << "Номер: " << i+1 << endl << "Фамилия: " << arr[i].get_scnd_name() << endl;
        cout << "Имя: " << arr[i].get_name() << endl << "Отчество: " << arr[i].get_surname() << endl;
        cout << "День Рождения: " << arr[i].get_birth_day() << endl << "Месяц: " << arr[i].get_birth_month() << endl << "Год: " << arr[i].get_birth_year() << endl;
        cout << "Индекс: " << arr[i].get_addr().get_index() << endl << "Страна: " << arr[i].get_addr().get_country() << endl;
        cout << "Регион: " << arr[i].get_addr().get_region() << endl << "Район: " << arr[i].get_addr().get_rayone() << endl;
        cout << "Город: " << arr[i].get_addr().get_city() << endl << "Улица: " << arr[i].get_addr().get_street() << endl;
        cout << "Дом: " << arr[i].get_addr().get_house() << endl << "Квартира: " << arr[i].get_addr().get_flat() << endl;
    }
}
void show_selected_rabotyag(rabotyaga* arr, initializer_list<int> numbers,int number_of_rabotyags) {
    for (int num : numbers) {
        if (num >= 1 && num <= number_of_rabotyags) {
            cout << "Работяга " << num << ": " 
                 << arr[num-1].get_scnd_name() << " "
                 << arr[num-1].get_name() << endl;
        }
    }
}
void sort_rabotyag(rabotyaga* arr, int number_of_rabotyags, int field) {
    for (int i = 0; i < number_of_rabotyags - 1; i++) {
        for (int j = 0; j < number_of_rabotyags - i - 1; j++) {
            bool need_swap = false;
            switch(field) {
                case 1:
                    if (arr[j].get_birth_day() > arr[j+1].get_birth_day())
                        need_swap = true;
                    break;
                case 2:
                    if (arr[j].get_birth_month() > arr[j+1].get_birth_month())
                        need_swap = true;
                    break;
                case 3:
                    if (arr[j].get_birth_year() > arr[j+1].get_birth_year())
                        need_swap = true;
                    break;
                case 4:
                    if (arr[j].get_addr().get_index() > arr[j+1].get_addr().get_index())
                        need_swap = true;
                    break;
                case 5:
                    if (arr[j].get_addr().get_house() > arr[j+1].get_addr().get_house())
                        need_swap = true;
                    break;
                case 6:
                    if (arr[j].get_addr().get_flat() > arr[j+1].get_addr().get_flat())
                        need_swap = true;
                    break;
            }
            if (need_swap) {
                rabotyaga temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}
void apply_criteria(rabotyaga&, bool&) {}
template<typename T, typename... Args>
void apply_criteria(rabotyaga& chel, bool& matches, T criterion, Args... args) {
    if (matches) {
        matches = criterion(chel);
        apply_criteria(chel, matches, args...);
    }
}
template<typename... Criteria>
void multi_search(rabotyaga* arr, int number_of_rabotyags, Criteria... criteria) {
    bool found_any = false;
    for (int i = 0; i < number_of_rabotyags; i++) {
        bool matches = true;
        apply_criteria(arr[i], matches, criteria...);
        if (matches) {
            found_any = true;
            cout << "Работяга №" << i+1 << endl;
            cout << "Фамилия: " << arr[i].get_scnd_name() << endl;
            cout << "Имя: " << arr[i].get_name() << endl;
            cout << "Отчество: " << arr[i].get_surname() << endl;
            cout << "Год рождения: " << arr[i].get_birth_year() << endl;
            cout << "Город: " << arr[i].get_addr().get_city() << endl;
        }
    }
    if (!found_any) {
        cout << "Работяги не найдены" << endl;
    }
}
int main(int argc, char* argv[]) {
    int number_of_rabotyags;
    if (argc >= 3) {
        cout << "Вас зовут: " << user(argv) << endl;
    }
    cout << "Введите количество работяг: ";
    cin >> number_of_rabotyags;
    rabotyaga* arr = create_arr(number_of_rabotyags);

    typedef void (*MenuFunc)(rabotyaga*&, int&);
    
    MenuFunc menu[] = {
        nullptr,
        [](rabotyaga*& arr, int& count) {
            int num;
            cout << "Введите номер работяги (1-" << count << "): ";
            cin >> num;
            if (num >= 1 && num <= count) {
                naznachit_rabotyagu(arr, num);
            } else {
                cout << "Неверный номер!" << endl;
            }
        },
        [](rabotyaga*& arr, int& count) {
            show_rabotyag(arr, count);
        },
        [](rabotyaga*& arr, int& count) {
            int choice;
            cout << "Параметры поиска:" << endl 
                 << "1-Фамилия 2-Имя 3-Отчество 4-Индекс" << endl 
                 << "5-Страна 6-Город 7-Регион 8-Район" << endl
                 << "9-Улица 10-Дом 11-Квартира" << endl
                 << "12-День 13-Месяц 14-Год";
            cout << "Выбор: ";
            cin >> choice;
            poisk_po_parametru_rabotyagi(arr, choice, count);
        },
        [](rabotyaga*& arr, int& count) {
            int add;
            cout << "Сколько добавить? (по умолчанию 1): ";
            cin >> add;
            int old = count;
            if (add == 0) {
                dobavit_rabotyag(arr, count);  // add = 1 по умолчанию
            } else {
                dobavit_rabotyag(arr, count, add);
            }
            for (int i = old; i < count; i++) {
                cout << "\nЗаполните работягу №" << i+1 << ":\n";
                naznachit_rabotyagu(arr, i+1);
            }
        },
        [](rabotyaga*& arr, int& count) {
            int num, dec;
            cout << "Номер для удаления (1-" << count << "): ";
            cin >> num;
            cout << "Сколько удалить? (по умолчанию 1): ";
            cin >> dec;
            if (num >= 1 && num <= count) {
                if (dec == 0) {
                    udaleet_rabotyagu(arr, num, count);
                } else {
                    udaleet_rabotyagu(arr, num, count, dec);
                }
                cout << "Удалено! Осталось: " << count << endl;
            } else {
                cout << "Неверный номер!" << endl;
            }
        },
        [](rabotyaga*& arr, int& count) {
            int n, nums[100];
            cout << "Сколько показать? ";
            cin >> n;
            cout << "Номера: ";
            for (int i = 0; i < n; i++) cin >> nums[i];
            for (int i = 0; i < n; i++) {
                if (nums[i] >= 1 && nums[i] <= count) {
                    cout << nums[i] << ": " << arr[nums[i]-1].get_scnd_name() 
                         << " " << arr[nums[i]-1].get_name() << endl;
                }
            }
        },
        [](rabotyaga*& arr, int& count) {
            int field;
            cout << "Сортировать: 1-День 2-Месяц 3-Год 4-Индекс 5-Дом 6-Квартира: ";
            cin >> field;
            if (field >= 1 && field <= 6) {
                sort_rabotyag(arr, count, field);
                cout << "Готово!" << endl;
            }
        },
    [](rabotyaga*& arr, int& count) {
        int crit_types[10];
        char crit_values[10][50];
        int crit_count = 0;
        int choice;
        cout << "МНОЖЕСТВЕННЫЙ ПОИСК" << endl;
        cout << "Выберите критерии поиска:" << endl;
        cout << "1 - Фамилия" << endl;
        cout << "2 - Имя" << endl;
        cout << "3 - Отчество" << endl;
        cout << "4 - Год рождения" << endl;
        cout << "5 - Город" << endl;
        cout << "6 - Улица" << endl;
        cout << "7 - Индекс" << endl;
        cout << "0 - Завершить выбор и выполнить поиск" << endl;
        while (true) {
            cout << "Введите номер критерия (0 для поиска): ";
            cin >> choice;
            if (choice == 0) break;
            if (choice >= 1 && choice <= 7) {
                crit_types[crit_count] = choice;
                cout << "Введите значение: ";
                cin >> crit_values[crit_count];
                switch(choice) {
                    case 1: cout << "Фамилия"; break;
                    case 2: cout << "Имя"; break;
                    case 3: cout << "Отчество"; break;
                    case 4: cout << "Год рождения"; break;
                    case 5: cout << "Город"; break;
                    case 6: cout << "Улица"; break;
                    case 7: cout << "Индекс"; break;
                }
                cout << " = " << crit_values[crit_count] << endl;
                crit_count++;
            }
        }
        if (crit_count == 0) {
            cout << "Не выбрано ни одного критерия!" << endl;
            return;
        }
        cout << "РЕЗУЛЬТАТЫ ПОИСКА" << endl;
        for (int i = 0; i < count; i++) {
            bool matches_all = true;
            for (int j = 0; j < crit_count; j++) {
                int type = crit_types[j];
                char* value = crit_values[j];
                switch(type) {
                    case 1:
                        if (strcmp(arr[i].get_scnd_name(), value) != 0)
                            matches_all = false;
                        break;
                    case 2:
                        if (strcmp(arr[i].get_name(), value) != 0)
                            matches_all = false;
                        break;
                    case 3:
                        if (strcmp(arr[i].get_surname(), value) != 0)
                            matches_all = false;
                        break;
                    case 4:
                        if (arr[i].get_birth_year() != atoi(value))
                            matches_all = false;
                        break;
                    case 5:
                        if (strcmp(arr[i].get_addr().get_city(), value) != 0)
                            matches_all = false;
                        break;
                    case 6:
                        if (strcmp(arr[i].get_addr().get_street(), value) != 0)
                            matches_all = false;
                        break;
                    case 7:
                        if (arr[i].get_addr().get_index() != atoi(value))
                            matches_all = false;
                        break;
                }
                if (!matches_all) break;
            }
            if (matches_all) {
                cout << "Работяга №" << i+1 << endl;
                cout << "Фамилия: " << arr[i].get_scnd_name() << endl;
                cout << "Имя: " << arr[i].get_name() << endl;
                cout << "Отчество: " << arr[i].get_surname() << endl;
                cout << "Дата рождения: " << arr[i].get_birth_day() << "."
                    << arr[i].get_birth_month() << "."
                    << arr[i].get_birth_year() << endl;
                cout << "Адрес: " << arr[i].get_addr().get_index() << ", "
                    << arr[i].get_addr().get_country() << ", "
                    << arr[i].get_addr().get_city() << ", "
                    << arr[i].get_addr().get_street() << " "
                    << arr[i].get_addr().get_house() << "/"
                    << arr[i].get_addr().get_flat() << endl;
                }
            }
        } 
    };
const int SIZE = sizeof(menu) / sizeof(menu[0]);

    while (true) {
        cout << "МЕНЮ" << endl
             << "1 - Назначить" << endl << "2 - Показать всех " << endl << "3 - Поиск" << endl
             << "4 - Добавить (0 - по умолч. +1)" << endl << "5 - Удалить (0 - по умолч. 1)" << endl
             << "6 - Показать выбранных" << endl << "7 - Сортировка" << endl
             << "8 - Множественный поиск" << endl << "0 - Выход\n> ";
        int c;
        cin >> c;
        if (c >= 1 && c < SIZE) {
            menu[c](arr, number_of_rabotyags);
        }
    }
    delete[] arr;
    return 0;
}