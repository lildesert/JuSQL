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

void Schema::addRelationTMP(Relation r)
{
	(this->listRelationTMP).push_back(r);
}

Relation Schema::GetRelationById(string id)
{
	Relation r;
	int convertId = bin8ToInt(id);
	for (auto &rel : this->listRelation)
	{
		if(rel.GetId() == convertId)
		{
			r = rel;
		}
	}
	return r;
}

void Schema::DeleteAllRelations()
{
	this->listRelation.clear();
}

vector<Relation> Schema::GetRelations()
{
	return this->listRelation;
}

vector<Relation> Schema::GetRelationsTMP()
{
	return this->listRelationTMP;
}

Relation Schema::GetRelationByNom(string nom)
{
	Relation r;
	for (auto &rel : this->listRelation)
	{
		if(rel.GetNom() == nom)
		{
			r = rel;
		}
	}
	return r;
}