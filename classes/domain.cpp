#include "domain.h"

domain::domain() = default;
domain::domain(string name) {
    this->name = name;
}
domain::domain(vector<string> input) {
    this->name = input[0];
    for (int i = 1; i < input.size() ; ++i) {
        addBookId(input[i]);
    }
}

void domain::setName(string name) {
    this->name = name;
}

string domain::getName() {
    return this->name;
}

void domain::setIds(vector<string> ids) {
    this->ids = ids;
}

vector<string> domain::getIds() {
    return this->ids;
}

bool domain::addBookId(string id) {
    if (searchById(id)) {
        return false;
    }

    this->ids.push_back(id);

    return true;
}

void domain::removeBookId(string id) {
    for (int i = 0; i < this->ids.size(); ++i) {
        if (ids[i] == id) {
            this->ids.erase(this->ids.begin() + i);
        }
    }
}

bool domain::searchById(string id) {
    for (int i = 0; i < this->ids.size(); ++i) {
        if (ids[i] == id) {
            return true;
        }
    }

    return false;
}

vector<string> domain::toVector() {
    vector<string> output;

    output.push_back(this->name);

    for (int i = 0; i < ids.size(); ++i) {
        output.push_back(ids[i]);
    }

    return output;
}
