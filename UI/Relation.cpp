#include "Relation.h"

using namespace std;

int Relation::idIncrementRelation = 1;

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

int Relation::GetTailleNuplet()
{
	int taille = 0;
	for (auto &a : this->listAttribut)
	{
		taille += a.GetTaille();
	}
	return taille;
}

int Relation::GetId()
{
	return this->idRelation;
}

vector<int> Relation::GetTaillesAttributs()
{
	vector<int> listTaille;
	for (auto &a : this->listAttribut)
	{
		listTaille.push_back(a.GetTaille());
	}
	return listTaille;
}

vector<string> Relation::GetTypesAttributs()
{
	vector<string> listTypes;
	for (auto &a : this->listAttribut)
	{
		listTypes.push_back(a.GetType());
	}
	return listTypes;
}

int Relation::NbMaxNuplets()
{
	int tailleNuplet = this->GetTailleNuplet();
	int nbEnregistrement = 62 / tailleNuplet;
	int reste = 62 % tailleNuplet;
	while(nbEnregistrement > (reste * 8))
	{
		nbEnregistrement--;
		reste++;
	}
	return nbEnregistrement;
}