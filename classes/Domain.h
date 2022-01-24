#ifndef POO_DOMAIN_H
#define POO_DOMAIN_H

#include "string"
#include <vector>

using namespace std;

class Domain {
private:
    string name;
    vector<string> cote;
    bool searchCota(string cota);
public:
    Domain();
    Domain(string name);
    Domain(vector<string> input);

    void setName(string name);
    string getName();
    void setCote(vector<string> cote);

    vector<string> getCote();
    bool addCota(string cota);
    void deleteCota(string cota);

    vector<string> toVector();
};


#endif //POO_DOMAIN_H
