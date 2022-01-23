#include <iostream>
#include <vector>
#include "classes/Carte.h"
#include "classes/csvFile.h"
#include "classes/menuItem.h"
#include "classes/menu.h"
#include "classes/bibliotecaManager.h"

using namespace std;

vector<menuItem> createMenuItems();
void exitApp();
void execute(void *function);
void printMenu();
void app();

void printMenu();

int main() {
    printMenu();

    bibliotecaManager manager("carti.in", ',');
    manager.loadCarti();

    manager.lendCarte("BB 421");
    manager.lendCarte("BB 420");

//    manager.getAllBooksPastReturnDate();
//    manager.deleteCarte("BB 420");
//    manager.findCarte("Doi chiori");

    manager.saveCarti();



    //    ((void(*)())menuItems[0].getAction())();

//    execute(menuItems[0].getAction());


//    cout << menuItems[0].getAction();
//    cout << endl;
//    cout << mainMenu.getExitItem().getAction();


    return 0;
}

void printMenu() {
    menu mainMenu("Biblioteca", createMenuItems());
    mainMenu.setExitItem(menuItem("0","Exit",exitApp,'0'));

    cout << mainMenu.toString();
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
    menuItems.push_back(menuItem("2", "Create new domain", app, '2'));
    menuItems.push_back(menuItem("3", "Add book to domain", app, '3'));
    menuItems.push_back(menuItem("4", "Delete book", app, '4'));
    menuItems.push_back(menuItem("5", "Check loaned books return term", app, '1'));



    return menuItems;
}


