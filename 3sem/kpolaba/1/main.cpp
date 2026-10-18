#include <iostream>
using namespace std;
enum MainMenuId {
    menu_start = 1,
    menu_load,
    menu_settings,
    menu_about,
    menu_exit
};
enum SettingsMenuId {
    set_difficulty = 1,
    set_duration,
    set_reset,
    set_back
};
int readInt(int min, int max) {
    int v;
    while (!(cin >> v) || v < min || v > max) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Неверный ввод, повторите: ";
    }
    return v;
}
class Settings {
public:
    static const int default_diff     = 2;
    static const int default_duration = 30;
    static const int min_diff         = 1;
    static const int max_diff         = 3;
    static const int min_duration     = 15;
    static const int max_duration     = 60;
    Settings() { reset(); }
    int difficulty() const { return diff; }
    int duration()   const { return dura; }
    bool set_difficulty(int value) {
        if (value < min_diff || value > max_diff) return false;
        diff = value;
        return true;
    }
    bool set_duration(int value) {
        if (value < min_duration || value > max_duration) return false;
        dura = value;
        return true;
    }
    void reset() {
        diff = default_diff;
        dura = default_duration;
    }
private:
    int diff;
    int dura;
};
void show_settings(Settings& s) {
    int choice = set_difficulty;   // начальное значение, чтобы войти в цикл
    while (choice != set_back) {
        cout << "\nНастройки\n";
        cout << "1. Сложность (сейчас: " << s.difficulty() << ")\n";
        cout << "2. Продолжительность (сейчас: " << s.duration() << ")\n";
        cout << "3. Сброс настроек\n";
        cout << "4. Назад\n";
        cout << "Выбор: ";
        choice = readInt(set_difficulty, set_back);
        switch (choice) {
            case set_difficulty:
                cout << "Сложность (" << Settings::min_diff << ".." << Settings::max_diff << "): ";
                s.set_difficulty(readInt(Settings::min_diff, Settings::max_diff));
                break;
            case set_duration:
                cout << "Продолжительность (" << Settings::min_duration << ".." << Settings::max_duration << "): ";
                s.set_duration(readInt(Settings::min_duration, Settings::max_duration));
                break;
            case set_reset:
                s.reset();
                cout << "Настройки сброшены\n";
                break;
        }
    }
}
int main() {
    Settings settings;
    int choice = menu_start;
    while (choice != menu_exit) {
        cout << "\nЛошади и гонки\n";
        cout << "1. Начать игру\n";
        cout << "2. Загрузить игру\n";
        cout << "3. Настройки\n";
        cout << "4. О программе\n";
        cout << "5. Выход\n";
        cout << "Выбор: ";
        choice = readInt(menu_start, menu_exit);
        switch (choice) {
            case menu_start:
                cout << "Игра началась\n";
                break;
            case menu_load:
                cout << "Пока нет игры\n";
                break;
            case menu_settings:
                show_settings(settings);
                break;
            case menu_about:
                cout << "Версия 0.01. Автор: Кузьмин Андрей \n";
                break;
        }
    }
    return 0;
}