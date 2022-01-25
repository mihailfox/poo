#include <sstream>
#include <stdexcept>
#include "menu.h"


menu::menu() = default;

menu::menu(const string& header) {
    if(header.empty())
    {
        throw invalid_argument("Received an empty or invalid argument!");
    }

    this->header = header;
}

void menu::addMenuItem(menuItem menuItem) {
    if(menuItem.isInitialized()) {
        this->menuItems.push_back(menuItem);
    }
}

menuItem menu::getMenuItem(const string& id) {
    for (int i = 0; i < menuItemsCount(); ++i) {
        if (menuItems[i].getItemId() == id) {
            return menuItems[i];
        }
    }
    return {};
}

unsigned int menu::menuItemsCount() {
    return menuItems.size();
}

string menu::toString() {
    stringstream menu;
    menu << header << endl;

    for (int i = 0; i < menuItems.size(); ++i) {
        menu << menuItems[i].toString() << endl;
    }

    menu << endl;

    return menu.str();
}

void menu::setExitItem(const string& id) {
    this->exitItem = getMenuItem(id);
}

menuItem menu::getExitItem() {
    return exitItem;
}

menu::~menu() {
    this->header.clear();
    this->menuItems.clear();
}


