#include <iostream>
#include <cmath>
using namespace std;
const int MENU_START   = 1;
const int MENU_LOAD    = 2;
const int MENU_SETTINGS = 3;
const int MENU_ABOUT   = 4;
const int MENU_EXIT    = 5;
class Settings{
    public:
        static const int default_diff = 2;
        static const int default_duration = 30;
        static const int min_diff = 1;
        static const int min_duration = 15;
        static const int max_diff = 3;
        static const int max_duration = 60;
        Settings() {
            reset();
        }
        int difficulty() const {
            return diff;
        }
        int duration() const {
            return dura;
        }
        bool set_difficulty(int value){
            if (value < min_diff || value > max_diff){
                return false;
            }
            diff = value;
            return true;
        }
        bool set_duration(int value){
            if (value<min_duration || value>max_duration){
                return false;
            }
            dura = value;
            return true;
        }
        void reset(){
            diff = default_diff;
            dura = default_duration;
        }
    private:
        int diff;
        int dura;
};
int main(){
    
}
