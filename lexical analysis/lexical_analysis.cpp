#include <iostream>
#include <string>
#include<fstream>


using namespace std;


 string keywords[] = {
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "inline", "int", "long", "namespace", "new", "operator", "private",
    "protected", "public", "register", "return","while",
    "friend", "class", "include", "using", "cout"
};


 string operators[] = {
    "+", "-", "*", "/", "%", "++", "--", "==", "!=", "<", ">", "<=", ">=",
    "&&", "||", "&", "|", "^", "~", "<<", ">>", "=", "+=", "-=", "*=", "/=",
    "%=", "<<=", ">>=", "&=", "|=", "^="
};


 char punctuation[] = {
    '(', ')', '{', '}', '[', ']', ';', ',', '.', ':', '?', '!',
    '#', '@', '&', '\\', '/'
};


 int numKeywords = sizeof(keywords) / sizeof(keywords[0]);
 int numOperators = sizeof(operators) / sizeof(operators[0]);
 int numPunctuation = sizeof(punctuation) / sizeof(punctuation[0]);


bool isKeyword( string& word) {
    for (int i = 0; i < numKeywords; ++i) {
        if (keywords[i] == word) {
            return true;
        }
    }
    return false;
}


bool isIdentifier( string& word) {
    if (word.empty() || !((word[0] >= 'a' && word[0] <= 'z') ||
                          (word[0] >= 'A' && word[0] <= 'Z') ||
                          word[0] == '_')) {
        return false;
    }

    for (size_t i = 1; i < word.length(); i++) {
        if (!((word[i] >= 'a' && word[i] <= 'z') ||
               (word[i] >= 'A' && word[i] <= 'Z') ||
               (word[i] >= '0' && word[i] <= '9') ||
               word[i] == '_')) {
            return false;
        }
    }
    return true;
}


bool isPunctuation(char c) {
    for (int i = 0; i < numPunctuation; ++i) {
        if (punctuation[i] == c) {
            return true;
        }
    }
    return false;
}


bool isOperator( string& word) {
    for (int i = 0; i < numOperators; ++i) {
        if (operators[i] == word) {
            return true;
        }
    }
    return false;
}


void detectComponents(string& code) {
    string identifiers[100];
    string keywordsFound[100];
    string operatorsFound[100];
    char punctuationFound[100];
    int idCount = 0, kwCount = 0, opCount = 0, punCount = 0;

    string word;

    for (size_t i = 0; i < code.length(); ++i) {
        char c = code[i];

        if (isspace(c) || isPunctuation(c)) {
            if (!word.empty()) {

                if (isKeyword(word) && kwCount < 100) {
                    bool found = false;
                    for (int j = 0; j < kwCount; ++j) {
                        if (keywordsFound[j] == word) {
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        keywordsFound[kwCount++] = word;
                    }
                }

                else if (isIdentifier(word) && idCount < 100) {
                    bool found = false;
                    for (int j = 0; j < idCount; ++j) {
                        if (identifiers[j] == word) {
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        identifiers[idCount++] = word;
                    }
                }

                else if (isOperator(word) && opCount < 100) {
                    bool found = false;
                    for (int j = 0; j < opCount; ++j) {
                        if (operatorsFound[j] == word) {
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        operatorsFound[opCount++] = word;
                    }
                }
                word.clear();
            }

            if (isPunctuation(c) && punCount < 100) {
                bool found = false;
                for (int j = 0; j < punCount; ++j) {
                    if (punctuationFound[j] == c) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    punctuationFound[punCount++] = c;
                }
            }
        } else {
            word += c;
        }
    }

    cout << "Identifiers: ";
    for (int i = 0; i < idCount; ++i) {
        cout << identifiers[i];
        if (i < idCount - 1) {
            cout << ", ";
        }
    }
    cout << endl;

    cout << "Keywords: ";
    for (int i = 0; i < kwCount; ++i) {
        cout << keywordsFound[i];
        if (i < kwCount - 1) {
            cout << ", ";
        }
    }
    cout << endl;

    cout << "Operators: ";
    for (int i = 0; i < opCount; ++i) {
        cout << operatorsFound[i];
        if (i < opCount - 1) {
            cout << ", ";
        }
    }
    cout << endl;

    cout << "Punctuation: ";
    for (int i = 0; i < punCount; i++) {
        cout << punctuationFound[i];
        if (i < punCount - 2) {
            cout << "  ";
        }
    }
    cout << endl;
}

int main() {
   string x;
     string input;
    // Read from the text file
    ifstream MyReadFile("D://New//tanzil.txt");

      while (getline (MyReadFile,x))
    {


        input+=x;
    }


    MyReadFile.close();

    detectComponents(input);
    return 0;
}

