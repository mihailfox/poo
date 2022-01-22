#include "menu.h"
#include <sstream>
#include <stdexcept>

menu::menu() { }

menu::menu(string header, vector<menuItem> menuItems) {
    if(header.empty() || menuItems.empty())
    {
        throw invalid_argument("Received an empty or invalid argument!");
    }

    this->header = header;
    this->menuItems = menuItems;
}

string menu::toString() {
    stringstream menu;
    menu << header << endl;

    for (int i = 0; i < menuItems.size(); ++i) {
        menu << menuItems[i].toString() << endl;
    }

    menu << exitItem.toString() << endl;

    menu << endl;
    menu << "Please select an option: ";
    menu << endl;

    return menu.str();
}

void menu::setExitItem(menuItem exitItem) {
    this->exitItem = exitItem;
}

menuItem menu::getExitItem() {
    return exitItem;
}

menu::~menu() {
    this->header.clear();
    this->menuItems.clear();
}


