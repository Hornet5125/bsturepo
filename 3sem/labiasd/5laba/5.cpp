#include <iostream>
using namespace std;
struct Point {
    int row;
    int col;
};
void print_maze(char** maze, int rows, int cols) {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            cout << maze[r][c];
        }
        cout << '\n';
    }
}
void print_wave(int* dist, int rows, int cols) {
    cout << "\nВолновая матрица (расстояние от S; # - стена, . - недостижимо):\n";
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            int d = dist[r * cols + c];
            if (d == -1) {
                cout << "   .";
            } else if (d == 0) {
                cout << "   S";
            } else {
                char digits[12];
                int len = 0;
                for (int t = d; t > 0; t /= 10) {
                    digits[len++] = (char)('0' + t % 10);
                }
                for (int i = len; i < 3; ++i) {
                    cout << ' ';
                }
                for (int i = len - 1; i >= 0; --i) {
                    cout << digits[i];
                }
            }
            cout << ' ';
        }
        cout << '\n';
    }
}
const char* steps_word(int length) {
    int last_two = length % 100;
    int last = length % 10;
    if (last_two >= 11 && last_two <= 14) {
        return "шагов";
    }
    if (last == 1) {
        return "шаг";
    }
    if (last >= 2 && last <= 4) {
        return "шага";
    }
    return "шагов";
}
int find_exit(char** maze, int rows, int cols, Point start, Point finish) {
    const int total = rows * cols;
    int* dist = new int[total];
    int* prev = new int[total];
    Point* queue = new Point[total];
    for (int i = 0; i < total; ++i) {
        dist[i] = -1;
        prev[i] = -1;
    }
    const int dr[4] = { 1, -1, 0, 0 };
    const int dc[4] = { 0, 0, 1, -1 };
    int start_index  = start.row * cols + start.col;
    int finish_index = finish.row * cols + finish.col;
    int head = 0;
    int tail = 0;
    dist[start_index] = 0;
    queue[tail++] = start;
    while (head < tail) {
        Point cur = queue[head++];
        for (int k = 0; k < 4; ++k) {
            int nr = cur.row + dr[k];
            int nc = cur.col + dc[k];
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) {
                continue;
            }
            if (maze[nr][nc] == '#') {
                continue;
            }
            int index = nr * cols + nc;
            if (dist[index] != -1) {
                continue;
            }
            dist[index] = dist[cur.row * cols + cur.col] + 1;
            prev[index] = cur.row * cols + cur.col;
            queue[tail].row = nr;
            queue[tail].col = nc;
            ++tail;
        }
    }
    print_wave(dist, rows, cols);
    int path_length = dist[finish_index];
    if (path_length != -1) {
        int cell = finish_index;
        while (cell != start_index) {
            int r = cell / cols;
            int c = cell % cols;
            if (maze[r][c] == '.') {
                maze[r][c] = '*';
            }
            cell = prev[cell];
        }
    }
    delete[] dist;
    delete[] prev;
    delete[] queue;
    return path_length;
}
int main() {
    const char* demo[] = {
        "#####################",
        "#S#...........#...#.#",
        "#.###.#####.#.#.#.#.#",
        "#...#.#...#.#.#.#...#",
        "###.#.#.#.#.#.#.###.#",
        "#...#.#.#.#.#...#...#",
        "#.#####.#.#.#####.###",
        "#...#...#...#.....#.#",
        "###.#.#######.#####.#",
        "#.#.#.....#.#...#...#",
        "#.#.#.###.#.###.#.###",
        "#.#.#...#.#...#.#...#",
        "#.#.#####.#.###.###.#",
        "#.........#........E#",
        "#####################"
    };
    int rows = 15;
    int cols = 0;
    while (demo[0][cols] != '\0') {
        ++cols;
    }
    for (int r = 0; r < rows; ++r) {
        int len = 0;
        while (demo[r][len] != '\0') {
            ++len;
        }
        if (len != cols) {
            cout << "Ошибка: все строки лабиринта должны быть одинаковой длины.\n";
            return 1;
        }
    }
    char** maze = new char*[rows];
    for (int r = 0; r < rows; ++r) {
        maze[r] = new char[cols + 1];
        for (int c = 0; c < cols; ++c) {
            maze[r][c] = demo[r][c];
        }
        maze[r][cols] = '\0';
    }
    Point start  = { 1, 1 };
    Point finish = { 13, 19 };
    cout << "Исходный лабиринт ('#' - стена, '.' - проход, 'S' - старт, 'E' - выход):\n";
    print_maze(maze, rows, cols);
    int length = find_exit(maze, rows, cols, start, finish);
    cout << "\n РЕЗУЛЬТАТ \n";
    if (length == -1) {
        cout << "Выхода нет: клетка E недостижима из S.\n";
    } else {
        cout << "Длина кратчайшего пути: " << length << " " << steps_word(length)
             << " (" << length + 1 << " клеток)\n";
        cout << "\nЛабиринт с найденным маршрутом ('*' - путь):\n";
        print_maze(maze, rows, cols);
    }
    for (int r = 0; r < rows; ++r) {
        delete[] maze[r];
    }
    delete[] maze;
    return 0;
}
