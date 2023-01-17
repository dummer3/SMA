#include "Joueur.hpp"

Joueur::Joueur(void)
{
    soleil = 0;
    objet = "None";
}

void Joueur::setSoleil(int numOfSoleil)
{
    this->soleil = numOfSoleil;
}

int Joueur::getSoleil(void)
{
    return soleil;
}

void Joueur::setObjet(std::string objet)
{
    this->objet += objet;
}

std::string Joueur::getObjet(void)
{
    return objet;
}