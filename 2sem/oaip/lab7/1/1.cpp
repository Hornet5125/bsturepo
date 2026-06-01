#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;
struct Node {
    char data;
    Node* left;
    Node* right;
    Node(char d) : data(d), left(nullptr), right(nullptr) {}
};
void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}
int compute(Node* root) {
    if (!root->left && !root->right) return root->data - '0';
    int leftVal = compute(root->left);
    int rightVal = compute(root->right);
    if (root->data == '+') return leftVal + rightVal;
    if (root->data == '-') return leftVal - rightVal;
    if (root->data == '*') return leftVal * rightVal;
    return 0;
}
Node* buildFromString(const string& s, int& pos) {
    if (isdigit(s[pos])) {
        return new Node(s[pos++]);
    }
    if (s[pos] == '(') {
        pos++;
        Node* left = buildFromString(s, pos);
        char op = s[pos++];
        Node* right = buildFromString(s, pos);
        pos++;
        Node* root = new Node(op);
        root->left = left;
        root->right = right;
        return root;
    }
    return nullptr;
}
Node* buildFromFile(const string& filename) {
    ifstream file(filename);
    string formula;
    getline(file, formula);
    file.close();
    int pos = 0;
    return buildFromString(formula, pos);
}
void printTree(Node* root) {
    if (!root->left && !root->right) {
        cout << root->data;
        return;
    }
    cout << "(";
    printTree(root->left);
    cout << root->data;
    printTree(root->right);
    cout << ")";
}
bool isFormulaTree(Node* root) {
    if (!root) return false;
    if (!root->left && !root->right) {
        return isdigit(root->data);
    }
    if (root->left && root->right) {
        return (root->data == '+' || root->data == '-' || root->data == '*') &&
               isFormulaTree(root->left) && isFormulaTree(root->right);
    }
    return false;
}
int main() {
    Node* tree = buildFromFile("formula.txt");
    if (isFormulaTree(tree)) {
        cout << "Value: " << compute(tree) << endl;
        cout << "Formula: ";
        printTree(tree);
        cout << endl;
    }
    deleteTree(tree);
    return 0;
}