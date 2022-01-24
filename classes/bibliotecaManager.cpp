#include "bibliotecaManager.h"
#include "csvFile.h"
#include <string>
#include "helper.h"

using namespace std;

bibliotecaManager::bibliotecaManager() = default;

bibliotecaManager::bibliotecaManager(string fileName, char fieldDelimiter) {
    this->fileName = fileName;
    this->fieldDelimiter = fieldDelimiter;
}

void bibliotecaManager::loadBooks() {
    this->carti.clear();
    csvFile input(fileName, fieldDelimiter);
    vector<vector<string>> temp;

    try {
        temp = input.getFileContent();

        for (int i = 0; i < temp.size(); ++i) {
            carti.push_back((Carte(temp[i])));
        }
    }
    catch (exception ex) {
        throw ex;
    }
}

void bibliotecaManager::saveCarti() {
    csvFile output(fileName, fieldDelimiter);
    vector<vector<string>> temp;

    for (int i = 0; i < carti.size(); ++i) {
        temp.push_back(carti[i].toVector());
    }

    output.setFileContent(temp);
}

vector<Carte> bibliotecaManager::findCarte(string pattern) {
    vector<Carte> foundCarti;

    for (int i = 0; i < carti.size(); ++i) {

        if (helper::stringContains(carti[i].getAutor(), pattern) ||
            helper::stringContains(carti[i].getTitlu(), pattern)) {
            foundCarti.push_back(carti[i]);
        }
    }

    return foundCarti;
}

int bibliotecaManager::getIndexCarte(string cota) {
    for (int i = 0; i < carti.size(); ++i) {
        if (helper::stringsEqual(carti[i].getCota(), cota)) {
            return i;
        }
    }

    return -1;
}

bool bibliotecaManager::deleteCarte(string cotaCarte) {
    int index = getIndexCarte(cotaCarte);

    if (index == -1) {
        return false;
    }
    carti.erase(carti.begin() + index);
    return true;
}

bool bibliotecaManager::isPastReturnDate(Carte carte) {
    time_t now = time(nullptr);
    long int lendPeriod = now - carte.getLendTime();

    return lendPeriod > this->returnPeriod && carte.getImprumutat();
}

vector<Carte> bibliotecaManager::getAllBooksPastReturnDate() {
    vector<Carte> booksPastReturnDate;
    for (int i = 0; i < carti.size(); ++i) {
        if (isPastReturnDate(carti[i])) {
            booksPastReturnDate.push_back(carti[i]);
        }
    }

    return booksPastReturnDate;
}

bool bibliotecaManager::lendCarte(string cotaCarte) {
    int index = getIndexCarte(cotaCarte);

    if (index < 0 || carti[index].getImprumutat()) {
        return false;
    }

    carti[index].setImprumutat(true);
    carti[index].setLendTime(time(nullptr));

    return true;
}

bool bibliotecaManager::returnCarte(string cotaCarte) {
    int index = getIndexCarte(cotaCarte);

    if (index < 0 || !carti[index].getImprumutat()) {
        return false;
    }

    carti[index].setImprumutat(false);
    carti[index].setLendTime(0);

    return true;
}

bool bibliotecaManager::addBook(Carte carte) {
    if (getIndexCarte(carte.getCota()) >= 0) {
        return false;
    }

    this->carti.push_back(carte);
    return true;
}