#ifndef POO_DOMAINSMANAGER_H
#define POO_DOMAINSMANAGER_H
#include "string"
#include "vector"
#include "domain.h"
#include "csvFile.h"
#include "book.h"
#include "helper.h"


using namespace std;

class domainsManager {
private:
    string fileName;
    char fieldDelimiter;
    vector<domain> domains;
    int getDomainIndex(string domainName);
public:
    domainsManager();
    domainsManager(string fileName, char fieldDelimiter);
    void load();
    void saveDomains();
    bool addDomain(string domainName);
    bool addToDomain(book book, string domainName);
    void removeFromDomain(string bookId);
    int countDomains();
};


#endif //POO_DOMAINSMANAGER_H
