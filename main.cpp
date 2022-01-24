#include <iostream>
#include <vector>
#include "classes/book.h"
#include "classes/menuItem.h"
#include "classes/menu.h"
#include "classes/booksManager.h"
#include "classes/domainsManager.h"
#include "classes/helper.h"

using namespace std;

booksManager library;
domainsManager domains;
menu mainMenu;
bool dataLoaded = false;

void initMenu();
void executeUserRequest();
void clearScreen();
void wait();

void exitApp();
void findBooks();
void printBooks(vector<book> books);
void deleteBook();
void lendBook();
void returnBook();
void checkBorrowedBooks();
void createNewDomain();
void addBookToDomain();
void loadData();
string promptString();
string promptString(const string& message);

int main() {
    try {
        library = booksManager("carti.in", ';');
        domains = domainsManager("domenii.in", ';');
        initMenu();
        executeUserRequest();
    }
    catch (exception ex) {
        cout << ex.what();
    }

    if (dataLoaded) {
        library.save();
        domains.saveDomains();
    }

    return 0;
}

void initMenu() {
    mainMenu = menu("Biblioteca");
    mainMenu.addMenuItem(menuItem("1", "Load data", loadData));
    mainMenu.addMenuItem(menuItem("2", "Create new domain", createNewDomain));
    mainMenu.addMenuItem(menuItem("3", "Add book to domain", addBookToDomain));
    mainMenu.addMenuItem(menuItem("4", "Search books by title or author", findBooks));
    mainMenu.addMenuItem(menuItem("5", "Delete book", deleteBook));
    mainMenu.addMenuItem(menuItem("6", "Lend book", lendBook));
    mainMenu.addMenuItem(menuItem("7", "Return book", returnBook));
    mainMenu.addMenuItem(menuItem("8", "Check loaned books return term", checkBorrowedBooks));
    mainMenu.addMenuItem(menuItem("0","Exit",exitApp));
    mainMenu.setExitItem("0");
}

void executeUserRequest() {
    string choice;
    do {
        clearScreen();

        cout << mainMenu.toString();
        choice = promptString();

        menuItem temp = mainMenu.getMenuItem(choice);
        if (temp == mainMenu.getExitItem()) {
            helper::execute(temp.getAction());
            return;
        }

        if (temp.getItemId().empty()) {
            cout << "Invalid option!" << endl;
            wait();
            continue;
        }

        helper::execute(temp.getAction());
        wait();

    } while (true);
}

void exitApp() {
    cout << "Exiting application..." << endl;
    return;
}


void loadData() {
    library.load();
    domains.load();

    dataLoaded = true;

    cout << "Loaded " << library.countBooks() << " books from ";
    cout << domains.countDomains() << " domains!" << endl;
}

void findBooks() {
    cout << "Find books" << endl;

    string input = promptString("Input search term: ");

    vector<book> foundBooks = library.findBook(input);

    if (foundBooks.empty()) {
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
    cout << "Delete book" << endl;

    string input = promptString("Input id: ");

    if (library.deleteBook(input)) {
        domains.removeFromDomain(input);
        cout << "Book with id " << input << " has been successfully deleted" << endl;
    } else {
        cout << "No book found with id " << input << endl;
    }
}

void lendBook() {
    cout << "Lend book" << endl;

    string input = promptString("Input id: ");

    if (library.lendBook(input)) {
        cout << "Book with id " << input << " has been lend" << endl;
    } else {
        cout << "Book not found or book already lend" << endl;
    }
}

void returnBook() {
    cout << "Return book" << endl;

    string input = promptString("Input id: ");

    if (library.returnBook(input)) {
        cout << "Book with id " << input << " has been returned" << endl;
    } else {
        cout << "Book not found or book already returned" << endl;
    }
}

void checkBorrowedBooks() {
    cout << "Past due date books" << endl;

    vector<book> books = library.getAllBooksPastReturnDate();

    if (books.empty()) {
        cout << "No books found past return date" << endl;
        return;
    }
    printBooks(books);
}

void createNewDomain() {
    cout << "Create new domain" << endl;

    string domainName = promptString("Input new domain name: ");

    if (domains.addDomain(domainName)) {
        cout << "domain added" << endl;
    } else {
        cout << "domain already exists" << endl;
    }
}

void addBookToDomain() {
    cout << "Add new book" << endl;

    book carte;

    cout<<endl;
    string domainName = promptString("Input existing domain: ");

    carte.setTitle(promptString("Input book title: "));
    carte.setAuthor(promptString("Input book author: "));
    carte.setId(promptString("Input book id: "));

    if (!library.addBook(carte)) {
        cout << "A book with same id already exists" << endl;
        return;
    }

    if (domains.addToDomain(carte, domainName)) {
        cout << "Book has been added to domain" << endl;
    } else {
        library.deleteBook(carte.getId());
        cout << "Domain does not exist" << endl;
    }
}


void clearScreen() {
#ifdef _WIN32
    system("cls");
#elif defined(_UNIX)
    system("clear");
#endif
}

void wait()
{
    cout << "Press ENTER to continue...";
    cin.ignore();
}

string promptString()
{
    string input;
    getline(cin, input);

    return input;
}

string promptString(const string& message) {
    cout << message << endl;

    return promptString();
}

