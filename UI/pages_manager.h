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

int deleteNupletByChamp(string IDRelation, int numChamp, string ref);

vector<int> getAdressesPages(string IDRelation);

string getNextIDBloc();

void ajouterAdressage(string IDRelation, int position);

void afficherPagesBrut();

void afficherPage(string IDPage);

bool creerEnregistrement(string IDRelation, int nbMaxNUplets, string nUplet);

void supprimerAdressage(int position);

void allouerPages(string IDRelation, int nbMaxNuplets, string nUplet);

void AfficherPages();

string getBlocIDRelation(string Bloc);

string getBlocContent(string bloc);

void desallouerPage(string IDPage);

#endif	/* PAGES_MANAGER_H */

