#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
using namespace std;
bool check_brackets(const string& str) {
    stack<char> bracket_stack;
    unordered_map<char, char> brackets = {
        {')', '('},
        {']', '['},
        {'}', '{'}
    };
    unordered_map<char, bool> opening = {
        {'(', true},
        {'[', true},
        {'{', true}
    };
    for (char ch : str) {
        if (opening.find(ch) != opening.end()) {
            bracket_stack.push(ch);
        } 
        else if (brackets.find(ch) != brackets.end()) {
            if (bracket_stack.empty() || bracket_stack.top() != brackets[ch]) {
                return false;
            }
            bracket_stack.pop();
        }
    }
    return bracket_stack.empty();
}
int main() {
    string input_line = "{([x1,x2],[y1,y2])}";
    if (check_brackets(input_line)) {
        cout << "Правильно" << endl;
    } else {
        cout << "Неправильно" << endl;
    }
    return 0;
}