#ifndef FILES_H
#define	FILES_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>

#include "page.h"

using namespace std;

int modeF();

string fichierBDD();

string fichierRPages();

int getPositionPage();

void afficherPbmOuverture(string nomFichier);

void viderFichier(string nomFichier);

vector<Page> chargerPages();

void chargerSchema(vector<string> &tabSchema);

void enregistrerSchema();

void sauvegarderPages(vector<Page> pages, bool aLaFin);

bool fichierPagesValide(string nomFichier);

void enregistrerSchema();

int tailleFichier(string nomFichier);

#endif	/* FILES_H */

