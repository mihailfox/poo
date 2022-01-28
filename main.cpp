#include "classes/book.h"
#include "classes/menuItem.h"
#include "classes/menu.h"
#include "classes/booksManager.h"
#include "classes/domainsManager.h"

const string booksFile = "carti.in";
const string domainsFile = "domenii.in";
const char csvFieldDelimiter = ';';

booksManager libraryBooksManager;
domainsManager libraryDomainsManager;
menu mainMenu;

bool dataLoaded = false;

void initMenu();
void executeUserRequest();
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

    saveData();
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

void exitApp() {
    if(dataLoaded) {
        saveData();
    }

    cout << "Exiting application..." << endl;
    exit(0);
}

void loadData() {
    libraryBooksManager.load();
    libraryDomainsManager.load();

    dataLoaded = true;

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

    string domainName = helper::promptString("Input new domain name: ");

    if (libraryDomainsManager.addDomain(domainName)) {
        cout << "domain added" << endl;
    } else {
        cout << "domain already exists" << endl;
    }
}

void addBookToDomain() {
    cout << "Add new book" << endl;

    book carte;

    cout<<endl;
    string domainName = helper::promptString("Input existing domain: ");

    carte.setTitle(helper::promptString("Input book title: "));
    carte.setAuthor(helper::promptString("Input book author: "));
    carte.setId(helper::promptString("Input book id: "));

    if (!libraryBooksManager.addBook(carte)) {
        cout << "A book with same id already exists" << endl;
        return;
    }

    if (libraryDomainsManager.addToDomain(carte, domainName)) {
        cout << "Book has been added to domain" << endl;
    } else {
        libraryBooksManager.deleteBook(carte.getId());
        cout << "Domain does not exist" << endl;
    }
}
