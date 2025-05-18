#include <iostream>
#include <fstream>
#include <stack>
#include <string>
using namespace std;
bool check_brackets_in_cpp(const string& file_path) {
    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Could not open the file " << file_path << endl;
        return false;
    }

    stack<char> bracket_stack;
    string line;
    int line_num = 0;
    bool balanced = true;

    while (getline(file, line)) {
        ++line_num;

        for (char ch : line) {
            if (ch == '(' || ch == '{' || ch == '[') {
                bracket_stack.push(ch);
            } else if (ch == ')' || ch == '}' || ch == ']') {
                if (bracket_stack.empty()) {
                    cout << "Line " << line_num << ": Unmatched closing bracket '" << ch << "' found." <<endl;
                    balanced = false;
                } else {
                    char top = bracket_stack.top();
                    if ((ch == ')' && top == '(') ||
                        (ch == '}' && top == '{') ||
                        (ch == ']' && top == '[')) {
                        bracket_stack.pop();
                    } else {
                        cout << "Line " << line_num << ": Mismatched closing bracket '" << ch << "' for opening '" << top << "'." << endl;
                        balanced = false;
                    }
                }
            }
        }
    }

    while (!bracket_stack.empty()) {
        char unmatched = bracket_stack.top();
        cout << "Unmatched opening bracket '" << unmatched << "' found." << endl;
        balanced = false;
        bracket_stack.pop();
    }

    if (balanced) {
        cout << "All parenthesis are properly defined." << endl;
    }

    file.close();
    return balanced;
}

int main() {
    string file_path = "inputFile.cpp";
    check_brackets_in_cpp(file_path);
    return 0;
}

