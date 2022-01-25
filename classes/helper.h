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
    static void execute(void *function);
    static void clearScreen();
    static string promptString();
    static string promptString(const string& message);
    static void wait();
    static string boolToStr(bool input);
    static bool strToBool(string input);
};


#endif //POO_HELPER_H
