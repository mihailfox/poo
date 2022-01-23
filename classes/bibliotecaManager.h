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
    const long int returnPeriod = 86400 * 14;
public:
    bibliotecaManager();
    bibliotecaManager(string fileName, char fieldDelimiter);
    void loadCarti();
    void saveCarti();
    void deleteCarte(string cotaCarte);
    vector<Carte> findCarte(string pattern);
    vector<Carte> getAllBooksPastReturnDate();
    void lendCarte(string cotaCarte);
    void returnCarte(string cotaCarte);
};


#endif //POO_BIBLIOTECAMANAGER_H
