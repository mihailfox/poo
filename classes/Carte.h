#ifndef POO_CARTE_H
#define POO_CARTE_H

#include <string>
#include <vector>

using namespace std;

class Carte {
private:
    string cota;
    string titlu;
    string autor;
    string domeniu;

public:
    Carte();
    Carte(string cota, string titlu,string autor,string domeniu);
    Carte(vector<string> input);

    void setCota(string input);
    string getCota();

    void setTitlu(string input);
    string getTitlu();

    void setAutor(string input);
    string getAutor();

    void setDomeniu(string input);
    string getDomeniu();

    vector<string> toVector();

    void printDetails();

    ~Carte();
};


#endif //POO_CARTE_H
