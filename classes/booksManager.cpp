#include <string>
#include "helper.h"
#include "booksManager.h"
#include "csvFile.h"

using namespace std;

booksManager::booksManager() = default;

booksManager::booksManager(string fileName, char fieldDelimiter) {
    this->fileName = fileName;
    this->fieldDelimiter = fieldDelimiter;
}

void booksManager::load() {
    this->books.clear();
    csvFile input(fileName, fieldDelimiter);
    vector<vector<string>> temp;

    try {
        temp = input.getFileContent();

        for (int i = 0; i < temp.size(); ++i) {
            books.push_back((book(temp[i])));
        }
    }
    catch (exception &ex) {
        throw ex;
    }
}

void booksManager::save() {
    csvFile output(fileName, fieldDelimiter);
    vector<vector<string>> temp;

    for (int i = 0; i < books.size(); ++i) {
        temp.push_back(books[i].toVector());
    }

    output.setFileContent(temp);
}

vector<book> booksManager::findBook(string pattern) {
    vector<book> foundBooks;

    for (int i = 0; i < books.size(); ++i) {

        if (helper::stringContains(books[i].getAuthor(), pattern) ||
            helper::stringContains(books[i].getTitle(), pattern)) {
            foundBooks.push_back(books[i]);
        }
    }

    return foundBooks;
}

int booksManager::getIndexCarte(string id) {
    for (int i = 0; i < books.size(); ++i) {
        if (helper::stringsEqual(books[i].getId(), id)) {
            return i;
        }
    }

    return -1;
}

bool booksManager::deleteBook(string id) {
    int index = getIndexCarte(id);

    if (index == -1) {
        return false;
    }
    books.erase(books.begin() + index);

    this->save();
    return true;
}

bool booksManager::isPastReturnDate(book book) {
    time_t now = time(nullptr);
    long int lendPeriod = now - book.getLendTime();

    return lendPeriod > this->returnPeriod && book.getBorrowed();
}

vector<book> booksManager::getAllBooksPastReturnDate() {
    vector<book> booksPastReturnDate;
    for (int i = 0; i < books.size(); ++i) {
        if (isPastReturnDate(books[i])) {
            booksPastReturnDate.push_back(books[i]);
        }
    }

    return booksPastReturnDate;
}

bool booksManager::lendBook(string id) {
    int index = getIndexCarte(id);

    if (index < 0 || books[index].getBorrowed()) {
        return false;
    }

    books[index].setBorrowed(true);
    books[index].setBorrowedTime(time(nullptr));

    this->save();
    return true;
}

bool booksManager::returnBook(string id) {
    int index = getIndexCarte(id);

    if (index < 0 || !books[index].getBorrowed()) {
        return false;
    }

    books[index].setBorrowed(false);
    books[index].setBorrowedTime(0);

    this->save();
    return true;
}

bool booksManager::addBook(book book) {
    if (getIndexCarte(book.getId()) >= 0) {
        return false;
    }

    this->books.push_back(book);
    this->save();
    return true;
}

int booksManager::countBooks() {
    return books.size();
}