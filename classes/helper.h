#ifndef POO_HELPER_H
#define POO_HELPER_H

#include <string>

using namespace std;

class helper {
private:
    static string toLower(string input);
public:
    static bool stringContains(string input, string pattern);
    static bool stringsEqual(string string1, string string2);
};


#endif //POO_HELPER_H
