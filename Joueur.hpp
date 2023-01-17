#ifndef _joueur
#define _joueur

#include <iostream>
#include <string>

class Joueur{

    int soleil;
    std::string objet;

    public:
    Joueur(void);
    void setSoleil(int numOfSoleil);
    int getSoleil(void);
    void setObjet(std::string objet);
    std::string getObjet(void);

};

#endif