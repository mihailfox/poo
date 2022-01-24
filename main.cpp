#include <iostream>
#include <vector>
#include "classes/book.h"
#include "classes/menuItem.h"
#include "classes/menu.h"
#include "classes/booksManager.h"
#include "classes/domainsManager.h"

using namespace std;

vector<menuItem> createMenuItems();
void exitApp();
void execute(void *function);
void initMenu();
void wait();
booksManager biblioteca;
domainsManager domains;
void initMenu();
void printBooks(vector<book> books);
string getInput();
string getInput(string message);

int main() {
    try {
        biblioteca = booksManager("books.in", ';');
        domains = domainsManager("domenii.in", ';');
        initMenu();


    }
    catch (exception ex) {
        cout << ex.what();
    }


    biblioteca.saveBooks();
    domains.saveDomains();
    return 0;
}

void initMenu() {
    vector<menuItem> menuItems = createMenuItems();
    menu mainMenu("Biblioteca", menuItems);
    mainMenu.setExitItem(menuItem("0","Exit",exitApp,"0"));


    string choice;
    do {
        system("cls");
        // system("clear); // for linux OS

        cout << mainMenu.toString();
        choice = getInput();
        for (int i = 0; i < menuItems.size(); ++i) {
            if (menuItems[i].getConsoleKey() == choice) {
                execute(menuItems[i].getAction());
                wait();
                break;
            }
        }

    } while (choice != mainMenu.getExitItem().getConsoleKey());
}

string getInput()
{
    string input;
    getline(cin, input);

    return input;
}


void exitApp() {
    return;
}

void loadData() {
    biblioteca.loadBooks();
    domains.loadDomains();
}

void findBooks() {
    string input = getInput("Input search term: ");

    vector<book> foundBooks = biblioteca.findBook(input);

    if (foundBooks.size() == 0) {
        cout << "No books found for search term " << input << endl;
        return;
    }

    printBooks(foundBooks);
}

void printBooks(vector<book> books) {
    for (int i = 0; i < books.size(); ++i) {
        books[i].printDetails();
        cout << endl;
    }
}

void deleteBook() {
    string input = getInput("Input id: ");

    if (biblioteca.deleteBook(input)) {
        domains.removeFromDomain(input);
        cout << "Book with id " << input << " has been successfully deleted" << endl;
    } else {
        cout << "No book found with id " << input << endl;
    }
}

void lendBook() {
    string input = getInput("Input id: ");

    if (biblioteca.lendBook(input)) {
        cout << "Book with id " << input << " has been lend" << endl;
    } else {
        cout << "Book not found or book already lend" << endl;
    }
}

void returnBook() {
    string input = getInput("Input id: ");

    if (biblioteca.returnBook(input)) {
        cout << "Book with id " << input << " has been returned" << endl;
    } else {
        cout << "Book not found or book already returned" << endl;
    }
}

void checkLendBooks() {
    vector<book> books = biblioteca.getAllBooksPastReturnDate();

    if (books.empty()) {
        cout << "No books found past return date" << endl;
        return;
    }
    printBooks(books);
}

void createNewDomain() {
    string domainName = getInput("Input new domain name: ");

    if (domains.addDomain(domainName)) {
        cout << "domain added" << endl;
    } else {
        cout << "domain already exists" << endl;
    }
}

void addBookToDomain() {
    book carte;

    cout<<endl;
    string domainName = getInput("Input existing domain: ");

    string temp = getInput("Input book title: ");
    carte.setTitle(temp);
    temp = getInput("Input book author: ");
    carte.setAuthor(temp);
    temp = getInput("Input book id: ");
    carte.setId(temp);

    if (!biblioteca.addBook(carte)) {
        cout << "A book with same id already exists" << endl;
        return;
    }

    if (domains.addToDomain(carte, domainName)) {
        cout << "Book has been added to domain" << endl;
    } else {
        biblioteca.deleteBook(carte.getId());
        cout << "Domain does not exist" << endl;
    }
}

void execute(void *function) {
    ((void(*)())function)();
}

vector<menuItem> createMenuItems() {
    vector<menuItem> menuItems;

    menuItems.push_back(menuItem("1", "Load data", loadData, "1"));
    menuItems.push_back(menuItem("2", "Create new domain", createNewDomain, "2"));
    menuItems.push_back(menuItem("3", "Add book to domain", addBookToDomain, "3"));
    menuItems.push_back(menuItem("4", "Search books by title or author", findBooks, "4"));
    menuItems.push_back(menuItem("5", "Delete book", deleteBook, "5"));
    menuItems.push_back(menuItem("6", "Lend book", lendBook, "6"));
    menuItems.push_back(menuItem("7", "Return book", returnBook, "7"));
    menuItems.push_back(menuItem("8", "Check loaned books return term", checkLendBooks, "8"));

    return menuItems;
}

void wait()
{
    cout << "Press ENTER to continue...";
    cin.ignore();
}

string getInput(string message) {
    cout << message << endl;

    return getInput();
}

