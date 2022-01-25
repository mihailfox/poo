#ifndef POO_MENUITEM_H
#define POO_MENUITEM_H

#include <string>

using namespace std;

class menuItem {
protected:
    string itemId;
    string label;
    void *action;
public:
    menuItem();
    menuItem(string itemId, string label, void *action);

    void setItemId(string itemId);
    string getItemId();

    void setLabel(string label);
    string getLabel();

    void setAction(void *action);
    void *getAction();

    string toString();

    bool isInitialized();

    bool operator==(const menuItem &rhs) const;

    bool operator!=(const menuItem &rhs) const;

    ~menuItem();

};


#endif //POO_MENUITEM_H
