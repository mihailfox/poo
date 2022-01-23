#include "Carte.h"

#include <stdexcept>
#include <iostream>

using namespace std;

Carte::Carte() = default;

Carte::Carte(string cota, string titlu, string autor, string domeniu, bool imprumutat, long int lendTime) {
    if (cota.empty() || titlu.empty() || autor.empty() || domeniu.empty())
    {
        throw invalid_argument("Received an empty argument!");
    }

    this->cota = cota;
    this->titlu = titlu;
    this->autor = autor;
    this->domeniu = domeniu;
    this->imprumutat = imprumutat;
    this->lendTime = lendTime;
}

Carte::Carte(vector<string> input) {

    if (input.size() != 6 ) {
        throw invalid_argument("Input has different size than expected!");
    }

    for (int i = 0; i < input.size(); ++i) {
        if(input[i].empty())
        {
            throw invalid_argument("Received an empty argument!");
        }
    }

    this->cota = input[0];
    this->titlu = input[1];
    this->autor = input[2];
    this->domeniu = input[3];
    this->imprumutat = strToBool(input[4]);
    this->lendTime = stol(input[5]);
}


void Carte::setCota(string input) {
    if(input.empty())
    {
        throw invalid_argument("Received an empty argument!");
    }

    this->cota = input;
}

string Carte::getCota() {
    return this->cota;
}

void Carte::setTitlu(string input) {
    if(input.empty())
    {
        throw invalid_argument("Received an empty argument!");
    }

    this->titlu = input;
}

string Carte::getTitlu() {
    return this->titlu;
}

void Carte::setAutor(string input) {
    if(input.empty())
    {
        throw invalid_argument("Received an empty argument!");
    }

    this->autor = input;
}

string Carte::getAutor() {
    return this->autor;
}

void Carte::setDomeniu(string input) {
    if(input.empty())
    {
        throw invalid_argument("Received an empty argument!");
    }

    this->domeniu = input;
}

string Carte::getDomeniu() {
    return this->domeniu;
}

void Carte::setImprumutat(bool input) {
    this->imprumutat = input;
}

bool Carte::getImprumutat() {
    return this->imprumutat;
}

void Carte::setLendTime(long input) {
    this->lendTime = input;
}

long int Carte::getLendTime() {
    return this->lendTime;
}

vector<string> Carte::toVector() {
    vector<string> output;

    output.push_back(this->cota);
    output.push_back(this->titlu);
    output.push_back(this->autor);
    output.push_back(this->domeniu);
    output.push_back(boolToStr(this->imprumutat));
    output.push_back(to_string(this->lendTime));

    return output;
}

void Carte::printDetails() {
    cout << "Cota: " << this->cota << endl;
    cout << "Titlu: " << this->titlu << endl;
    cout << "Autor: " << this->autor << endl;
    cout << "Domeniu: " << this->domeniu << endl;
}

Carte::~Carte() {
    this->cota.clear();
    this->titlu.clear();
    this->autor.clear();
    this->domeniu.clear();
    this->imprumutat = false;
    this->lendTime = 0;
}

bool Carte::strToBool(string input) {
    if (input == "false") {
        return false;
    }
    return true;
}

string Carte::boolToStr(bool input) {
    if (input == false)
    {
        return "false";
    }
    return "true";
}
