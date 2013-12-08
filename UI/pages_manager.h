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

bool creerEnregistrement(string IDRelation, int nbMaxNUplets, string nUplet);

void supprimerAdressage(int position);

void allouerPages(string IDRelation, int nbMaxNuplets, string nUplet);

void desallouerPage(string IDPage);

void afficherPage(string IDPage);

void AfficherPages(string IDRelation);

int selectByChamp(string IDRelation, int numChamp, string ref);

#endif	/* PAGES_MANAGER_H */

