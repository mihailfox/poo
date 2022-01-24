#include "book.h"

#include <stdexcept>
#include <iostream>

using namespace std;

book::book() = default;

book::book(string id, string title, string author, bool borrowed, long int borrowedTime) {
    if (id.empty() || title.empty() || author.empty())
    {
        throw invalid_argument("Received an empty argument!");
    }

    this->id = id;
    this->title = title;
    this->author = author;
    this->borrowed = borrowed;
    this->borrowedTime = borrowedTime;
}

book::book(vector<string> input) {

    if (input.size() != 5 ) {
        throw invalid_argument("Input has different size than expected!");
    }

    for (int i = 0; i < input.size(); ++i) {
        if(input[i].empty())
        {
            throw invalid_argument("Received an empty argument!");
        }
    }

    this->id = input[0];
    this->title = input[1];
    this->author = input[2];
    this->borrowed = strToBool(input[3]);
    this->borrowedTime = stol(input[4]);
}


void book::setId(string input) {
    if(input.empty())
    {
        throw invalid_argument("Received an empty argument!");
    }

    this->id = input;
}

string book::getId() {
    return this->id;
}

void book::setTitle(string input) {
    if(input.empty())
    {
        throw invalid_argument("Received an empty argument!");
    }

    this->title = input;
}

string book::getTitle() {
    return this->title;
}

void book::setAuthor(string input) {
    if(input.empty())
    {
        throw invalid_argument("Received an empty argument!");
    }

    this->author = input;
}

string book::getAuthor() {
    return this->author;
}

void book::setBorrowed(bool input) {
    this->borrowed = input;
}

bool book::getBorrowed() {
    return this->borrowed;
}

void book::setBorrowedTime(long input) {
    this->borrowedTime = input;
}

long int book::getLendTime() {
    return this->borrowedTime;
}

vector<string> book::toVector() {
    vector<string> output;

    output.push_back(this->id);
    output.push_back(this->title);
    output.push_back(this->author);
    output.push_back(boolToStr(this->borrowed));
    output.push_back(to_string(this->borrowedTime));

    return output;
}

void book::printDetails() {
    cout << "Cota: " << this->id << endl;
    cout << "Titlu: " << this->title << endl;
    cout << "Autor: " << this->author << endl;
}

book::~book() {
    this->id.clear();
    this->title.clear();
    this->author.clear();
    this->borrowed = false;
    this->borrowedTime = 0;
}

bool book::strToBool(string input) {
    if (input == "false") {
        return false;
    }
    return true;
}

string book::boolToStr(bool input) {
    if (input == false)
    {
        return "false";
    }
    return "true";
}
