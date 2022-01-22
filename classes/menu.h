#ifndef POO_MENU_H
#define POO_MENU_H

#include <vector>
#include "menuItem.h"


class menu {
private:
    string header;
    vector<menuItem> menuItems;
    menuItem exitItem;
public:
    menu();
    menu(string header, vector<menuItem> menuItems);
    void setExitItem(menuItem exitItem);
    menuItem getExitItem();
    string toString();
    ~menu();
};


#endif //POO_MENU_H
