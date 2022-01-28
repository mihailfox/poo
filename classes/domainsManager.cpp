#include "domainsManager.h"

domainsManager::domainsManager() = default;

domainsManager::domainsManager(string fileName, char fieldDelimiter) {
    this->fileName = fileName;
    this->fieldDelimiter = fieldDelimiter;
}

void domainsManager::load() {
    this->domains.clear();
    csvFile input(fileName, fieldDelimiter);
    vector<vector<string>> temp;

    temp = input.getFileContent();
    for (int i = 0; i < temp.size(); ++i) {
        domains.push_back(domain(temp[i]));
    }
}
void domainsManager::save() {
    csvFile output(fileName, fieldDelimiter);
    vector<vector<string>> temp;

    for (int i = 0; i < domains.size(); ++i) {
        temp.push_back(domains[i].toVector());
    }

    output.setFileContent(temp);
}

int domainsManager::getDomainIndex(string domainName) {
    for (int i = 0; i < this->domains.size(); ++i) {
        if (helper::stringsEqual(this->domains[i].getName(),domainName)) {
            return i;
        }
    }

    return -1;
}

bool domainsManager::addDomain(string domainName) {
    if(getDomainIndex(domainName) >= 0) {
        return false;
    }

    this->domains.push_back(domain(domainName));

    this->save();
    return true;
}

bool domainsManager::addToDomain(book book, string domainName) {
    int index = getDomainIndex(domainName);

    if (index < 0) {
        return false;
    }

    if(this->domains[index].addBookId(book.getId()))
    {
        this->save();
        return true;
    }

    return false;
}

void domainsManager::removeFromDomain(string bookId) {
    for (int i = 0; i < domains.size(); ++i) {
        domains[i].removeBookId(bookId);
    }
    this->save();
}

int domainsManager::countDomains() {
    return domains.size();
}