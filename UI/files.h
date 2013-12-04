#ifndef FILES_H
#define	FILES_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>

#include "page.h"

using namespace std;

void afficherPbmOuverture(string nomFichier);

void viderFichier(string nomFichier);

vector<Page> chargerPages();

void chargerSchema(vector<string> &tabSchema);

void enregistrerSchema();

void sauvegarderPages(char tabBlocs[][512], int nbPages, bool aLaFin);

bool fichierPagesValide(string nomFichier);

void enregistrerSchema();

int tailleFichier(string nomFichier);

#endif	/* FILES_H */

