#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <limits>
#include <algorithm>
#include <filesystem>
#include <system_error>
#include <random>
#include <chrono>
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
enum StableMenuId {
    stable_horses = 1,
    stable_train,
    stable_care,
    stable_jockey,
    stable_race,
    stable_buy,
    stable_save,
    stable_exit
};
static mt19937& rng() {
    static mt19937 gen(static_cast<unsigned>(
        chrono::steady_clock::now().time_since_epoch().count()));
    return gen;
}
int random_int(int lo, int hi) {
    if (hi < lo) {
        swap(lo, hi);
    }
    uniform_int_distribution<int> dist(lo, hi);
    return dist(rng());
}
bool chance(int percent) {
    return random_int(1, 100) <= percent;
}
int read_int(int min, int max) {
    int v;
    while (!(cin >> v) || v < min || v > max) {
        if (cin.eof()) {
            cout << "\nКонец ввода.\n";
            exit(0);
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Неверный ввод, повторите: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return v;
}
string trim_copy(const string& s) {
    size_t first = s.find_first_not_of(" \t\r\n");
    if (first == string::npos) {
        return "";
    }
    size_t last = s.find_last_not_of(" \t\r\n");
    return s.substr(first, last - first + 1);
}
string read_line(const string& prompt, const string& fallback = "") {
    cout << prompt;
    string s;
    if (!getline(cin, s)) {
        return fallback;
    }
    s = trim_copy(s);
    return s.empty() ? fallback : s;
}
vector<string> split_text(const string& text, char delimiter) {
    vector<string> parts;
    string current;
    for (char c : text) {
        if (c == delimiter) {
            parts.push_back(current);
            current.clear();
        } else {
            current += c;
        }
    }
    parts.push_back(current);
    return parts;
}
int text_to_int(const string& text, int fallback) {
    try {
        size_t used = 0;
        int value = stoi(text, &used);
        if (used != text.size()) {
            return fallback;
        }
        return value;
    } catch (...) {
        return fallback;
    }
}
string sanitize_name(const string& raw) {
    string s = trim_copy(raw);
    for (char& c : s) {
        if (c == '|' || c == '=') {
            c = ' ';
        }
    }
    s = trim_copy(s);
    if (s.empty()) {
        s = "Без имени";
    }
    if (s.size() > 60) {
        s = s.substr(0, 60);
    }
    return s;
}
class Settings {
    public:
        static const int min_duration = 15;
        static const int max_duration = 60;
        static const int default_duration = 30;
        Settings() {
            load();
        }
        int difficulty_index() {
            size_t idx = 0;
            char* end = nullptr;
            long n = strtol(diff.c_str(), &end, 10);
            if (end != diff.c_str() && *end == '\0' && n >= 1) {
                idx = (size_t)(n - 1);
            }
            if (idx < diffs.size()) {
                return (int)(idx + 1);
            }
            return 1;
        }
        string difficulty_name() {
            int idx = difficulty_index();
            if (idx >= 1 && (size_t)idx <= diffs.size()) {
                return diffs[idx - 1];
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
string segments_word(int count) {
    int mod100 = count % 100;
    int mod10 = count % 10;
    if (mod100 >= 11 && mod100 <= 14) {
        return "отрезков";
    }
    if (mod10 == 1) {
        return "отрезок";
    }
    if (mod10 >= 2 && mod10 <= 4) {
        return "отрезка";
    }
    return "отрезков";
}
enum class Stat {
    Speed = 0,
    Stamina = 1,
    Control = 2
};
const char* stat_name(Stat stat) {
    switch (stat) {
        case Stat::Speed:   return "скорость";
        case Stat::Stamina: return "выносливость";
        case Stat::Control: return "контроль";
    }
    return "?";
}
const char* stat_title(Stat stat) {
    switch (stat) {
        case Stat::Speed:   return "Скорость";
        case Stat::Stamina: return "Выносливость";
        case Stat::Control: return "Контроль";
    }
    return "?";
}
Stat jockey_training_stat(int menu_choice) {
    switch (menu_choice) {
        case 1:  return Stat::Control;
        case 2:  return Stat::Stamina;
        default: return Stat::Speed;
    }
}
enum class Bonus {
    Whirlwind = 0,
    IronStamina,
    Stubborn,
    Sprinter,
    Closer,
    Proud,
    Sensitive,
    Lucky
};
const char* bonus_name(Bonus bonus) {
    switch (bonus) {
        case Bonus::Whirlwind:   return "Вихрь";
        case Bonus::IronStamina: return "Несгибаемая выносливость";
        case Bonus::Stubborn:    return "Упрямец";
        case Bonus::Sprinter:    return "Спринтер";
        case Bonus::Closer:      return "Финишёр";
        case Bonus::Proud:       return "Гордец";
        case Bonus::Sensitive:   return "Чуткий";
        case Bonus::Lucky:       return "Везунчик";
    }
    return "?";
}
const char* bonus_description(Bonus bonus) {
    switch (bonus) {
        case Bonus::Whirlwind:
            return "+2 к проверкам скорости.";
        case Bonus::IronStamina:
            return "Расход энергии в гонке снижен вдвое.";
        case Bonus::Stubborn:
            return "Один раз за гонку можно перебросить проваленную проверку.";
        case Bonus::Sprinter:
            return "+3 к проверкам на первых двух отрезках гонки.";
        case Bonus::Closer:
            return "+3 к проверкам на последних двух отрезках гонки.";
        case Bonus::Proud:
            return "+3 к проверкам, пока лошадь не лидирует.";
        case Bonus::Sensitive:
            return "Жокей даёт двойной бонус к проверкам контроля.";
        case Bonus::Lucky:
            return "Критический успех на 19-20 и +1 ко всем проверкам.";
    }
    return "?";
}
vector<Bonus> all_bonuses() {
    return {
        Bonus::Whirlwind,
        Bonus::IronStamina,
        Bonus::Stubborn,
        Bonus::Sprinter,
        Bonus::Closer,
        Bonus::Proud,
        Bonus::Sensitive,
        Bonus::Lucky
    };
}
void split_total(int total, int& a, int& b, int& c) {
    total = clamp(total, 9, 60);
    a = clamp(total / 3 + random_int(-2, 2), 2, 20);
    b = clamp(total / 3 + random_int(-2, 2), 2, 20);
    c = total - a - b;
    while (c > 20) {
        if (a < 20) {
            ++a;
        } else if (b < 20) {
            ++b;
        } else {
            break;
        }
        --c;
    }
    while (c < 2) {
        if (a > 2) {
            --a;
        } else if (b > 2) {
            --b;
        } else {
            break;
        }
        ++c;
    }
}
class Horse {
    public:
        Horse() {
        }
        Horse(const string& name, const string& breed, Bonus bonus,
              int speed, int stamina, int control)
            : name_(name), breed_(breed), bonus_(bonus) {
            stats_[0] = clamp(speed, 1, 20);
            stats_[1] = clamp(stamina, 1, 20);
            stats_[2] = clamp(control, 1, 20);
        }
        static Horse make_candidate(const string& name, const string& breed, Bonus bonus) {
            return Horse(name, breed, bonus,
                         random_int(3, 6), random_int(3, 6), random_int(3, 6));
        }
        static Horse make_rival(const string& name, const string& breed, int total, Bonus bonus) {
            int speed = 0, stamina = 0, control = 0;
            split_total(total, speed, stamina, control);
            return Horse(name, breed, bonus, speed, stamina, control);
        }
        const string& name() const { return name_; }
        void set_name(const string& name) { name_ = name; }
        const string& breed() const { return breed_; }
        int stat(Stat stat) const { return stats_[(int)stat]; }
        void improve(Stat stat, int amount = 1) {
            int& value = stats_[(int)stat];
            value = min(20, value + amount);
        }
        int total() const {
            return stats_[0] + stats_[1] + stats_[2];
        }
        int level() const { return level_; }
        int xp() const { return xp_; }
        int xp_to_next() const { return 40 + (level_ - 1) * 30; }
        int add_xp(int amount) {
            if (amount <= 0) {
                return 0;
            }
            int levels = 0;
            xp_ += amount;
            while (xp_ >= xp_to_next()) {
                xp_ -= xp_to_next();
                ++level_;
                max_energy_ += 5;
                energy_ = max_energy_;
                mood_ = min(100, mood_ + 10);
                health_ = min(100, health_ + 5);
                int index = random_int(0, 2);
                if (stats_[index] < 20) {
                    ++stats_[index];
                }
                ++levels;
            }
            return levels;
        }
        int energy() const { return energy_; }
        int max_energy() const { return max_energy_; }
        int mood() const { return mood_; }
        int health() const { return health_; }
        void change_energy(int delta) { energy_ = clamp(energy_ + delta, 0, max_energy_); }
        void change_mood(int delta) { mood_ = clamp(mood_ + delta, 0, 100); }
        void change_health(int delta) { health_ = clamp(health_ + delta, 0, 100); }
        Bonus bonus() const { return bonus_; }
        const char* bonus_name_text() const { return bonus_name(bonus_); }
        const char* bonus_description_text() const { return bonus_description(bonus_); }
        int condition_modifier() const {
            int modifier = 0;
            if (mood_ >= 80) {
                modifier += 1;
            } else if (mood_ <= 30) {
                modifier -= 2;
            }
            if (energy_ < 30) {
                modifier -= 2;
            }
            if (health_ < 40) {
                modifier -= 1;
            }
            return modifier;
        }
        int passive_flat(Stat stat, int segment, int segments, int position) const {
            switch (bonus_) {
                case Bonus::Whirlwind:
                    return stat == Stat::Speed ? 2 : 0;
                case Bonus::Sprinter:
                    return segment < 2 ? 3 : 0;
                case Bonus::Closer:
                    return segment >= segments - 2 ? 3 : 0;
                case Bonus::Proud:
                    return position > 1 ? 3 : 0;
                case Bonus::Lucky:
                    return 1;
                default:
                    return 0;
            }
        }
        int race_energy_cost(Stat stat) const {
            int cost = 5;
            if (stat == Stat::Speed) {
                cost = 8;
            } else if (stat == Stat::Stamina) {
                cost = 4;
            }
            if (bonus_ == Bonus::IronStamina) {
                cost = (cost + 1) / 2;
            }
            return cost;
        }
        bool reroll_available() const {
            return bonus_ == Bonus::Stubborn && !reroll_used_;
        }
        void use_reroll() { reroll_used_ = true; }
        void prepare_for_race() { reroll_used_ = false; }
        void note_race(int place) {
            ++races_;
            if (place == 1) {
                ++wins_;
            }
        }
        int wins() const { return wins_; }
        int races() const { return races_; }
        Stat best_stat() const {
            if (stats_[0] >= stats_[1] && stats_[0] >= stats_[2]) {
                return Stat::Speed;
            }
            if (stats_[1] >= stats_[2]) {
                return Stat::Stamina;
            }
            return Stat::Control;
        }
        void load_state(int level, int xp, int energy, int max_energy,
                        int mood, int health, int wins, int races) {
            level_ = clamp(level, 1, 99);
            xp_ = max(0, xp);
            max_energy_ = clamp(max_energy, 50, 400);
            energy_ = clamp(energy, 0, max_energy_);
            mood_ = clamp(mood, 0, 100);
            health_ = clamp(health, 0, 100);
            wins_ = max(0, wins);
            races_ = max(0, races);
        }
    private:
        string name_ = "Без имени";
        string breed_ = "Неизвестная порода";
        int stats_[3] = {3, 3, 3};
        Bonus bonus_ = Bonus::Whirlwind;
        int level_ = 1;
        int xp_ = 0;
        int energy_ = 100;
        int max_energy_ = 100;
        int mood_ = 70;
        int health_ = 100;
        int wins_ = 0;
        int races_ = 0;
        bool reroll_used_ = false;
};
void print_horse_card(const Horse& horse) {
    cout << horse.name() << " — " << horse.breed()
         << ", уровень " << horse.level()
         << " (опыт " << horse.xp() << "/" << horse.xp_to_next() << ")\n";
    cout << "   Скорость " << horse.stat(Stat::Speed)
         << " | Выносливость " << horse.stat(Stat::Stamina)
         << " | Контроль " << horse.stat(Stat::Control) << "\n";
    cout << "   Пассивка «" << horse.bonus_name_text() << "»: "
         << horse.bonus_description_text() << "\n";
    cout << "   Энергия " << horse.energy() << "/" << horse.max_energy()
         << " | Настроение " << horse.mood()
         << " | Здоровье " << horse.health()
         << " | Побед " << horse.wins() << " из " << horse.races() << "\n";
}
class Jockey {
    public:
        Jockey() {
        }
        Jockey(const string& name, int skill, int fitness, int intuition)
            : name_(name) {
            stats_[0] = clamp(skill, 1, 20);
            stats_[1] = clamp(fitness, 1, 20);
            stats_[2] = clamp(intuition, 1, 20);
        }
        const string& name() const { return name_; }
        void set_name(const string& name) { name_ = name; }
        int stat(Stat stat) const { return stats_[(int)stat]; }
        void improve(Stat stat, int amount = 1) {
            int& value = stats_[(int)stat];
            value = min(20, value + amount);
        }
        int bonus(Stat kind) const { return stat(kind) / 3; }
        int level() const { return level_; }
        int xp() const { return xp_; }
        int xp_to_next() const { return 50 + (level_ - 1) * 35; }
        int add_xp(int amount) {
            if (amount <= 0) {
                return 0;
            }
            int levels = 0;
            xp_ += amount;
            while (xp_ >= xp_to_next()) {
                xp_ -= xp_to_next();
                ++level_;
                int index = random_int(0, 2);
                if (stats_[index] < 20) {
                    ++stats_[index];
                }
                ++levels;
            }
            return levels;
        }
        int money() const { return money_; }
        void add_money(int amount) { money_ = max(0, money_ + amount); }
        bool spend_money(int amount) {
            if (money_ < amount) {
                return false;
            }
            money_ -= amount;
            return true;
        }
        string title() const {
            if (level_ >= 7) return "Мастер";
            if (level_ >= 5) return "Опытный жокей";
            if (level_ >= 3) return "Наездник";
            return "Новичок";
        }
        void load_state(int level, int xp, int money) {
            level_ = clamp(level, 1, 99);
            xp_ = max(0, xp);
            money_ = max(0, money);
        }
    private:
        string name_ = "Алекс";
        int stats_[3] = {4, 4, 4};
        int level_ = 1;
        int xp_ = 0;
        int money_ = 500;
};
class Race {
    public:
        Race(Horse& horse, Jockey& jockey, int difficulty, int segments,
             const string& difficulty_name);
        int run();
    private:
        struct Entry {
            Horse* horse;
            int progress;
            bool player;
        };
        struct CheckResult {
            int natural;
            int total;
            int dc;
            bool success;
            bool crit;
            bool rerolled;
        };
        Horse& player_;
        Jockey& jockey_;
        int difficulty_;
        int segments_;
        string difficulty_name_;
        vector<Horse> rivals_;
        vector<Entry> entries_;
        int player_index_ = 0;
        int position_of(const Entry& entry) const;
        int player_position() const;
        void show_standings() const;
        int rival_gain(Entry& entry, int segment);
        CheckResult roll_check(Stat stat, int dc, int segment, int position);
        CheckResult make_check(Stat stat, int dc, int segment, int position);
};
Race::Race(Horse& horse, Jockey& jockey, int difficulty, int segments,
           const string& difficulty_name)
    : player_(horse), jockey_(jockey),
      difficulty_(clamp(difficulty, 1, 3)),
      segments_(clamp(segments, 3, 12)),
      difficulty_name_(difficulty_name) {
    vector<string> names = {
        "Буран", "Ласточка", "Гром", "Заря", "Сокол",
        "Искра", "Тайфун", "Метель", "Пегас", "Вихрь"
    };
    vector<string> breeds = {
        "Орловский рысак", "Арабская чистокровная", "Ахалтекинец",
        "Владимирский тяжеловоз", "Донская порода", "Тракененская"
    };
    names.erase(remove(names.begin(), names.end(), player_.name()), names.end());
    shuffle(names.begin(), names.end(), rng());
    shuffle(breeds.begin(), breeds.end(), rng());
    vector<Bonus> bonuses = all_bonuses();
    bonuses.erase(remove(bonuses.begin(), bonuses.end(), player_.bonus()), bonuses.end());
    shuffle(bonuses.begin(), bonuses.end(), rng());
    rivals_.reserve(3);
    for (int i = 0; i < 3; ++i) {
        int target = player_.total() + difficulty_ - 2 + random_int(-1, 2);
        target = clamp(target, 9, 45);
        Horse rival = Horse::make_rival(names[(size_t)i % names.size()],
                                        breeds[(size_t)i % breeds.size()],
                                        target,
                                        bonuses[(size_t)i % bonuses.size()]);
        rivals_.push_back(rival);
    }
    for (Horse& rival : rivals_) {
        entries_.push_back({&rival, 0, false});
    }
    entries_.push_back({&player_, 0, true});
    player_index_ = (int)entries_.size() - 1;
}
int Race::position_of(const Entry& entry) const {
    int place = 1;
    for (const Entry& other : entries_) {
        if (&other != &entry && other.progress > entry.progress) {
            ++place;
        }
    }
    return place;
}
int Race::player_position() const {
    return position_of(entries_[player_index_]);
}
void Race::show_standings() const {
    vector<int> order(entries_.size());
    for (int i = 0; i < (int)order.size(); ++i) {
        order[i] = i;
    }
    sort(order.begin(), order.end(), [&](int a, int b) {
        return entries_[a].progress > entries_[b].progress;
    });
    cout << "  Положение:";
    for (int index : order) {
        const Entry& entry = entries_[index];
        cout << " " << position_of(entry) << ") "
             << (entry.player ? "ВЫ" : entry.horse->name())
             << " " << entry.progress << ";";
    }
    cout << "\n";
}
int Race::rival_gain(Entry& entry, int segment) {
    int position = position_of(entry);
    int power = entry.horse->total();
    int gain = 2 + power / 10 + random_int(0, 4);
    gain += entry.horse->passive_flat(entry.horse->best_stat(), segment,
                                      segments_, position);
    return max(1, gain);
}
Race::CheckResult Race::roll_check(Stat stat, int dc, int segment, int position) {
    int natural = random_int(1, 20);
    int horse_stat = player_.stat(stat);
    int jockey_bonus = jockey_.bonus(stat);
    bool sensitive = player_.bonus() == Bonus::Sensitive && stat == Stat::Control;
    if (sensitive) {
        jockey_bonus *= 2;
    }
    int passive = player_.passive_flat(stat, segment, segments_, position);
    int condition = player_.condition_modifier();
    int total = natural + horse_stat + jockey_bonus + passive + condition;
    bool crit = natural == 20 ||
                (player_.bonus() == Bonus::Lucky && natural == 19);
    bool success = crit || (natural != 1 && total >= dc);
    cout << "  Бросок d20: " << natural;
    cout << " + " << horse_stat << " (" << stat_name(stat) << ")";
    if (jockey_bonus != 0) {
        cout << " + " << jockey_bonus << " (жокей";
        if (sensitive) {
            cout << ", x2";
        }
        cout << ")";
    }
    if (passive != 0) {
        cout << " + " << passive << " («" << player_.bonus_name_text() << "»)";
    }
    if (condition != 0) {
        cout << (condition > 0 ? " + " : " - ") << abs(condition)
             << " (состояние)";
    }
    cout << " = " << total << " против " << dc << " — ";
    if (crit) {
        cout << "критический успех!\n";
    } else if (natural == 1) {
        cout << "провал (единица)!\n";
    } else if (success) {
        cout << "успех!\n";
    } else {
        cout << "провал.\n";
    }
    CheckResult result;
    result.natural = natural;
    result.total = total;
    result.dc = dc;
    result.success = success;
    result.crit = crit;
    result.rerolled = false;
    return result;
}
Race::CheckResult Race::make_check(Stat stat, int dc, int segment, int position) {
    CheckResult result = roll_check(stat, dc, segment, position);
    if (!result.success && player_.reroll_available()) {
        cout << "  Пассивка «Упрямец»: перебросить проверку? 1 — да, 0 — нет: ";
        if (read_int(0, 1) == 1) {
            player_.use_reroll();
            cout << "  Переброс:\n";
            result = roll_check(stat, dc, segment, position);
            result.rerolled = true;
        }
    }
    return result;
}
int Race::run() {
    cout << "\n========== ГОНКА ==========\n";
    cout << "Дистанция: " << segments_ << " " << segments_word(segments_)
         << ". Сложность: " << difficulty_name_ << ".\n";
    cout << "Соперники:\n";
    for (const Horse& rival : rivals_) {
        cout << "  - " << rival.name() << " (" << rival.breed()
             << "), пассивка «" << rival.bonus_name_text() << "»\n";
    }
    cout << "Ваша лошадь: " << player_.name() << " (" << player_.breed()
         << "), пассивка «" << player_.bonus_name_text() << "»\n";
    cout << "Статы: скорость " << player_.stat(Stat::Speed)
         << " | выносливость " << player_.stat(Stat::Stamina)
         << " | контроль " << player_.stat(Stat::Control) << "\n";
    cout << "1 — начать заезд, 0 — отказаться: ";
    if (read_int(0, 1) == 0) {
        cout << "Вы отказались от гонки.\n";
        return 0;
    }
    player_.prepare_for_race();
    for (int segment = 0; segment < segments_; ++segment) {
        int position = player_position();
        cout << "\n--- Отрезок " << segment + 1 << "/" << segments_
             << " | позиция " << position << "/" << entries_.size()
             << " | энергия " << player_.energy() << "/" << player_.max_energy()
             << " ---\n";
        cout << "Выберите тактику:\n";
        cout << "  1. Ускориться — проверка скорости, при успехе +2 к продвижению (энергия "
             << player_.race_energy_cost(Stat::Speed) << ")\n";
        cout << "  2. Держать темп — проверка выносливости (энергия "
             << player_.race_energy_cost(Stat::Stamina) << ")\n";
        cout << "  3. Аккуратно — проверка контроля, сложность ниже, но продвижение меньше (энергия "
             << player_.race_energy_cost(Stat::Control) << ")\n";
        int choice = read_int(1, 3);
        Stat stat = Stat::Stamina;
        int dc_mod = 0;
        int success_bonus = 0;
        int failure_gain = 1;
        if (choice == 1) {
            stat = Stat::Speed;
            dc_mod = 1;
            success_bonus = 2;
        } else if (choice == 2) {
            stat = Stat::Stamina;
        } else {
            stat = Stat::Control;
            dc_mod = -1;
            success_bonus = -1;
            failure_gain = 3;
        }
        int dc = 10 + difficulty_ + segment / 2 + dc_mod;
        CheckResult result = make_check(stat, dc, segment, position);
        int energy_cost = player_.race_energy_cost(stat);
        player_.change_energy(-energy_cost);
        int gain = 0;
        if (result.success) {
            int margin = max(0, result.total - result.dc);
            gain = 6 + min(6, margin / 2) + random_int(0, 2) + success_bonus;
            if (result.crit) {
                gain += 4;
            }
        } else {
            gain = failure_gain + random_int(0, 2);
            player_.change_mood(-4);
            player_.change_health(-1);
        }
        gain = max(1, gain);
        entries_[player_index_].progress += gain;
        cout << "  Продвижение: +" << gain
             << ". Энергия: " << player_.energy() << "/"
             << player_.max_energy() << ".\n";
        vector<int> rival_gains;
        for (Entry& entry : entries_) {
            if (!entry.player) {
                rival_gains.push_back(rival_gain(entry, segment));
            }
        }
        cout << "  Соперники:";
        int rival_index = 0;
        for (Entry& entry : entries_) {
            if (entry.player) {
                continue;
            }
            entry.progress += rival_gains[(size_t)rival_index];
            cout << " " << entry.horse->name() << " +"
                 << rival_gains[(size_t)rival_index] << ";";
            ++rival_index;
        }
        cout << "\n";
        show_standings();
    }
    int place = player_position();
    cout << "\n========== ФИНИШ ==========\n";
    cout << "Вы заняли " << place << "-е место!\n";
    static const int prize_factors[4] = {10, 6, 4, 2};
    int factor = prize_factors[clamp(place, 1, 4) - 1];
    int prize = (60 + segments_ * 18) * difficulty_ * factor / 10;
    jockey_.add_money(prize);
    int xp = 30 + segments_ * 3 + (4 - place) * 8;
    int horse_levels = player_.add_xp(xp);
    int jockey_levels = jockey_.add_xp(xp);
    player_.note_race(place);
    cout << "Приз: " << prize << " монет. Опыт лошади: +" << xp
         << ", опыт жокея: +" << xp << ".\n";
    if (horse_levels > 0) {
        cout << "Лошадь повысила уровень до " << player_.level() << "!\n";
    }
    if (jockey_levels > 0) {
        cout << "Жокей повысил уровень до " << jockey_.level() << "!\n";
    }
    cout << "Энергия лошади: " << player_.energy() << "/"
         << player_.max_energy() << ". Настроение: " << player_.mood()
         << ". Здоровье: " << player_.health() << ".\n";
    return place;
}
class Game {
    public:
        explicit Game(Settings& settings) : settings_(settings) {
        }
        void new_game();
        bool load();
        void run();
    private:
        Settings& settings_;
        Jockey jockey_;
        vector<Horse> horses_;
        int active_ = 0;
        Horse& active_horse() { return horses_[active_]; }
        const Horse& active_horse() const { return horses_[active_]; }
        int difficulty() const { return settings_.difficulty_index(); }
        int race_segments() const {
            return clamp(settings_.duration() / 5, 3, 12);
        }
        void show_header();
        void show_horses();
        void train_horse();
        void care_horse();
        void train_jockey();
        void start_race();
        void buy_horse();
        bool save() const;
};
void Game::show_header() {
    cout << "\n========================================\n";
    cout << " Конюшня | " << jockey_.name() << " — " << jockey_.title()
         << " (ур. " << jockey_.level() << ")\n";
    cout << " Монеты: " << jockey_.money()
         << " | Сложность: " << settings_.difficulty_name()
         << " | Гонка: " << race_segments() << " "
         << segments_word(race_segments()) << "\n";
    if (!horses_.empty()) {
        const Horse& horse = active_horse();
        cout << " Лошадь: " << horse.name() << " (ур. " << horse.level() << ")"
             << " | Энергия " << horse.energy() << "/" << horse.max_energy()
             << " | Настроение " << horse.mood()
             << " | Здоровье " << horse.health() << "\n";
    }
    cout << "========================================\n";
}
void Game::new_game() {
    cout << "\n========== НОВАЯ ИГРА ==========\n";
    cout << "Добро пожаловать на конюшню! Здесь вы растите жокея\n";
    cout << "и его лошадей: тренируйте их, заботьтесь и побеждайте в гонках.\n\n";
    string jockey_name = read_line("Имя жокея (Enter — Алекс): ");
    if (jockey_name.empty()) {
        jockey_name = "Алекс";
    }
    jockey_ = Jockey(sanitize_name(jockey_name), 4, 4, 4);
    horses_.clear();
    active_ = 0;
    vector<string> names = {
        "Буран", "Ласточка", "Гром", "Заря", "Сокол", "Искра"
    };
    vector<string> breeds = {
        "Орловский рысак", "Арабская чистокровная", "Ахалтекинец",
        "Владимирский тяжеловоз", "Донская порода"
    };
    shuffle(names.begin(), names.end(), rng());
    shuffle(breeds.begin(), breeds.end(), rng());
    vector<Bonus> bonuses = all_bonuses();
    shuffle(bonuses.begin(), bonuses.end(), rng());
    vector<Horse> candidates;
    for (int i = 0; i < 3; ++i) {
        candidates.push_back(Horse::make_candidate(
            names[(size_t)i % names.size()],
            breeds[(size_t)i % breeds.size()],
            bonuses[(size_t)i]));
    }
    cout << "Выберите первую лошадь:\n";
    for (int i = 0; i < (int)candidates.size(); ++i) {
        cout << "\n" << i + 1 << ". ";
        print_horse_card(candidates[(size_t)i]);
    }
    cout << "\nВаш выбор: ";
    int choice = read_int(1, (int)candidates.size());
    Horse chosen = candidates[(size_t)choice - 1];
    string custom_name = read_line(
        "Имя лошади (Enter — оставить «" + chosen.name() + "»): ");
    if (!custom_name.empty()) {
        chosen.set_name(sanitize_name(custom_name));
    }
    horses_.push_back(chosen);
    cout << "\nОтлично! У вас " << jockey_.money() << " монет.\n";
    cout << "Тренируйте лошадь, заботьтесь о ней и выходите на гонки.\n";
    cout << "Помните: у каждой лошади есть уникальная пассивка — она\n";
    cout << "срабатывает во время гонки.\n";
}
void Game::show_horses() {
    if (horses_.empty()) {
        cout << "У вас пока нет лошадей.\n";
        return;
    }
    cout << "\n--- Мои лошади ---\n";
    for (int i = 0; i < (int)horses_.size(); ++i) {
        cout << (i == active_ ? "-> " : "   ") << i + 1 << ". ";
        print_horse_card(horses_[(size_t)i]);
        if (i + 1 < (int)horses_.size()) {
            cout << "\n";
        }
    }
    cout << "\nВыберите лошадь для выступлений (0 — назад): ";
    int choice = read_int(0, (int)horses_.size());
    if (choice > 0) {
        active_ = choice - 1;
        cout << "Активная лошадь: " << active_horse().name() << ".\n";
    }
}
void Game::train_horse() {
    Horse& horse = active_horse();
    cout << "\n--- Тренировка: " << horse.name() << " ---\n";
    cout << "Энергия " << horse.energy() << "/" << horse.max_energy()
         << " | Настроение " << horse.mood()
         << " | Монеты " << jockey_.money() << "\n";
    cout << "1. " << stat_title(Stat::Speed) << " (" << horse.stat(Stat::Speed) << ")\n";
    cout << "2. " << stat_title(Stat::Stamina) << " (" << horse.stat(Stat::Stamina) << ")\n";
    cout << "3. " << stat_title(Stat::Control) << " (" << horse.stat(Stat::Control) << ")\n";
    cout << "4. Назад\n";
    cout << "Выбор: ";
    int choice = read_int(1, 4);
    if (choice == 4) {
        return;
    }
    Stat stat = static_cast<Stat>(choice - 1);
    if (horse.stat(stat) >= 20) {
        cout << stat_title(stat) << " уже на максимуме (20).\n";
        return;
    }
    if (horse.energy() < 25) {
        cout << "Лошадь слишком устала для тренировки. Нужен отдых.\n";
        return;
    }
    if (!jockey_.spend_money(40)) {
        cout << "Не хватает монет: тренировка стоит 40.\n";
        return;
    }
    horse.change_energy(-25);
    horse.change_mood(-5);
    int success_chance = clamp(55 + (horse.mood() - 50) / 2 +
                               (jockey_.level() - 1) * 3, 25, 90);
    bool success = chance(success_chance);
    int xp = success ? 20 : 10;
    int levels = horse.add_xp(xp);
    if (success) {
        horse.improve(stat);
        cout << "Успех! " << stat_title(stat) << " +1 (теперь "
             << horse.stat(stat) << ").\n";
    } else {
        horse.change_mood(-3);
        cout << "Тренировка не удалась, но лошадь получила опыт.\n";
    }
    cout << "Опыт лошади: +" << xp << " ("
         << horse.xp() << "/" << horse.xp_to_next() << ").\n";
    if (levels > 0) {
        cout << "Лошадь повысила уровень до " << horse.level() << "!\n";
    }
}
void Game::care_horse() {
    Horse& horse = active_horse();
    cout << "\n--- Забота: " << horse.name() << " ---\n";
    cout << "Энергия " << horse.energy() << "/" << horse.max_energy()
         << " | Настроение " << horse.mood()
         << " | Здоровье " << horse.health()
         << " | Монеты " << jockey_.money() << "\n";
    cout << "1. Покормить (30 монет): +20 энергии, +8 настроения, +3 здоровья\n";
    cout << "2. Почистить (бесплатно): +12 настроения, +2 здоровья\n";
    cout << "3. Погулять (бесплатно): +10 настроения, +5 энергии\n";
    cout << "4. Отдых (бесплатно): +35 энергии, +5 здоровья\n";
    cout << "5. Назад\n";
    cout << "Выбор: ";
    int choice = read_int(1, 5);
    if (choice == 5) {
        return;
    }
    int xp = 5;
    switch (choice) {
        case 1:
            if (!jockey_.spend_money(30)) {
                cout << "Не хватает монет: кормление стоит 30.\n";
                return;
            }
            horse.change_energy(20);
            horse.change_mood(8);
            horse.change_health(3);
            cout << "Лошадь с аппетитом всё съела.\n";
            break;
        case 2:
            horse.change_mood(12);
            horse.change_health(2);
            xp = 4;
            cout << "Лошадь довольно фыркает после чистки.\n";
            break;
        case 3:
            horse.change_mood(10);
            horse.change_energy(5);
            xp = 4;
            cout << "Прогулка подняла настроение.\n";
            break;
        case 4:
            horse.change_energy(35);
            horse.change_health(5);
            horse.change_mood(2);
            xp = 3;
            cout << "Лошадь хорошо отдохнула.\n";
            break;
        default:
            return;
    }
    int levels = horse.add_xp(xp);
    int jockey_levels = jockey_.add_xp(2);
    cout << "Энергия: " << horse.energy() << "/" << horse.max_energy()
         << ", настроение: " << horse.mood()
         << ", здоровье: " << horse.health() << ".\n";
    if (levels > 0) {
        cout << "Лошадь повысила уровень до " << horse.level() << "!\n";
    }
    if (jockey_levels > 0) {
        cout << "Жокей повысил уровень до " << jockey_.level() << "!\n";
    }
}
void Game::train_jockey() {
    cout << "\n--- Тренировка жокея ---\n";
    cout << jockey_.name() << " — " << jockey_.title()
         << ", уровень " << jockey_.level()
         << " (опыт " << jockey_.xp() << "/" << jockey_.xp_to_next() << ")\n";
    cout << "Мастерство " << jockey_.stat(Stat::Control)
         << " | Физподготовка " << jockey_.stat(Stat::Stamina)
         << " | Чутьё " << jockey_.stat(Stat::Speed) << "\n";
    cout << "Монеты: " << jockey_.money() << "\n";
    cout << "1. Мастерство (" << jockey_.stat(Stat::Control) << ")\n";
    cout << "2. Физподготовка (" << jockey_.stat(Stat::Stamina) << ")\n";
    cout << "3. Чутьё (" << jockey_.stat(Stat::Speed) << ")\n";
    cout << "4. Назад\n";
    cout << "Выбор: ";
    int choice = read_int(1, 4);
    if (choice == 4) {
        return;
    }
    Stat stat = jockey_training_stat(choice);
    static const char* jockey_stat_names[3] = {
        "Мастерство", "Физподготовка", "Чутьё"
    };
    const char* jockey_stat_name = jockey_stat_names[choice - 1];
    if (jockey_.stat(stat) >= 20) {
        cout << jockey_stat_name << " уже на максимуме (20).\n";
        return;
    }
    if (!jockey_.spend_money(80)) {
        cout << "Не хватает монет: тренировка жокея стоит 80.\n";
        return;
    }
    int success_chance = clamp(55 + (jockey_.level() - 1) * 3, 25, 90);
    bool success = chance(success_chance);
    int xp = success ? 25 : 10;
    int levels = jockey_.add_xp(xp);
    if (success) {
        jockey_.improve(stat);
        cout << "Успех! " << jockey_stat_name << " +1 (теперь "
             << jockey_.stat(stat) << ").\n";
    } else {
        cout << "Тренировка не удалась, но опыт получен.\n";
    }
    cout << "Опыт жокея: +" << xp << " ("
         << jockey_.xp() << "/" << jockey_.xp_to_next() << ").\n";
    if (levels > 0) {
        cout << "Жокей повысил уровень до " << jockey_.level() << "!\n";
    }
}
void Game::start_race() {
    Horse& horse = active_horse();
    if (horse.energy() < 20) {
        cout << "Лошадь слишком устала для гонки (энергия "
             << horse.energy() << "). Дайте ей отдохнуть.\n";
        return;
    }
    Race race(horse, jockey_, difficulty(), race_segments(),
              settings_.difficulty_name());
    int place = race.run();
    if (place > 0) {
        if (save()) {
            cout << "Прогресс сохранён.\n";
        }
    }
}
void Game::buy_horse() {
    if ((int)horses_.size() >= 3) {
        cout << "В конюшне нет места: максимум 3 лошади.\n";
        return;
    }
    vector<string> names = {
        "Буран", "Ласточка", "Гром", "Заря", "Сокол",
        "Искра", "Тайфун", "Метель", "Пегас", "Вихрь"
    };
    vector<string> breeds = {
        "Орловский рысак", "Арабская чистокровная", "Ахалтекинец",
        "Владимирский тяжеловоз", "Донская порода", "Тракененская"
    };
    for (const Horse& horse : horses_) {
        names.erase(remove(names.begin(), names.end(), horse.name()), names.end());
    }
    shuffle(names.begin(), names.end(), rng());
    shuffle(breeds.begin(), breeds.end(), rng());
    if (names.empty()) {
        names.push_back("Новичок");
    }
    int total = active_horse().total() + random_int(-2, 4);
    total = clamp(total, 9, 45);
    vector<Bonus> free_bonuses = all_bonuses();
    for (const Horse& horse : horses_) {
        free_bonuses.erase(remove(free_bonuses.begin(), free_bonuses.end(),
                                  horse.bonus()),
                           free_bonuses.end());
    }
    if (free_bonuses.empty()) {
        free_bonuses = all_bonuses();
    }
    Bonus bonus = free_bonuses[random_int(0, (int)free_bonuses.size() - 1)];
    Horse candidate = Horse::make_rival(names[0], breeds[0], total, bonus);
    int price = 200 + candidate.total() * 12;
    cout << "\n--- Ярмарка ---\n";
    cout << "Предлагается лошадь:\n";
    print_horse_card(candidate);
    cout << "Цена: " << price << " монет. Купить? 1 — да, 0 — нет: ";
    if (read_int(0, 1) == 0) {
        cout << "Вы отказались от покупки.\n";
        return;
    }
    if (!jockey_.spend_money(price)) {
        cout << "Не хватает монет.\n";
        return;
    }
    horses_.push_back(candidate);
    active_ = (int)horses_.size() - 1;
    cout << "Лошадь куплена! Теперь она активна.\n";
}
bool Game::save() const {
    ofstream file("save.txt");
    if (!file) {
        return false;
    }
    file << "version = 1\n";
    file << "jockey = " << jockey_.name() << "|"
         << jockey_.stat(Stat::Speed) << "|"
         << jockey_.stat(Stat::Stamina) << "|"
         << jockey_.stat(Stat::Control) << "|"
         << jockey_.level() << "|"
         << jockey_.xp() << "|"
         << jockey_.money() << "\n";
    file << "active = " << active_ << "\n";
    for (const Horse& horse : horses_) {
        file << "horse = " << horse.name() << "|"
             << horse.breed() << "|"
             << horse.stat(Stat::Speed) << "|"
             << horse.stat(Stat::Stamina) << "|"
             << horse.stat(Stat::Control) << "|"
             << horse.level() << "|"
             << horse.xp() << "|"
             << horse.energy() << "|"
             << horse.max_energy() << "|"
             << horse.mood() << "|"
             << horse.health() << "|"
             << static_cast<int>(horse.bonus()) << "|"
             << horse.wins() << "|"
             << horse.races() << "\n";
    }
    return true;
}
bool Game::load() {
    ifstream file("save.txt");
    if (!file) {
        cout << "Сохранение не найдено (save.txt).\n";
        return false;
    }
    Jockey loaded_jockey;
    vector<Horse> loaded_horses;
    int loaded_active = 0;
    bool jockey_read = false;
    string line;
    while (getline(file, line)) {
        line = trim_copy(line);
        if (line.empty()) {
            continue;
        }
        size_t equal_pos = line.find('=');
        if (equal_pos == string::npos) {
            continue;
        }
        string key = trim_copy(line.substr(0, equal_pos));
        string value = trim_copy(line.substr(equal_pos + 1));
        if (key == "jockey") {
            vector<string> parts = split_text(value, '|');
            if (parts.size() != 7) {
                cout << "Ошибка сохранения: неверная запись жокея.\n";
                return false;
            }
            int skill = text_to_int(parts[1], -1);
            int fitness = text_to_int(parts[2], -1);
            int intuition = text_to_int(parts[3], -1);
            int level = text_to_int(parts[4], -1);
            int xp = text_to_int(parts[5], -1);
            int money = text_to_int(parts[6], -1);
            if (skill < 1 || skill > 20 || fitness < 1 || fitness > 20 ||
                intuition < 1 || intuition > 20 || level < 1 || level > 99 ||
                xp < 0 || money < 0) {
                cout << "Ошибка сохранения: неверные характеристики жокея.\n";
                return false;
            }
            loaded_jockey = Jockey(parts[0], skill, fitness, intuition);
            loaded_jockey.load_state(level, xp, money);
            jockey_read = true;
        } else if (key == "horse") {
            vector<string> parts = split_text(value, '|');
            if (parts.size() != 14) {
                cout << "Ошибка сохранения: неверная запись лошади.\n";
                return false;
            }
            int speed = text_to_int(parts[2], -1);
            int stamina = text_to_int(parts[3], -1);
            int control = text_to_int(parts[4], -1);
            int level = text_to_int(parts[5], -1);
            int xp = text_to_int(parts[6], -1);
            int energy = text_to_int(parts[7], -1);
            int max_energy = text_to_int(parts[8], -1);
            int mood = text_to_int(parts[9], -1);
            int health = text_to_int(parts[10], -1);
            int bonus = text_to_int(parts[11], -1);
            int wins = text_to_int(parts[12], -1);
            int races = text_to_int(parts[13], -1);
            if (speed < 1 || speed > 20 || stamina < 1 || stamina > 20 ||
                control < 1 || control > 20 || level < 1 || level > 99 ||
                xp < 0 || energy < 0 || max_energy < 50 || max_energy > 400 ||
                energy > max_energy || mood < 0 || mood > 100 ||
                health < 0 || health > 100 || bonus < 0 || bonus > 7 ||
                wins < 0 || races < 0 || wins > races) {
                cout << "Ошибка сохранения: неверные данные лошади.\n";
                return false;
            }
            string name = parts[0].empty() ? "Без имени" : parts[0];
            string breed = parts[1].empty() ? "Неизвестная порода" : parts[1];
            Horse horse(name, breed, static_cast<Bonus>(bonus),
                        speed, stamina, control);
            horse.load_state(level, xp, energy, max_energy,
                             mood, health, wins, races);
            loaded_horses.push_back(horse);
        } else if (key == "active") {
            loaded_active = text_to_int(value, 0);
        }
    }
    if (!jockey_read || loaded_horses.empty()) {
        cout << "Ошибка сохранения: нет данных жокея или лошадей.\n";
        return false;
    }
    if (loaded_active < 0 || loaded_active >= (int)loaded_horses.size()) {
        loaded_active = 0;
    }
    jockey_ = loaded_jockey;
    horses_ = loaded_horses;
    active_ = loaded_active;
    cout << "Игра загружена.\n";
    return true;
}
void Game::run() {
    int choice = stable_horses;
    while (choice != stable_exit) {
        show_header();
        cout << "1. Мои лошади\n";
        cout << "2. Тренировка лошади\n";
        cout << "3. Забота о лошади\n";
        cout << "4. Тренировка жокея\n";
        cout << "5. Гонка\n";
        cout << "6. Купить лошадь\n";
        cout << "7. Сохранить игру\n";
        cout << "8. В главное меню\n";
        cout << "Выбор: ";
        choice = read_int(stable_horses, stable_exit);
        switch (choice) {
            case stable_horses: {
                show_horses();
                break;
            }
            case stable_train: {
                train_horse();
                break;
            }
            case stable_care: {
                care_horse();
                break;
            }
            case stable_jockey: {
                train_jockey();
                break;
            }
            case stable_race: {
                start_race();
                break;
            }
            case stable_buy: {
                buy_horse();
                break;
            }
            case stable_save: {
                if (save()) {
                    cout << "Игра сохранена (save.txt).\n";
                } else {
                    cout << "Не удалось сохранить игру.\n";
                }
                break;
            }
            case stable_exit: {
                break;
            }
            default: {
                break;
            }
        }
    }
    if (save()) {
        cout << "Игра сохранена.\n";
    } else {
        cout << "Не удалось сохранить игру.\n";
    }
}
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
    {
        error_code ec;
        filesystem::path source(__FILE__);
        if (source.is_absolute() && std::filesystem::exists(source.parent_path(), ec)) {
            std::filesystem::current_path(source.parent_path(), ec);
        }
    }
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
                Game game(settings);
                game.new_game();
                game.run();
                break;
            }
            case menu_load: {
                Game game(settings);
                if (game.load()) {
                    game.run();
                }
                break;
            }
            case menu_settings: {
                show_settings(settings);
                break;
            }
            case menu_about: {
                cout << "Версия 0.05. Автор: Кузьмин Андрей\n";
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
