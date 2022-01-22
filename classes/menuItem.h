#ifndef POO_MENUITEM_H
#define POO_MENUITEM_H

#include <string>

using namespace std;

class menuItem {
protected:
    string itemId;
    string label;
    char consoleKey;
    void *function;
public:
    menuItem();
    menuItem(string itemId, string label, void *function, char consoleKey);

    void setItemId(string itemId);
    string getItemId();

    void setLabel(string label);
    string getLabel();

    void setConsoleKey(char consoleKey);
    char getConsoleKey();

    void setAction(void *function);
    void *getAction();

    string toString();

    ~menuItem();

};


#endif //POO_MENUITEM_H
