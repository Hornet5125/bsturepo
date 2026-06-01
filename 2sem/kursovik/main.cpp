#include "prototypes.h"
#include <iostream> 
#include <fstream>
#include <chrono> 
#include <string>
#include <cstring>
#include <random>
#include <iomanip>
#include <thread>
#include <mutex>
#include <atomic>
#include <conio.h>
using namespace std;
struct Record {
    string name;
    int moves;
    double time;
};
class Leaderboard {
private:
    Record records[10];
    int record_count;
    string filename;
public:
    Leaderboard(string file = "records.txt") : filename(file), record_count(0) {
        for (int i = 0; i < 10; i++) {
            records[i].name = "";
            records[i].moves = 0;
            records[i].time = 0;
        }
        loadRecords();
    }
    void loadRecords() {
        ifstream file(filename);
        record_count = 0;
        if (file.is_open()) {
            string name;
            int moves;
            double time;
            while (record_count < 10 && getline(file, name)) {
                if (file >> moves >> time) {
                    file.ignore();
                    records[record_count].name = name;
                    records[record_count].moves = moves;
                    records[record_count].time = time;
                    record_count++;
                }
            }
            file.close();
        }
        sort_records();
    }
    void saveRecords() {
        ofstream file(filename);
        if (file.is_open()) {
            for (int i = 0; i < record_count; i++) {
                file << records[i].name << "\n";
                file << records[i].moves << "\n";
                file << records[i].time << "\n";
            }
            file.close();
        }
    }
    void sort_records() {
        for (int i = 0; i < record_count - 1; i++) {
            for (int j = 0; j < record_count - i - 1; j++) {
                if (records[j].moves > records[j + 1].moves) {
                    swap(records[j], records[j + 1]);
                } else if (records[j].moves == records[j + 1].moves) {
                    if (records[j].time > records[j + 1].time) {
                        swap(records[j], records[j + 1]);
                    }
                }
            }
        }
    }
    bool isHighScore(int moves, double time) {
        if (record_count < 10) return true;
        if (moves < records[record_count - 1].moves) return true;
        if (moves == records[record_count - 1].moves && time < records[record_count - 1].time) return true;
        return false;
    }
    void addRecord(string name, int moves, double time) {
        if (!isHighScore(moves, time)) return;
        if (record_count < 10) {
            records[record_count].name = name;
            records[record_count].moves = moves;
            records[record_count].time = time;
            record_count++;
        } else {
            records[record_count - 1].name = name;
            records[record_count - 1].moves = moves;
            records[record_count - 1].time = time;
        }
        sort_records();
        saveRecords();
    }
    void showLeaderboard() {
        if (record_count == 0) {
            cout << "Таблица рекордов пуста" << endl;
            return;
        }
        cout << "Таблица рекордов: " << endl;
        cout << "Место | Игрок              | Ходов | Время (с)" << endl;
        for (int i = 0; i < record_count; i++) {
            cout << "  " << i + 1 << "    | ";
            if (records[i].name.length() > 18) {
                cout << records[i].name.substr(0, 15);
            } 
            else {
                cout << records[i].name;
                for (int j = records[i].name.length(); j < 18; j++) {
                    cout << " ";
                }
            }
            cout << " |   " << records[i].moves;
            for (int j = (records[i].moves < 10 ? 3 : (records[i].moves < 100 ? 2 : 1)); j < 4; j++) cout << " ";
            cout << " |   " << fixed << setprecision(2) << records[i].time << "\n";
        }
    }
    int getRank(int moves, double time) {
        for (int i = 0; i < record_count; i++) {
            if (moves < records[i].moves){
                return i + 1;
            } 
            if (moves == records[i].moves && time < records[i].time){
                return i + 1;
            }
        }
        if (record_count < 10){
            return record_count + 1;
        }
        return -1;
    }
};
struct TimerData {
    int (*pyatnashki)[4];
    atomic<bool>& game_running;
    atomic<int>& current_moves;
    chrono::steady_clock::time_point start_time;
    mutex& display_mutex;
    atomic<double>& current_time;
    TimerData(int (*p)[4], atomic<bool>& gr, atomic<int>& cm, 
              chrono::steady_clock::time_point st, mutex& dm, atomic<double>& ct)
        : pyatnashki(p), game_running(gr), current_moves(cm), 
          start_time(st), display_mutex(dm), current_time(ct) {}
};
void timer_update_func(TimerData* data) {
    while (data->game_running) {
        this_thread::sleep_for(chrono::milliseconds(100));
        if (data->game_running) {
            auto now = chrono::steady_clock::now();
            double elapsed = chrono::duration<double>(now - data->start_time).count();
            data->current_time = elapsed;
        }
    }
}
string input_player_name(){
    string name;
    cout << "Введите имя:";
    getline(cin, name);
    return name;
}
void input_spawn_point(int pyatnashki[4][4]){
        int i,j;
    int x;
    cout << "Выберите сценарий: " << endl << "1 Появиться в заданной позиции" << endl << "2 Появиться случайно" << endl;
    cin >> x;
    cin.ignore();
    switch(x){
        case 1:
            cout << "Введите ряд в котором хотите появиться: ";
            cin >> i;
            cout << "Введите колонну в которой хотите появиться: ";
            cin >> j;
            for (int row = 0; row < 4; row++) {
                for (int col = 0; col < 4; col++) {
                    pyatnashki[row][col] = 1;
                }
            }
            pyatnashki[i-1][j-1] = 0;
            generate_other_solvable_tiles(pyatnashki);
            break;
        case 2:
            generate_solvable_tiles(pyatnashki);
            break;
    }
}
void display_game_state(int pyatnashki[4][4], int move_count, double elapsed) {
    system("cls");
    display_matrix(pyatnashki);
    cout << "Ходов сделано: " << move_count << endl;
    cout << "Время: " << fixed << setprecision(2) << elapsed << " секунд" << endl;
    cout << "Куда вы хотите двигаться?" << endl;
    cout << "1 Вверх" << endl;
    cout << "2 Вниз" << endl;
    cout << "3 Вправо" << endl;
    cout << "4 Влево" << endl;
    cout << "Ваш выбор: " << flush;
}
void menu_moves(int pyatnashki[4][4], Leaderboard& leaderboard, string players_name) {
    char x;
    atomic<bool> game_running(true);
    atomic<int> current_moves(0);
    atomic<double> current_time(0);
    if (!is_solvable(pyatnashki)) {
        int emptyi = -1, emptyj = -1;
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                if (pyatnashki[row][col] == 0) {
                    emptyi = row;
                    emptyj = col;
                    break;
                }
            }
        }
        if (emptyi == -1) {
            emptyi = 3;
            emptyj = 3;
        }
        int new_pyatnashki[4][4];
        generate_solvable_tiles(new_pyatnashki);
        int new_emptyi = -1, new_emptyj = -1;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (new_pyatnashki[i][j] == 0) {
                    new_emptyi = i;
                    new_emptyj = j;
                    break;
                }
            }
        }
        if (new_emptyi != emptyi || new_emptyj != emptyj) {
            swap(new_pyatnashki[emptyi][emptyj], new_pyatnashki[new_emptyi][new_emptyj]);
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                pyatnashki[i][j] = new_pyatnashki[i][j];
            }
        }
    }
    auto start_time = chrono::steady_clock::now();
    thread timer_thread([&]() {
        auto last_redraw = chrono::steady_clock::now();
        while (game_running) {
            this_thread::sleep_for(chrono::milliseconds(100));
            if (game_running) {
                auto now = chrono::steady_clock::now();
                double elapsed = chrono::duration<double>(now - start_time).count();
                current_time = elapsed;
                if (chrono::duration<double>(now - last_redraw).count() > 0.5) {
                    system("cls");
                    display_matrix(pyatnashki);
                    cout << "Ходов сделано: " << current_moves.load() << endl;
                    cout << "Время: " << fixed << setprecision(2) << current_time.load() << " секунд" << endl;
                    cout << "\nКуда вы хотите двигаться?" << endl;
                    cout << "1 Вверх" << endl;
                    cout << "2 Вниз" << endl;
                    cout << "3 Вправо" << endl;
                    cout << "4 Влево" << endl;
                    cout << "Ваш выбор: " << flush;
                    last_redraw = now;
                }
            }
        }
    });
    display_game_state(pyatnashki, 0, 0);
    while (game_running) {
        if (_kbhit()) {
            x = _getch();
            switch(x){
                case '1':
                    move_up_up(pyatnashki);
                    current_moves++;
                    break;
                case '2':
                    move_down(pyatnashki);
                    current_moves++;
                    break;
                case '3':
                    move_right(pyatnashki);
                    current_moves++;
                    break;
                case '4':
                    move_left(pyatnashki);
                    current_moves++;
                    break;
                default:
                    continue;
            }
            double elapsed = current_time.load();
            display_game_state(pyatnashki, current_moves.load(), elapsed);
            if (win_check(pyatnashki) == 1) {
                game_running = false;
                timer_thread.join();
                double finalTime = current_time.load();
                system("cls");
                display_matrix(pyatnashki);
                cout << "Победа!" << endl;
                cout << "Финальное время: " << fixed << setprecision(2) << finalTime << " секунд" << endl;
                cout << "Всего ходов: " << current_moves.load() << endl;
                if (leaderboard.isHighScore(current_moves.load(), finalTime)) {
                    leaderboard.addRecord(players_name, current_moves.load(), finalTime);
                    int rank = leaderboard.getRank(current_moves.load(), finalTime);
                    cout << "Ваше место в рейтинге: " << rank << endl;
                } else {
                    cout << "Рекорд не побит, попробуйте ещё" << endl;
                }
                cout << "Нажмите любую клавишу для продолжения";
                _getch();
                break;
            }
        }
        this_thread::sleep_for(chrono::milliseconds(10));
    }
    if (game_running) {
        game_running = false;
        timer_thread.join();
    }
}
void menu(int pyatnashki[4][4],Leaderboard& leaderboard){
    int x;
    string players_name;
    bool prog = true;
    while (prog){
        cout << "Выберите действие: " << endl << "1 Ввести имя "
        << endl << "2 Появиться " << endl << "3 Показать таблицу рекордов " << endl << "4 Выход " << endl;
        cin >> x;
        cin.ignore();
        switch(x){
            case 1:
                players_name = input_player_name();
                break;
            case 2:
                if (players_name.empty()) {
                    cout << "Сначала введите имя!" << endl;
                    break;
                }
                input_spawn_point(pyatnashki);
                menu_moves(pyatnashki,leaderboard,players_name);
                break;
            case 3:
                leaderboard.showLeaderboard();
                break;
            default:
                prog = false;
                break;
        }
    }
}
int main(){
    int pyatnashki[4][4];
    Leaderboard leaderboard;
    menu(pyatnashki,leaderboard);
    return 0;
}