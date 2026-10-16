#include "prototypes.h"
#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
using namespace std;
int win_check(int pyatnashki[4][4]) {
    int count = 0;
    int win_matrix[4][4] = {1,2,3,4,
                            5,6,7,8,
                            9,10,11,12,
                            13,14,15,0};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (pyatnashki[i][j] == win_matrix[i][j]) {
                count++;
            }
        }
    }
    return (count == 16) ? 1 : 0;
}
void generate_tiles(int pyatnashki[4][4]) {
    int numbers[16];
    for (int i = 0; i < 15; i++) {
        numbers[i] = i + 1;
    }
    numbers[15] = 0;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(numbers, numbers + 16, default_random_engine(seed));
    int index = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            pyatnashki[i][j] = numbers[index++];
        }
    }
}
int define_pos(int pyatnashki[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (pyatnashki[i][j] == 0) {
                return i * 4 + j;
            }
        }
    }
    return -1;
}
void display_matrix(int pyatnashki[4][4]) {
    for (int j = 0; j < 4; j++) {
        cout << "+---";
    }
    cout << "+" << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << "|";
            if (pyatnashki[i][j] == 0) {
                cout << "   ";
            } else if (pyatnashki[i][j] < 10) {
                cout << " " << pyatnashki[i][j] << " ";
            } else {
                cout << pyatnashki[i][j] << " ";
            }
        }
        cout << "|" << endl;
        if (i < 3) {
            for (int j = 0; j < 4; j++) {
                cout << "+---";
            }
            cout << "+" << endl;
        }
    }
    for (int j = 0; j < 4; j++) {
        cout << "+---";
    }
    cout << "+" << endl;
}
void move_up_up(int pyatnashki[4][4]) {
    int pos = define_pos(pyatnashki);
    int i = pos / 4;
    int j = pos % 4;
    if (i > 0) {
        int temp = pyatnashki[i][j];
        pyatnashki[i][j] = pyatnashki[i - 1][j];
        pyatnashki[i - 1][j] = temp;
    }
}
void move_down(int pyatnashki[4][4]) {
    int pos = define_pos(pyatnashki);
    int i = pos / 4;
    int j = pos % 4;
    if (i < 3) {
        int temp = pyatnashki[i][j];
        pyatnashki[i][j] = pyatnashki[i + 1][j];
        pyatnashki[i + 1][j] = temp;
    }
}
void move_left(int pyatnashki[4][4]) {
    int pos = define_pos(pyatnashki);
    int i = pos / 4;
    int j = pos % 4;
    if (j > 0) {
        int temp = pyatnashki[i][j];
        pyatnashki[i][j] = pyatnashki[i][j - 1];
        pyatnashki[i][j - 1] = temp;
    }
}
void move_right(int pyatnashki[4][4]) {
    int pos = define_pos(pyatnashki);
    int i = pos / 4;
    int j = pos % 4;
    if (j < 3) {
        int temp = pyatnashki[i][j];
        pyatnashki[i][j] = pyatnashki[i][j + 1];
        pyatnashki[i][j + 1] = temp;
    }
}
bool is_solvable(int pyatnashki[4][4]) {
    int line[16];
    int index = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            line[index++] = pyatnashki[i][j];
        }
    }
    int inversions = 0;
    for (int i = 0; i < 15; i++) {
        if (line[i] == 0) continue;
        for (int j = i + 1; j < 16; j++) {
            if (line[j] == 0) continue;
            if (line[i] > line[j]) {
                inversions++;
            }
        }
    }
    int empty_row = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (pyatnashki[i][j] == 0) {
                empty_row = 4 - i;
                break;
            }
        }
    }
    return ((inversions + empty_row) % 2 == 1);
}
void generate_solvable_tiles(int pyatnashki[4][4]) {
    do {
        generate_tiles(pyatnashki);
    } while (!is_solvable(pyatnashki));
}
void generate_other_solvable_tiles(int pyatnashki[4][4]) {
    do {
        int pos = define_pos(pyatnashki);
        int empty_i = pos / 4;
        int empty_j = pos % 4;
        
        int numbers[15];
        for (int i = 0; i < 15; i++) {
            numbers[i] = i + 1;
        }
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        shuffle(numbers, numbers + 15, default_random_engine(seed));
        
        int index = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (i != empty_i || j != empty_j) {
                    pyatnashki[i][j] = numbers[index++];
                }
            }
        }
    } while (!is_solvable(pyatnashki));
}