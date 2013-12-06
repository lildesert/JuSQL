#include "Relation.h"

using namespace std;

int Relation::idIncrementRelation = 0;

Relation::Relation(string nomR)
{
	nomRelation = nomR;
	idRelation = idIncrementRelation++;
}

Relation::Relation()
{
}

Relation::~Relation(void)
{
}

void Relation::addAttribut(Attribut a)
{
	(this->listAttribut).push_back(a);
}

string Relation::getNom()
{
	return this->nomRelation;
}