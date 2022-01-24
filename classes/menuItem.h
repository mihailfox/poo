#ifndef POO_MENUITEM_H
#define POO_MENUITEM_H

#include <string>

using namespace std;

class menuItem {
protected:
    string itemId;
    string label;
    int consoleKey;
    void *function;
public:
    menuItem();
    menuItem(string itemId, string label, void *function, int consoleKey);

    void setItemId(string itemId);
    string getItemId();

    void setLabel(string label);
    string getLabel();

    void setConsoleKey(int consoleKey);
    int getConsoleKey();

    void setAction(void *function);
    void *getAction();

    string toString();

    ~menuItem();

};


#endif //POO_MENUITEM_H
