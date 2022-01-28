#include <csignal>
#include <stdio.h>
#include "classes/book.h"
#include "classes/menuItem.h"
#include "classes/menu.h"
#include "classes/booksManager.h"
#include "classes/domainsManager.h"

const string booksFile = "carti.in";
const string domainsFile = "domenii.in";
const char csvFieldDelimiter = ';';

static booksManager libraryBooksManager;
static domainsManager libraryDomainsManager;
static menu mainMenu;

void initMenu();
void executeUserRequest();
void exitApp(int exitNum);
void findBooks();
void printBooks(vector<book> books);
void deleteBook();
void lendBook();
void returnBook();
void checkBorrowedBooks();
void createNewDomain();
void addBookToDomain();
void loadData();
void saveData();

int main() {
    try {

        libraryBooksManager = booksManager(booksFile, csvFieldDelimiter);
        libraryDomainsManager = domainsManager(domainsFile, csvFieldDelimiter);
        initMenu();
        executeUserRequest();
    }
    catch (exception &ex) {
        cout << ex.what();
    }

    return 0;
}

void initMenu() {
    mainMenu = menu("Biblioteca");
    mainMenu.add(menuItem("1", "Load data", (void *) loadData));
    mainMenu.add(menuItem("2", "Create new domain", (void *) createNewDomain));
    mainMenu.add(menuItem("3", "Add book to domain", (void *) addBookToDomain));
    mainMenu.add(menuItem("4", "Search books by title or author", (void *) findBooks));
    mainMenu.add(menuItem("5", "Delete book", (void *) deleteBook));
    mainMenu.add(menuItem("6", "Lend book", (void *) lendBook));
    mainMenu.add(menuItem("7", "Return book", (void *) returnBook));
    mainMenu.add(menuItem("8", "Check loaned books return term", (void *) checkBorrowedBooks));
    mainMenu.add(menuItem("0", "Exit", (void *) exitApp));
    mainMenu.setExitItem("0");
}

void executeUserRequest() {
    string choice;
    do {
        helper::clearScreen();

        cout << mainMenu.toString();
        choice = helper::promptString("Please select an option: ");

        signal(SIGINT, exitApp);

        menuItem temp = mainMenu.getMenuItem(choice);

        if (temp.isInitialized() == false) {
            cout << "Invalid option!" << endl;
            helper::wait();
            continue;
        }

        if (temp == mainMenu.getExitItem()) {
            helper::execute(temp.getAction());
            return;
        }

        helper::execute(temp.getAction());
        helper::wait();

    } while (true);
}

void exitApp(int exitNum) {
    saveData();

    cout << endl;
    cout << "Exiting application..." << endl;

    exit(exitNum);
}

void loadData() {
    libraryBooksManager.load();
    libraryDomainsManager.load();

    cout << "Loaded " << libraryBooksManager.countBooks() << " books from ";
    cout << libraryDomainsManager.countDomains() << " domains!" << endl;
}

void saveData() {
    libraryBooksManager.save();
    libraryDomainsManager.save();
}

void findBooks() {
    cout << "Find books" << endl;

    string input = helper::promptString("Input search term: ");

    vector<book> foundBooks = libraryBooksManager.findBook(input);

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

    string input = helper::promptString("Input id: ");

    if (libraryBooksManager.deleteBook(input)) {
        libraryDomainsManager.removeFromDomain(input);
        cout << "Book with id " << input << " has been successfully deleted" << endl;
    } else {
        cout << "No book found with id " << input << endl;
    }
}

void lendBook() {
    cout << "Lend book" << endl;

    string input = helper::promptString("Input id: ");

    if (libraryBooksManager.lendBook(input)) {
        cout << "Book with id " << input << " has been lend" << endl;
    } else {
        cout << "Book not found or book already lend" << endl;
    }
}

void returnBook() {
    cout << "Return book" << endl;

    string input = helper::promptString("Input id: ");

    if (libraryBooksManager.returnBook(input)) {
        cout << "Book with id " << input << " has been returned" << endl;
    } else {
        cout << "Book not found or book already returned" << endl;
    }
}

void checkBorrowedBooks() {
    cout << "Past due date books" << endl;

    vector<book> books = libraryBooksManager.getAllBooksPastReturnDate();

    if (books.empty()) {
        cout << "No books found past return date" << endl;
        return;
    }
    printBooks(books);
}

void createNewDomain() {
    cout << "Create new domain" << endl;

    string domainName;
    do {
        domainName = helper::promptString("Input new domain name: ");
        if(libraryDomainsManager.find(domainName)) {
            cout << "Domain name already exists!" << endl;
            continue;
        }

        break;
    } while (true);

    if (libraryDomainsManager.addDomain(domainName)) {
        cout << "Domain added" << endl;
    } else {
        cout << "An error has occurred" << endl;
    }
}

void addBookToDomain() {
    cout << "Add new book" << endl;

    book newBook;

    string domainName;
    do {
        domainName = helper::promptString("Input existing domain: ");
    } while (libraryDomainsManager.find(domainName) == false);

    string bookId;
    do {
        bookId = helper::promptString("Input book id: ");

        if(libraryBooksManager.findBookId(newBook.getId()) == false) {
            newBook.setId(bookId);
            break;
        }

        cout << "A book with same id already exists" << endl;
    } while (true);

    newBook.setTitle(helper::promptString("Input book title: "));
    newBook.setAuthor(helper::promptString("Input book author: "));

    if (libraryBooksManager.addBook(newBook) &&
        libraryDomainsManager.addToDomain(newBook, domainName)) {
        cout << "Book has been added to domain" << endl;
    } else {
        cout << "An error has occurred!" << endl;
    }
}
