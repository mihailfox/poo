#ifndef POO_DOMAIN_H
#define POO_DOMAIN_H

#include "string"
#include <vector>

using namespace std;

class domain {
private:
    string name;
    vector<string> ids;
    bool searchById(string id);
public:
    domain();
    explicit domain(string name);
    explicit domain(vector<string> input);

    void setName(string name);
    string getName();
    void setIds(vector<string> ids);

    vector<string> getIds();
    bool addBookId(string id);
    void removeBookId(string id);

    vector<string> toVector();
};


#endif //POO_DOMAIN_H
