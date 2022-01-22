#include <iostream>
#include <vector>
#include "classes/Carte.h"
#include "classes/csvFile.h"
#include "classes/menuItem.h"
#include "classes/menu.h"

using namespace std;

vector<menuItem> createMenuItems();
void exitApp();
void execute(void *function);
void app();

int main() {
    vector<menuItem> menuItems = createMenuItems();
    menu mainMenu("Biblioteca",menuItems);
    mainMenu.setExitItem(menuItem("0","Exit",exitApp,'0'));

    cout << mainMenu.toString();

//    ((void(*)())menuItems[0].getAction())();

    execute(menuItems[0].getAction());


//    cout << menuItems[0].getAction();
//    cout << endl;
//    cout << mainMenu.getExitItem().getAction();


    return 0;
}

void app() {
    vector<Carte> carti;
    vector<vector<string>> temp;

    csvFile test;

    try {
        test.setFilename("carti.in");
        test.setFieldDelimiter(',');

        temp = test.getFileContent();

        for (int i = 0; i < temp.size(); ++i) {
            carti.push_back(Carte(temp[i]));
        }

        cout << "#### Carti ####" << endl;
        cout << carti.size() << endl;

        for (int i = 0; i < carti.size(); ++i) {
            carti[i].printDetails();
            cout << endl;
        }
    }
    catch (exception ex) {
        cout << ex.what();
    }
}

void exitApp() {
    exit(0);
}

void execute(void *function) {
    ((void(*)())function)();
}

vector<menuItem> createMenuItems() {
    vector<menuItem> menuItems;

    menuItems.push_back(menuItem("1", "Load carti.in", app, '1'));

    return menuItems;
}


