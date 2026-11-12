#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <limits>
#include <algorithm>
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
int read_int(int min, int max) {
    int v;
    while (!(cin >> v) || v < min || v > max) {
        if (cin.eof()) {
            cin.clear();
            return min;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Неверный ввод, повторите: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return v;
}
class Settings {
    public:
        static const int min_duration = 15;
        static const int max_duration = 60;
        static const int default_duration = 30;
        Settings() {
            load();
        }
        string difficulty_name() {
            size_t idx = 0;
            char* end = nullptr;
            long n = strtol(diff.c_str(), &end, 10);
            if (end != diff.c_str() && *end == '\0' && n >= 1) {
                idx = (size_t)(n - 1);
            }
            if (idx < diffs.size()) {
                return diffs[idx];
            }
            return diff;
        }
        int duration() {
            return dura;
        }
        const vector<string>& difficulties() {
            return diffs;
        }
        bool set_diff(const string& value) {
            for (size_t i = 0; i < diffs.size(); ++i) {
                if (diffs[i] == value) {
                    diff = to_string(i + 1);
                    return true;
                }
            }
            return false;
        }
        bool set_dura(int value) {
            if (value < min_duration || value > max_duration) {
                return false;
            }
            dura = value;
            return true;
        }
        void write_defaults_file(const string& d, int du) {
            ofstream f("defaults.txt");
            if (!f) return;
            f << "difficulty = " << d  << "\n";
            f << "duration = "   << du << "\n";
        }
        void reset() {
            ensure_difficulties_file();
            load_difficulties();
            string d = default_difficulty();
            write_defaults_file(d, default_duration);
            load_defaults();
            diff = d;
            dura = default_duration;
        }
        void save() {
            ofstream f("settings.txt");
            if (!f) {
                return;
            }
            f << "difficulty = " << diff << "\n";
            f << "duration = " << dura << "\n";
        }
    private:
        vector<string> diffs;
        string diff;
        int dura = default_duration;
        void write_difficulties_file() {
            ofstream f("difficulties.txt");
            if (!f) return;
            f << "Лёгкая\n";
            f << "Средняя\n";
            f << "Сложная\n";
        }
        string default_difficulty() {
            return diffs.empty() ? "" : "2";
        }
        void ensure_defaults_file(const string& d, int du) {
            ifstream check("defaults.txt");
            if (check.good()) {
                return;
            }
            write_defaults_file(d, du);
        }
        void ensure_difficulties_file() {
            ifstream check("difficulties.txt");
            if (check.good()) return;
            write_difficulties_file();
        }
        static string trim(const string& s) {
            size_t a = s.find_first_not_of(" \t\r\n");
            size_t b = s.find_last_not_of(" \t\r\n");
            return a == string::npos ? "" : s.substr(a, b - a + 1);
        }
        static void parse_line(const string& line, string& k, string& v) {
            size_t pos = line.find('=');
            if (pos == string::npos) {
                k.clear();
                v.clear();
                return;
            }
            k = trim(line.substr(0, pos));
            v = trim(line.substr(pos + 1));
        }
        void load_difficulties() {
            diffs.clear();
            ifstream f("difficulties.txt");
            string line;
            while (getline(f, line)) {
                if (line.empty()) continue;
                if (find(diffs.begin(), diffs.end(), line) == diffs.end()) {
                    diffs.push_back(line);
                }
            }
        }
        void load_defaults() {
            ifstream f("defaults.txt");
            string line, k, v;
            dura = default_duration;
            diff = default_difficulty();
            while (std::getline(f, line)) {
                parse_line(line, k, v);
                if (k == "difficulty") {
                    char* end = nullptr;
                    long n = strtol(v.c_str(), &end, 10);
                    if (end != v.c_str() && *end == '\0'
                        && n >= 1 && n <= (long)diffs.size()) {
                        diff = to_string(n);
                    }
                } else if (k == "duration") {
                    char* end = nullptr;
                    long d = strtol(v.c_str(), &end, 10);
                    if (end != v.c_str() && *end == '\0'
                        && d >= min_duration && d <= max_duration) {
                        dura = (int)d;
                    }
                }
            }
        }
        void load() {
            ensure_difficulties_file();
            load_difficulties();
            ensure_defaults_file(default_difficulty(), default_duration);
            load_defaults();
        }
};
void show_settings(Settings& s) {
    int choice = set_difficulty;
    while (choice != set_back) {
        cout << "\nНастройки\n";
        cout << "1. Сложность (сейчас: " << s.difficulty_name() << ")\n";
        cout << "2. Продолжительность (сейчас: " << s.duration() << ")\n";
        cout << "3. Сброс настроек\n";
        cout << "4. Назад\n";
        cout << "Выбор: ";
        choice = read_int(set_difficulty, set_back);
        switch (choice) {
            case set_difficulty: {
                const vector<string>& list = s.difficulties();
                if (list.empty()) {
                    cout << "Список сложностей пуст (проверьте difficulties.txt)\n";
                    break;
                }
                for (size_t i = 0; i < list.size(); ++i) {
                    cout << "  " << (i + 1) << ". " << list[i] << "\n";
                }
                cout << "Выберите пункт: ";
                int idx = read_int(1, (int)list.size());
                if (s.set_diff(list[idx - 1])) {
                    cout << "Сложность установлена: " << list[idx - 1] << "\n";
                }
                break;
            }
            case set_duration: {
                cout << "Продолжительность (" << Settings::min_duration
                     << ".." << Settings::max_duration << "): ";
                s.set_dura(read_int(Settings::min_duration, Settings::max_duration));
                break;
            }
            case set_reset: {
                s.reset();
                s.save();
                cout << "Настройки сброшены\n";
                break;
            }
            case set_back: {
                break;
            }
            default: {
                break;
            }
        }
    }
    s.save();
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
        choice = read_int(menu_start, menu_exit);
        switch (choice) {
            case menu_start: {
                cout << "Игра началась\n";
                break;
            }
            case menu_load: {
                cout << "Пока нет игры\n";
                break;
            }
            case menu_settings: {
                show_settings(settings);
                break;
            }
            case menu_about: {
                cout << "Версия 0.01. Автор: Кузьмин Андрей\n";
                break;
            }
            case menu_exit: {
                break;
            }
            default: {
                break;
            }
        }
    }
    return 0;
}