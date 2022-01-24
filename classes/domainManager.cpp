#include "domainManager.h"
#include "helper.h"

domainManager::domainManager() = default;

domainManager::domainManager(string fileName, char fieldDelimiter) {
    this->fileName = fileName;
    this->fieldDelimiter = fieldDelimiter;
}

void domainManager::loadDomains() {
    this->domains.clear();
    csvFile input(fileName, fieldDelimiter);
    vector<vector<string>> temp;

        temp = input.getFileContent();
        for (int i = 0; i < temp.size(); ++i) {
            domains.push_back(Domain(temp[i]));
        }
}
void domainManager::saveDomains() {
    csvFile output(fileName, fieldDelimiter);
    vector<vector<string>> temp;

    for (int i = 0; i < domains.size(); ++i) {
        temp.push_back(domains[i].toVector());
    }

    output.setFileContent(temp);
}

int domainManager::getDomainIndex(string domainName) {
    for (int i = 0; i < this->domains.size(); ++i) {
        if (helper::stringsEqual(this->domains[i].getName(),domainName)) {
            return i;
        }
    }

    return -1;
}

bool domainManager::addDomain(string domainName) {
    if(getDomainIndex(domainName) >= 0) {
        return false;
    }

    this->domains.push_back(Domain(domainName));

    return true;
}

bool domainManager::addCotaToDomain(Carte carte, string domainName) {
    int index = getDomainIndex(domainName);

    if (index < 0) {
        return false;
    }

    return this->domains[index].addCota(carte.getCota());
}

void domainManager::deleteCotaFromDomain(string cota) {
    for (int i = 0; i < domains.size(); ++i) {
        domains[i].deleteCota(cota);
    }
}