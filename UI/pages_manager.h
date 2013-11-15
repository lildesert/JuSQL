#ifndef PAGES_MANAGER_H
#define	PAGES_MANAGER_H

using namespace std;

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <bitset>
#include "files.h"

void creerEnregistrement(string IDRelation, int nbMaxNUplets);

void allouerPages(string IDRelation, int nbMaxNuplets);

void AfficherPages(vector<string> &tabBlocs);

void AfficherPagesLisiblement(vector<string> &tabBlocs);

void AfficherSchema(vector<string> &tabSchema);

string getBlocIDRelation(string Bloc);

string getBlocContent(string bloc);

string getTableIDRelation(string table);

vector<string> getTableChamps(string table);

#endif	/* PAGES_MANAGER_H */

