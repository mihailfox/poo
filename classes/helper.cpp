#include "helper.h"
#include "sstream"
#include <iostream>
#include <string>

using namespace std;

string helper::toLower(string input) {
    stringstream output;
    for (int i = 0; i < input.size(); ++i) {
        output << tolower(input[i]);
    }

    return output.str();
}

bool helper::stringContains(string input, string pattern) {
    return helper::toLower(input).find(helper::toLower(pattern)) != string::npos;
}

bool helper::stringsEqual(string string1, string string2) {
    return toLower(string1) == toLower(string2);
}

void helper::execute(void *function) {
    ((void(*)())function)();
}

void helper::clearScreen() {
#ifdef _WIN32
    system("cls");
#elif defined(_UNIX)
    system("clear");
#endif
}

void helper::wait()
{
    cout << "Press ENTER to continue...";
    cin.ignore();
}

string helper::promptString()
{
    string input;
    getline(cin, input);

    return input;
}

string helper::promptString(const string& message) {
    cout << message << endl;

    return promptString();
}

bool helper::strToBool(string input) {
    if (input == "false") {
        return false;
    }
    return true;
}

string helper::boolToStr(bool input) {
    if (input == false)
    {
        return "false";
    }
    return "true";
}
