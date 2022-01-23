#ifndef POO_CARTE_H
#define POO_CARTE_H

#include <string>
#include <vector>
#include <ctime>



using namespace std;

class Carte {
private:
    string cota;
    string titlu;
    string autor;
    string domeniu;
    bool imprumutat;
    long int lendTime;
    bool strToBool(string input);
    string boolToStr(bool input);
public:
    Carte();
    Carte(string cota, string titlu, string autor, string domeniu, bool imprumutat, long int lendTime);
    Carte(vector<string> input);

    void setCota(string input);
    string getCota();

    void setTitlu(string input);
    string getTitlu();

    void setAutor(string input);
    string getAutor();

    void setDomeniu(string input);
    string getDomeniu();

    void setImprumutat(bool input);
    bool getImprumutat();

    void setLendTime(long int input);
    long int getLendTime();

    vector<string> toVector();

    void printDetails();

    ~Carte();
};


#endif //POO_CARTE_H
