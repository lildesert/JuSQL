#ifndef PAGES_MANAGER_H
#define	PAGES_MANAGER_H

using namespace std;

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <bitset>
#include <list>
#include "files.h"

void creerEnregistrement(string IDRelation, int nbMaxNUplets, list<string> Nuplet);

void allouerPages(string IDRelation, int nbMaxNuplets, list<string> nUplet);

void AfficherPages();

void AfficherPagesLisiblement();

void AfficherSchema(vector<string> &tabSchema);

string getBlocIDRelation(string Bloc);

string getBlocContent(string bloc);

string getTableIDRelation(string table);

vector<string> getTableChamps(string table);

#endif	/* PAGES_MANAGER_H */

