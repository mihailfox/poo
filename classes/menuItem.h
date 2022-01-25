#ifndef POO_MENUITEM_H
#define POO_MENUITEM_H

#include <string>

using namespace std;

class menuItem {
protected:
    string itemId;
    string label;
    void *function;
public:
    menuItem();
    menuItem(string itemId, string label, void *function);

    void setItemId(string itemId);
    string getItemId();

    void setLabel(string label);
    string getLabel();

    void setAction(void *function);
    void *getAction();

    string toString();

    bool isInitialized();

    bool operator==(const menuItem &rhs) const;

    bool operator!=(const menuItem &rhs) const;

    ~menuItem();

};


#endif //POO_MENUITEM_H
