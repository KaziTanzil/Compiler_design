#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;
bool is_statement(const string& line) {
    string trimmed_line = line;
    size_t start = trimmed_line.find_first_not_of(" \t");

    if (start == string::npos) return false;
    trimmed_line = trimmed_line.substr(start);

    return !(trimmed_line == "int main()" ||
             trimmed_line.find("//") == 0 ||
             trimmed_line.find("/*") == 0 ||
             trimmed_line.find("#") == 0 ||
             trimmed_line == "{" || trimmed_line == "}" ||
             trimmed_line.find("if") == 0 ||
             trimmed_line.find("for") == 0 ||
             trimmed_line.find("while") == 0 ||
             trimmed_line.find("else") == 0 ||
             trimmed_line.find("switch") == 0 ||
             trimmed_line.find("do") == 0 ||
             trimmed_line.find("return") == 0);
}
bool missing_semicolon(const std::string& line) {
    size_t end = line.find_last_not_of(" \t");
    if (end == string::npos) return false;

    string trimmed_line = line.substr(0, end + 1);

    return is_statement(trimmed_line) && trimmed_line.back() != ';';
}
void check_semicolons_in_cpp(const string& file_path) {
    ifstream file(file_path);
    if (!file.is_open()) {
        cout << "Could not open the file " << file_path << endl;
        return;
    }

    string line;
    int line_num = 0;
    bool inside_main = false;
    bool issues_found = false;

    while (getline(file, line)) {
        ++line_num;

        if (line.find("int main()") != string::npos) {
            inside_main = true;
        }
        if (inside_main && missing_semicolon(line)) {
            cout << "Line " << line_num << ": Missing semicolon at the end of the statement." << endl;
            issues_found = true;
        }
        if (inside_main && line.find("}") != string::npos) {
            inside_main = false;
        }
    }

    if (!issues_found) {
       cout << "All statements in main() have semicolons at the end." << endl;
    }

    file.close();
}

int main() {
    string file_path = "inputFile.cpp";
    check_semicolons_in_cpp(file_path);
    return 0;
}
