#include "Attribut.h"

using namespace std;

int Attribut::idIncrementAttribut = 1;

Attribut::Attribut(string nomA, string typeA, int tailleA)
{
	nomAttribut = nomA;
	typeAttribut = typeA;
	tailleAttribut = tailleA;
	idAttribut = idIncrementAttribut++;
}


Attribut::~Attribut(void)
{
}

Attribut::Attribut()
{
}

int Attribut::GetTaille()
{
	return this->tailleAttribut;
}

string Attribut::GetType()
{
	return this->typeAttribut;
}

string Attribut::GetNom()
{
	return this->nomAttribut;
}