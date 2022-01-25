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
    explicit menu(const string& header);

    void addMenuItem(menuItem item);

    menuItem getMenuItem(const string& id);

    unsigned int menuItemsCount();

    void setExitItem(const string& id);
    menuItem getExitItem();

    string toString();
    ~menu();
};


#endif //POO_MENU_H
