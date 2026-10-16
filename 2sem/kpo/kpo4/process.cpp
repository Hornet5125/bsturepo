#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;
bool is_keyword(const string& code, size_t pos, const string& word) {
    if (code.compare(pos, word.size(), word) != 0) {
        return false;
    }
    if (pos + word.size() < code.size() && (isalnum(code[pos + word.size()]) || code[pos + word.size()] == '_')) {
        return false;
    }
    return true;
}
size_t skip_spaces(const string& code, size_t pos) {
    while (pos < code.size() && isspace(code[pos])) {
        pos++;
    }
    return pos;
}
size_t find_skobka(const string& code, size_t pos) {
    int count = 1;
    for (size_t i = pos + 1; i < code.size(); ++i) {
        if (code[i] == '(') {
            count++;
        } 
        else if (code[i] == ')') {
            count--;
            if (count == 0) {
                return i;
            }
        }
    }
    return string::npos;
}
size_t find_block_end(const string& code, size_t pos) {
    int paren_balance = 0;
    for (size_t i = pos; i < code.size(); ++i) {
        if (code[i] == '(') {
            paren_balance++;
        } 
        else if (code[i] == ')') {
            paren_balance--;
        } 
        else if (code[i] == ';' && paren_balance == 0) {
            return i;
        }
    }
    return string::npos;
}
string add_braces(const string& code) {
    string result;
    size_t i = 0;
    while (i < code.size()) {
        string keyword;
        if (is_keyword(code, i, "if")) {
            keyword = "if";
        } 
        else if (is_keyword(code, i, "else")) {
            keyword = "else";
        } 
        else if (is_keyword(code, i, "while")) {
            keyword = "while";
        } 
        else if (is_keyword(code, i, "for")) {
            keyword = "for";
        }
        if (keyword.empty()) {
            result += code[i];
            i++;
            continue;
        }
        result += keyword;
        i += keyword.size();
        size_t old_i = i;
        i = skip_spaces(code, i);
        result += code.substr(old_i, i - old_i);
        if (keyword != "else" && i < code.size() && code[i] == '(') {
            size_t close_pos = find_skobka(code, i);
            result += code.substr(i, close_pos - i + 1);
            i = close_pos + 1;
        }
        old_i = i;
        i = skip_spaces(code, i);
        result += code.substr(old_i, i - old_i);
        if (i < code.size() && code[i] == '{') {
            continue;
        }
        size_t end = find_block_end(code, i);
        if (end == string::npos) {
            continue;
        }
        string block = code.substr(i, end - i + 1);
        block = add_braces(block);
        result += "{";
        result += block;
        result += "}";
        i = end + 1;
    }
    return result;
}
string format_code(const string& code) {
    string result;
    int indent = 0;
    int paren_balance = 0;
    bool in_string = false;
    bool new_line = true;
    bool skip_future_spaces = true;
    for (size_t i = 0; i < code.size(); ++i) {
        char c = code[i];
        if (c == '"' && (i == 0 || code[i - 1] != '\\')) {
            in_string = !in_string;
        }
        if (!in_string) {
            if (c == '(') {
                paren_balance++;
            }
            if (c == ')') {
                paren_balance--;
            }
        }
        if (c == '\n' || c == '\r') {
            skip_future_spaces = true;
            continue;
        }
        if (!in_string && skip_future_spaces && (c == ' ' || c == '\t')) {
            continue;
        }
        if (new_line) {
            result += string(indent * 4, ' ');
            new_line = false;
        }
        skip_future_spaces = false;
        if (!in_string && c == '>' && i > 0 && code[i - 1] != '-') {
            result += ">\n";
            new_line = true;
            skip_future_spaces = true;
            continue;
        }
        if (!in_string && c == '{') {
            result += "{\n";
            indent++;
            new_line = true;
            skip_future_spaces = true;
            continue;
        }
        if (!in_string && c == '}') {
            while (!result.empty() && (result.back() == '\n' || result.back() == ' ' || result.back() == '\t')) {
                result.pop_back();
            }
            result += '\n';
            indent--;
            result += string(indent * 4, ' ') + "}";
            if (i + 1 < code.size()) {
                result += '\n';
                new_line = true;
                skip_future_spaces = true;
            }
            continue;
        }
        if (!in_string && c == ';' && paren_balance == 0) {
            result += ";\n";
            new_line = true;
            skip_future_spaces = true;
            continue;
        }
        result += c;
    }
    return result;
}
int main() {
    ifstream input("input.c");
    string code((istreambuf_iterator<char>(input)), istreambuf_iterator<char>());
    input.close();
    code = add_braces(code);
    code = format_code(code);
    ofstream output("output.c");
    output << code;
    output.close();
    return 0;
}