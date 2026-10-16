#ifndef PROTOTYPE_H
#define PROTOTYPE_H
int win_check(int pyatnashki[4][4]);
void generate_tiles(int pyatnashki[4][4]);
int define_pos(int pyatnashki[4][4]);
void display_matrix(int pyatnashki[4][4]);
void move_up_up(int pyatnashki[4][4]);
void move_down(int pyatnashki[4][4]);
void move_left(int pyatnashki[4][4]);
void move_right(int pyatnashki[4][4]);
bool is_solvable(int pyatnashki[4][4]);
void generate_solvable_tiles(int pyatnashki[4][4]);
void generate_other_solvable_tiles(int pyatnashki[4][4]);
#endif