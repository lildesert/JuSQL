#include "schema.h"

using namespace std;

int Schema::idIncrementSchema = 0;

void Schema::setNom(string nom)
{
	this->nomSchema = nom;
}

void Schema::addRelation(Relation r)
{
	(this->listRelation).push_back(r);
}