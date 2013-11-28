#include "Attribut.h"

using namespace std;

int Attribut::idIncrementAttribut = 0;

Attribut::Attribut(string nomA, string typeA, string tailleA)
{
	nomAttribut = nomA;
	typeAttribut = typeA;
	tailleAttribut = tailleA;
	idAttribut = idIncrementAttribut++;
}


Attribut::~Attribut(void)
{
}
