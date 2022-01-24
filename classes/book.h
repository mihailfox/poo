#ifndef POO_BOOK_H
#define POO_BOOK_H

#include <string>
#include <vector>
#include <ctime>

using namespace std;

class book {
private:
    string id;
    string title;
    string author;
    bool borrowed = false;
    long int borrowedTime = 0;
public:
    book();
    book(string id, string title, string author, bool borrowed, long int borrowedTime);
    explicit book(vector<string> input);

    void setId(string input);
    string getId();

    void setTitle(string input);
    string getTitle();

    void setAuthor(string input);
    string getAuthor();

    void setBorrowed(bool input);
    bool getBorrowed();

    void setBorrowedTime(long int input);
    long int getLendTime();

    vector<string> toVector();

    void printDetails();

    ~book();
};


#endif //POO_BOOK_H
