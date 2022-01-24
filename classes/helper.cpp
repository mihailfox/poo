#include "helper.h"
#include "sstream"

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
