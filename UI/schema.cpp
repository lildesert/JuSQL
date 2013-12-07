#include "schema.h"

using namespace std;

int Schema::idIncrementSchema = 0;

void Schema::setNom(string nom)
{
	this->nomSchema = nom;
}

int Schema::getId()
{
	return this->idSchema;
}

string Schema::getNom()
{
	return this->nomSchema;
}

void Schema::addRelation(Relation r)
{
	(this->listRelation).push_back(r);
}