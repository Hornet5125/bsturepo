#include <iostream>
#include <string>
#include <cstring>
using namespace::std;
int main(){
    int x;
    int n;
    int i;
    int time;
    int y;
    int temporary;
    int element;
    char stanciya[50];
    cout << "Введите кол-во поездов: ";
    cin >> n;
    enum time_of_arrival {
            time0= 0,
            time1= 1,
            time2= 2,
            time3= 3,
            time4 = 4, 
            time5 = 5, 
            time6 = 6,
            time7= 7,
            time8= 8,
            time9= 9,
            time10= 10,
            time11 = 11, 
            time12 = 12, 
            time13 = 13,
            time14= 14,
            time15= 15,
            time16= 16,
            time17= 17,
            time18 = 18, 
            time19 = 19, 
            time20 = 20,
            time21= 21,
            time22= 22,
            time23= 23,
            time24 = 24
        };
    struct train_schedule{
        int number;
        char station[50];
        time_of_arrival arrival_time;
        int traveldays;
        int timetostay_mins;
    }temp;
    train_schedule* arr = new train_schedule[n+1];
    while (int inf = 1 == 1){
        cout << "1) Ввод массива структур" << endl;
        cout << "2) Сортировка массива структур" << endl;
        cout << "3) Поиск в массиве структур по заданному параметру" << endl;
        cout << "4) Изменение заданной структуры" << endl;
        cout << "5) Удаление структуры из массива" << endl;
        cout << "6) Вывод на экран массива структур" << endl;
        cout << "7) Выход." << endl;
        cout << "Введите x: ";
        cin >> x;
        switch(x){
            case 1:
                for (int i = 0; i<n; i++){
                    cin >> arr[i].number >> arr[i].station >> arr[i].traveldays;
                    cin >> time; 
                    cin >> arr[i].timetostay_mins;
                    arr[i].arrival_time = static_cast<time_of_arrival>(time);
                }
                break;
            case 2:
                for (int i = 0; i < n - 1; i++) {
                    for (int j = 0; j < n - i - 1; j++) {
                        if (arr[j].number > arr[j + 1].number){
                            temp = arr[j];
                            arr[j] = arr[j + 1];
                            arr[j + 1] = temp;
                        }
                    }
                }
                break;
            case 3: 
                cout << "Выберите параметр: " << endl;
                cout << " 1) Номер" << endl;
                cout << " 2) Станция" << endl;
                cout << " 3) Время прибытия" << endl;
                cout << " 4) Дни в пути" << endl; 
                cout << " 5) Время стоянки" << endl;
                cout << " 6) Выход" << endl;
                cin >> y;
                switch (y) {
                    case 1 : 
                        cout << "Введите номер поезда  " << endl;
                        cin >> temporary;
                        for (int i = 0; i<n;i++){
                            if (temporary==arr[i].number){
                                cout << "Номер " << arr[i].number << endl << "Станция " << arr[i].station << 
                                endl << "Время прибытия " << arr[i].arrival_time << endl << "Время в пути " << arr[i].traveldays << endl <<
                                "Время стоянок " << arr[i].timetostay_mins
                                << endl;
                            } 
                            else break;
                        }
                        break;
                    case 2 :
                        cout << "Введите станцию " << endl;
                        cin >> stanciya;
                        for (int i = 0; i<n;i++){
                            if (stanciya==arr[i].station){
                                cout << "Номер " << arr[i].number << endl << "Станция " << arr[i].station << 
                                endl << "Время прибытия " << arr[i].arrival_time << endl << "Время в пути " << arr[i].traveldays << endl <<
                                "Время стоянок " << arr[i].timetostay_mins
                                << endl;
                            } 
                            else break;
                        }
                        break;
                    case 3 :
                        cout << "Введите прибытия " << endl;
                        cin >> temporary;
                        for (int i = 0; i<n;i++){
                            if (temporary==arr[i].arrival_time){
                                cout << "Номер " << arr[i].number << endl << "Станция " << arr[i].station << 
                                endl << "Время прибытия " << arr[i].arrival_time << endl << "Время в пути " << arr[i].traveldays << endl <<
                                "Время стоянок " << arr[i].timetostay_mins
                                << endl;
                            } 
                            else break;
                        }
                        break;
                    case 4 :
                        cout << "Введите время в пути " << endl;
                        cin >> temporary;
                        for (int i = 0; i<n;i++){
                            if (temporary==arr[i].traveldays){
                                cout << "Номер " << arr[i].number << endl << "Станция " << arr[i].station << 
                                endl << "Время прибытия " << arr[i].arrival_time << endl << "Время в пути " << arr[i].traveldays << endl <<
                                "Время стоянок " << arr[i].timetostay_mins
                                << endl;
                            } 
                            else break;
                        }
                        break;
                    case 5 :
                        cout << "Введите время стоянки " << endl;
                        cin >> temporary;
                        for (int i = 0; i<n;i++){
                            if (temporary==arr[i].timetostay_mins){
                                cout << "Номер " << arr[i].number << endl << "Станция " << arr[i].station << 
                                endl << "Время прибытия " << arr[i].arrival_time << endl << "Время в пути " << arr[i].traveldays << endl <<
                                "Время стоянок " << arr[i].timetostay_mins
                                << endl;
                            } 
                            else break;
                        }
                        break;
                    case 6 :
                        break;
                    }
                break;
            case 4:
                cout << "Введите номер поезда " << endl;
                cin >> temporary;
                for (int i = 0; i<n; i++){
                    if (temporary == arr[i].number){
                        cout << "Выберите изменяемый элемент " << endl;
                        cout << "1 Номер " << endl << "2 Станция " << endl << "3 Время прибытия " << endl
                        << "4 Время в пути " << endl << "5 Время стоянок "
                        << endl; 
                        cin >> element;
                        switch(element){
                            case 1: 
                                
                        }
                    }
                }
                break;
            case 5:
                cout << "penis" << endl;
                break;
            case 6:
                for (int i=0; i<n;i++){
                    cout << "Номер " << arr[i].number << endl << "Станция " << arr[i].station << 
                    endl << "Время прибытия " << arr[i].arrival_time << endl << "Время в пути " << arr[i].traveldays << endl <<
                    "Время стоянок " << arr[i].timetostay_mins
                    << endl;
                }
                break;
            case 7: 
                return 0;
        }
    }
    return 0;
}
