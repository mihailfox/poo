#include "bibliotecaManager.h"
#include "csvFile.h"
#include <string>

using namespace std;

bibliotecaManager::bibliotecaManager() = default;

bibliotecaManager::bibliotecaManager(string fileName, char fieldDelimiter) {
    this->fileName = fileName;
    this->fieldDelimiter = fieldDelimiter;
}

void bibliotecaManager::loadCarti() {
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
        if ((carti[i].getAutor()).find(pattern) != string::npos ||
            (carti[i].getTitlu()).find(pattern) != string::npos) {
            foundCarti.push_back(carti[i]);
        }
    }

    return foundCarti;
}

int bibliotecaManager::getIndexCarte(string cota) {
    for (int i = 0; i < carti.size(); ++i) {
        if (carti[i].getCota() == cota)
        {
            return i;
        }
    }
    return -1;
}

void bibliotecaManager::deleteCarte(string cotaCarte) {
    int index = getIndexCarte(cotaCarte);

    if (index == -1) {
        return;
    }
    carti.erase(carti.begin() + index);
}

bool bibliotecaManager::isPastReturnDate(Carte carte) {
    time_t now = time(nullptr);

    return now - carte.getLendTime() > this->returnPeriod;
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

void bibliotecaManager::lendCarte(string cotaCarte) {
    int index = getIndexCarte(cotaCarte);

    carti[index].setImprumutat(true);
    carti[index].setLendTime(time(nullptr));
}

void bibliotecaManager::returnCarte(string cotaCarte) {
    int index = getIndexCarte(cotaCarte);

    carti[index].setImprumutat(false);
    carti[index].setLendTime(0);
}