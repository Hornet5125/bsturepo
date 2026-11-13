#include <iostream>
using namespace std;
const int MAX_CHARS = 256;
const int MAX_TEXT  = 1024;
struct Node {
    char ch;
    int  freq;
    int  left;
    int  right;
};
int add_node(Node* nodes, int& count, char ch, int freq, int left, int right) {
    nodes[count].ch = ch;
    nodes[count].freq = freq;
    nodes[count].left = left;
    nodes[count].right = right;
    return count++;
}
int symbol_count(const char* s) {
    int count = 0;
    for (int i = 0; s[i] != '\0'; ++i) {
        if (((unsigned char)s[i] & 0xC0) != 0x80) {
            ++count;
        }
    }
    return count;
}
void print_left(const char* s, int width) {
    cout << s;
    int len = symbol_count(s);
    for (int i = len; i < width; ++i) {
        cout << ' ';
    }
}
void print_number(int value, int width) {
    char reversed[12];
    int len = 0;
    if (value == 0) {
        reversed[len++] = '0';
    }
    while (value > 0) {
        reversed[len++] = (char)('0' + value % 10);
        value /= 10;
    }
    char normal[12];
    for (int i = 0; i < len; ++i) {
        normal[i] = reversed[len - 1 - i];
    }
    normal[len] = '\0';
    print_left(normal, width);
}
void build_codes(Node* nodes, int root, char** code, int* length,
                 char* buffer, int depth) {
    if (root == -1) {
        return;
    }
    if (nodes[root].left == -1 && nodes[root].right == -1) {
        if (depth == 0) {
            buffer[0] = '0';
            depth = 1;
        }
        int c = (unsigned char)nodes[root].ch;
        code[c] = new char[depth + 1];
        for (int i = 0; i < depth; ++i) {
            code[c][i] = buffer[i];
        }
        code[c][depth] = '\0';
        length[c] = depth;
        return;
    }
    buffer[depth] = '0';
    build_codes(nodes, nodes[root].left, code, length, buffer, depth + 1);
    buffer[depth] = '1';
    build_codes(nodes, nodes[root].right, code, length, buffer, depth + 1);
}
int main() {
    char text[MAX_TEXT];
    cout << "Введите текст для сжатия (просто Enter - демонстрационный текст ABRACADABRA): ";
    cin.getline(text, MAX_TEXT);
    int text_length = 0;
    while (text[text_length] != '\0') {
        ++text_length;
    }
    if (text_length == 0) {
        const char* demo = "ABRACADABRA";
        while (demo[text_length] != '\0') {
            text[text_length] = demo[text_length];
            ++text_length;
        }
        text[text_length] = '\0';
    }
    cout << "\nИсходный текст: " << text << '\n';
    cout << "Длина текста: " << text_length << " символов\n";
    int* freq = new int[MAX_CHARS];
    for (int c = 0; c < MAX_CHARS; ++c) {
        freq[c] = 0;
    }
    for (int i = 0; i < text_length; ++i) {
        ++freq[(unsigned char)text[i]];
    }
    Node* nodes = new Node[2 * MAX_CHARS];
    int node_count = 0;
    int* roots = new int[MAX_CHARS];
    int root_count = 0;
    for (int c = 0; c < MAX_CHARS; ++c) {
        if (freq[c] > 0) {
            roots[root_count++] = add_node(nodes, node_count, (char)c, freq[c], -1, -1);
        }
    }
    while (root_count > 1) {
        int first = 0;
        int second = -1;
        for (int i = 1; i < root_count; ++i) {
            if (nodes[roots[i]].freq < nodes[roots[first]].freq) {
                second = first;
                first = i;
            } else if (second == -1 || nodes[roots[i]].freq < nodes[roots[second]].freq) {
                second = i;
            }
        }
        if (second == -1) {
            second = 0;
        }
        int left_node  = roots[first];
        int right_node = roots[second];
        int parent = add_node(nodes, node_count, '\0',
                              nodes[left_node].freq + nodes[right_node].freq,
                              left_node, right_node);
        int kept = 0;
        for (int i = 0; i < root_count; ++i) {
            if (i == first || i == second) {
                continue;
            }
            roots[kept++] = roots[i];
        }
        roots[kept++] = parent;
        root_count = kept;
    }
    if (root_count == 0) {
        cout << "Текст пустой - кодировать нечего.\n";
        delete[] freq;
        delete[] nodes;
        delete[] roots;
        return 0;
    }
    int root = roots[0];
    char** code = new char*[MAX_CHARS];
    int* length = new int[MAX_CHARS];
    for (int c = 0; c < MAX_CHARS; ++c) {
        code[c] = 0;
        length[c] = 0;
    }
    char* buffer = new char[MAX_CHARS];
    build_codes(nodes, root, code, length, buffer, 0);
    cout << "\nТаблица кодов Хаффмана:\n";
    print_left("Символ", 9);
    print_left("Частота", 9);
    print_left("Код", 22);
    cout << "Бит\n";
    for (int c = 0; c < MAX_CHARS; ++c) {
        if (freq[c] == 0) {
            continue;
        }
        char symbol[2] = { (char)c, '\0' };
        print_left(symbol, 9);
        print_number(freq[c], 9);
        print_left(code[c], 22);
        cout << length[c] << '\n';
    }
    int total_bits = 0;
    for (int c = 0; c < MAX_CHARS; ++c) {
        total_bits += freq[c] * length[c];
    }
    char* encoded = new char[total_bits + 1];
    int pos = 0;
    for (int i = 0; i < text_length; ++i) {
        int c = (unsigned char)text[i];
        for (int j = 0; j < length[c]; ++j) {
            encoded[pos++] = code[c][j];
        }
    }
    encoded[pos] = '\0';
    cout << "\nЗакодированный текст (по 64 бита в строке):\n";
    for (int i = 0; i < total_bits; ++i) {
        cout << encoded[i];
        if ((i + 1) % 64 == 0) {
            cout << '\n';
        }
    }
    if (total_bits % 64 != 0) {
        cout << '\n';
    }
    char* decoded = new char[text_length + 1];
    int decoded_length = 0;
    bool root_is_leaf = (nodes[root].left == -1 && nodes[root].right == -1);
    int v = root;
    for (int i = 0; i < total_bits; ++i) {
        if (root_is_leaf) {
            decoded[decoded_length++] = nodes[root].ch;
            continue;
        }
        if (encoded[i] == '0') {
            v = nodes[v].left;
        } else {
            v = nodes[v].right;
        }
        if (nodes[v].left == -1 && nodes[v].right == -1) {
            decoded[decoded_length++] = nodes[v].ch;
            v = root;
        }
    }
    decoded[decoded_length] = '\0';
    bool same = (decoded_length == text_length);
    for (int i = 0; same && i < text_length; ++i) {
        if (decoded[i] != text[i]) {
            same = false;
        }
    }
    cout << "\nДекодированный текст:\n" << decoded << '\n';
    cout << "Проверка: " << (same ? "текст восстановлен верно" : "ОШИБКА ДЕКОДИРОВАНИЯ") << '\n';
    int original_bits = text_length * 8;
    cout << "\n РЕЗУЛЬТАТ \n";
    cout << "Размер в исходном виде (8 бит на символ): " << original_bits << " бит\n";
    cout << "Размер после сжатия: " << total_bits << " бит\n";
    if (original_bits > 0) {
        cout.setf(ios::fixed);
        cout.precision(2);
        cout << "Степень сжатия: " << (double)original_bits / total_bits << " раза\n";
        cout << "Экономия: " << (1.0 - (double)total_bits / original_bits) * 100.0 << " %\n";
    }
    for (int c = 0; c < MAX_CHARS; ++c) {
        delete[] code[c];
    }
    delete[] code;
    delete[] length;
    delete[] buffer;
    delete[] encoded;
    delete[] decoded;
    delete[] freq;
    delete[] nodes;
    delete[] roots;
    return 0;
}
