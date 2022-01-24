
#include <iostream>
#include <vector>
#include "classes/Carte.h"
#include "classes/csvFile.h"
#include "classes/menuItem.h"
#include "classes/menu.h"
#include "classes/bibliotecaManager.h"
#include "classes/domainManager.h"

using namespace std;

vector<menuItem> createMenuItems();
void exitApp();
void execute(void *function);
void initMenu();
void app();
void wait();
bibliotecaManager biblioteca;
domainManager domains;
void initMenu();
int getInteger();
void printBooks(vector<Carte> books);
string getString(string message);

int main() {
    try {
        biblioteca = bibliotecaManager("carti.in", ';');
        domains = domainManager("domenii.in", ';');
        initMenu();


    }
    catch (exception ex) {
        cout << ex.what();
    }


//    biblioteca.lendCarte("BB 421");
//    biblioteca.lendCarte("BB 420");

//    biblioteca.getAllBooksPastReturnDate();
//    biblioteca.deleteCarte("BB 420");
//    biblioteca.findCarte("Doi chiori");

//    biblioteca.saveCarti();



    //    ((void(*)())menuItems[0].getAction())();

//    execute(menuItems[0].getAction());


//    cout << menuItems[0].getAction();
//    cout << endl;
//    cout << mainMenu.getExitItem().getAction();

    biblioteca.saveCarti();
    domains.saveDomains();
    return 0;
}

void initMenu() {
    vector<menuItem> menuItems = createMenuItems();
    menu mainMenu("Biblioteca", menuItems);
    mainMenu.setExitItem(menuItem("0","Exit",exitApp,0));


    int choice;
    do {
        system("cls");
        // system("clear); // for linux OS

        cout << mainMenu.toString();
        choice = getInteger();
        for (int i = 0; i < menuItems.size(); ++i) {
            if (menuItems[i].getConsoleKey() == choice) {
                execute(menuItems[i].getAction());
                wait();
                break;
            }
        }

    } while (choice != mainMenu.getExitItem().getConsoleKey() || !cin);
}

int getInteger()
{
    int input;
    cin >> input;

    while (!cin.good())
    {
        cout << "Invalid input!" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> input;
    }
    return input;
}

//void app() {
//    vector<Carte> carti;
//    vector<vector<string>> temp;
//
//    csvFile test;
//
//    try {
//        test.setFilename("carti.in");
//        test.setFieldDelimiter(',');
//
//        temp = test.getFileContent();
//
//        for (int i = 0; i < temp.size(); ++i) {
//            carti.push_back(Carte(temp[i]));
//        }
//
//        cout << "#### Carti ####" << endl;
//        cout << carti.size() << endl;
//
//        for (int i = 0; i < carti.size(); ++i) {
//            carti[i].printDetails();
//            cout << endl;
//        }
//    }
//    catch (exception ex) {
//        cout << ex.what();
//    }
//}

void exitApp() {
    return;
}

void loadData() {
    biblioteca.loadBooks();
    domains.loadDomains();
}

void findBooks() {
    string input = getString("Input search term: ");

    vector<Carte> foundBooks = biblioteca.findCarte(input);

    if (foundBooks.size() == 0) {
        cout << "No books found for search term " << input << endl;
        return;
    }

    printBooks(foundBooks);
}

void printBooks(vector<Carte> books) {
    for (int i = 0; i < books.size(); ++i) {
        books[i].printDetails();
        cout << endl;
    }
}

void deleteBook() {
    string input = getString("Input cota: ");

    if (biblioteca.deleteCarte(input)) {
        domains.deleteCotaFromDomain(input);
        cout << "Book with cota " << input << " has been successfully deleted" << endl;
    } else {
        cout << "No book found with cota " << input << endl;
    }
}

void lendBook() {
    string input = getString("Input cota: ");

    if (biblioteca.lendCarte(input)) {
        cout << "Book with cota " << input << " has been lend" << endl;
    } else {
        cout << "Book not found or book already lend" << endl;
    }
}

void returnBook() {
    string input = getString("Input cota: ");

    if (biblioteca.returnCarte(input)) {
        cout << "Book with cota " << input << " has been returned" << endl;
    } else {
        cout << "Book not found or book already returned" << endl;
    }
}

void checkLendBooks() {
    vector<Carte> books = biblioteca.getAllBooksPastReturnDate();

    if (books.empty()) {
        cout << "No books found past return date" << endl;
        return;
    }
    printBooks(books);
}

void createNewDomain() {
    string domainName = getString("Input new domain name: ");

    if (domains.addDomain(domainName)) {
        cout << "Domain added" << endl;
    } else {
        cout << "Domain already exists" << endl;
    }
}

void addBookToDomain() {
    Carte carte;

    cout<<endl;
    string domainName = getString("Input existing domain: ");

    string temp = getString("Input book title: ");
    carte.setTitlu(temp);
    temp = getString("Input book author: ");
    carte.setAutor(temp);
    temp = getString("Input book cota: ");
    carte.setCota(temp);

    if (biblioteca.addBook(carte)) {
        cout << "Book added" << endl;
    } else {
        cout << "A book with same cota already exists" << endl;
        return;
    }

    if (domains.addCotaToDomain(carte, domainName)) {
        cout << "Book has been added to domain" << endl;
    } else {
        biblioteca.deleteCarte(carte.getCota());
        cout << "Domain does not exist" << endl;
    }
}

void execute(void *function) {
    ((void(*)())function)();
}

vector<menuItem> createMenuItems() {
    vector<menuItem> menuItems;

    menuItems.push_back(menuItem("1", "Load data", loadData, 1));
    menuItems.push_back(menuItem("2", "Create new domain", createNewDomain, 2));
    menuItems.push_back(menuItem("3", "Add book to domain", addBookToDomain, 3));
    menuItems.push_back(menuItem("4", "Search books by title or author", findBooks, 4));
    menuItems.push_back(menuItem("5", "Delete book", deleteBook, 5));
    menuItems.push_back(menuItem("6", "Lend book", lendBook, 6));
    menuItems.push_back(menuItem("7", "Return book", returnBook, 7));
    menuItems.push_back(menuItem("8", "Check loaned books return term", checkLendBooks, 8));

    return menuItems;
}

void wait()
{
    cout << endl;
    cout << "Press ENTER to continue...";
    cin.ignore();
    cin.get();
}

string getString(string message) {
    string output;
    cout << message << endl;

//    cin.clear();
//    cin.ignore(/*numeric_limits<streamsize>::max(), '\n'*/);

    getline(cin, output);
//    cin >> output;

    return  output;
}

