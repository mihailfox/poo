#ifndef POO_BOOKSMANAGER_H
#define POO_BOOKSMANAGER_H

#include <string>
#include <vector>
#include "book.h"

using namespace std;

class booksManager {
private:
    string fileName;
    char fieldDelimiter;
    vector<book> books;
    int getIndexCarte(string id);
    bool isPastReturnDate(book book);
    static const long int returnPeriod = 86400 * 14; //1209600
public:
    booksManager();
    booksManager(string fileName, char fieldDelimiter);
    void load();
    void save();
    bool deleteBook(string id);
    vector<book> findBook(string pattern);
    bool findBookId(string bookId);
    vector<book> getAllBooksPastReturnDate();
    bool lendBook(string id);
    bool returnBook(string id);
    bool addBook(book book);
    int countBooks();
};


#endif //POO_BOOKSMANAGER_H
