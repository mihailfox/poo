#include "Domain.h"

Domain::Domain() = default;
Domain::Domain(string name) {
    this->name = name;
}
Domain::Domain(vector<string> input) {
    this->name = input[0];
    for (int i = 1; i < input.size() ; ++i) {
        addCota(input[i]);
    }
}

void Domain::setName(string name) {
    this->name = name;
}

string Domain::getName() {
    return this->name;
}

void Domain::setCote(vector<string> cote) {
    this->cote = cote;
}

vector<string> Domain::getCote() {
    return this->cote;
}

bool Domain::addCota(string cota) {
    if (searchCota(cota)) {
        return false;
    }

    this->cote.push_back(cota);

    return true;
}

void Domain::deleteCota(string cota) {
    for (int i = 0; i < this->cote.size(); ++i) {
        if (cote[i] == cota) {
            this->cote.erase(this->cote.begin() + i);
        }
    }
}

bool Domain::searchCota(string cota) {
    for (int i = 0; i < this->cote.size(); ++i) {
        if (cote[i] == cota) {
            return true;
        }
    }

    return false;
}

vector<string> Domain::toVector() {
    vector<string> output;

    output.push_back(this->name);

    for (int i = 0; i < cote.size(); ++i) {
        output.push_back(cote[i]);
    }

    return output;
}
