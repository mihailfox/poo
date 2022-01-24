#ifndef POO_DOMAINMANAGER_H
#define POO_DOMAINMANAGER_H
#include "string"
#include "vector"
#include "Domain.h"
#include "csvFile.h"
#include "Carte.h"

using namespace std;

class domainManager {
private:
    string fileName;
    char fieldDelimiter;
    vector<Domain> domains;
    int getDomainIndex(string domainName);
public:
    domainManager();
    domainManager(string fileName, char fieldDelimiter);
    void loadDomains();
    void saveDomains();
    bool addDomain(string domainName);
    bool addCotaToDomain(Carte carte, string domainName);
    void deleteCotaFromDomain(string cota);
};


#endif //POO_DOMAINMANAGER_H
