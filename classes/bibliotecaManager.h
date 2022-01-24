#ifndef POO_BIBLIOTECAMANAGER_H
#define POO_BIBLIOTECAMANAGER_H

#include <string>
#include <vector>
#include "Carte.h"

using namespace std;

class bibliotecaManager {
private:
    string fileName;
    char fieldDelimiter;
    vector<Carte> carti;
    int getIndexCarte(string cota);
    bool isPastReturnDate(Carte carte);
    long int returnPeriod = 86400 * 14; //1209600
public:
    bibliotecaManager();
    bibliotecaManager(string fileName, char fieldDelimiter);
    void loadBooks();
    void saveCarti();
    bool deleteCarte(string cotaCarte);
    vector<Carte> findCarte(string pattern);
    vector<Carte> getAllBooksPastReturnDate();
    bool lendCarte(string cotaCarte);
    bool returnCarte(string cotaCarte);
    bool addBook(Carte carte);
};


#endif //POO_BIBLIOTECAMANAGER_H
