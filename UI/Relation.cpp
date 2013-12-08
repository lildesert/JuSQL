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
	a.SetPosition(this->listAttribut.size() + 1);
	(this->listAttribut).push_back(a);
}

string Relation::GetNom()
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

vector<Attribut> Relation::GetAttributs()
{
	return this->listAttribut;
}

Attribut Relation::GetAttributByNom(string nom)
{
	Attribut a;
	for (auto &att : this->listAttribut)
	{
		if(att.GetNom() == nom)
		{
			a = att;
		}
	}
	return a;
}

void Relation::SetNom(string nom)
{
	this->nomRelation = nom;
}