#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;


bool isValidDataType(const string& type) {
    return (type == "int" || type == "float" || type == "double" || type == "void" || type == "char");
}


bool isValidFunctionName(const string& name) {
    if (name.empty()) return false;
    if (!isalpha(name[0]) && name[0] != '_') return false;
    for (char c : name) {
        if (!isalnum(c) && c != '_') return false;
    }
    return true;
}

bool isValidFunction(const string& function) {

    string trimmed = function;
    size_t start = trimmed.find_first_not_of(" \t");
    size_t end = trimmed.find_last_not_of(" \t");

    if (start == string::npos || end == string::npos) return false;

    trimmed = trimmed.substr(start, end - start + 1);


    if (trimmed.empty()) return false;

    size_t returnTypeEnd = trimmed.find_first_of(" \t");
    if (returnTypeEnd == string::npos) return false;

    string returnType = trimmed.substr(0, returnTypeEnd);


    if (!isValidDataType(returnType)) {
        cout << "Error: Invalid data type '" << returnType << "'\n";
        return false;
    }

    size_t nameStart = trimmed.find_first_not_of(" \t", returnTypeEnd);
    size_t nameEnd = trimmed.find_first_of("(", nameStart);
    if (nameEnd == string::npos || nameStart == string::npos) return false;

    string functionName = trimmed.substr(nameStart, nameEnd - nameStart);

    // Check for valid function name
    if (functionName.empty() || !isValidFunctionName(functionName)) {
        cout << "Error: Invalid function name '" << functionName << "'\n";
        return false;
    }


    size_t paramStart = nameEnd + 1;
    size_t paramEnd = trimmed.find_first_of(")", paramStart);
    if (paramEnd == string::npos || paramStart == string::npos) return false;
    if (paramEnd - paramStart > 0 && trimmed[paramStart] != ' ') return false;


    size_t bodyStart = trimmed.find_first_of("{", paramEnd);
    size_t bodyEnd = trimmed.find_first_of("}", bodyStart);
    if (bodyStart == string::npos || bodyEnd == string::npos) return false;

    string functionBody = trimmed.substr(bodyStart + 1, bodyEnd - bodyStart - 1);

    functionBody.erase(remove_if(functionBody.begin(), functionBody.end(), ::isspace), functionBody.end());


    if (returnType == "void") {

        if (functionBody.empty() || functionBody == "return0;") {
            return true;
        }
    } else if (returnType == "int" || returnType == "float" || returnType == "double" || returnType == "char") {

        if (functionBody.find("return") == 0) {

            if (functionBody == "return0;") {
                return true;
            }
        }
    }

    return false;
}

int main() {
    string filePath = "D://Text.txt";  // Set the file path

    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file at " << filePath << "\n";
        return 1;
    }

    string line;
    int lineNumber = 1;
    while (getline(file, line)) {


        if (isValidFunction(line)) {
            cout << "Valid --> " << line << endl;
        } else {
            cout << "Error in line " << lineNumber << ": Invalid function declaration.\n";
        }
        lineNumber++;
    }

    file.close();
    return 0;
}
