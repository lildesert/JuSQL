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

bool creerEnregistrement(string IDRelation, int nbMaxNUplets, string nUplet);

void allouerPages(string IDRelation, int nbMaxNuplets, string nUplet);

void AfficherPages();

void AfficherPagesLisiblement();

void AfficherSchema(vector<string> &tabSchema);

string getBlocIDRelation(string Bloc);

string getBlocContent(string bloc);

string getTableIDRelation(string table);

vector<string> getTableChamps(string table);

#endif	/* PAGES_MANAGER_H */

