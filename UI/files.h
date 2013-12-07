#ifndef FILES_H
#define	FILES_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>

#include "page.h"

using namespace std;

string intToBin(int entier);

int binToInt(string bin);

string intToBin8(int entier);

int bin8ToInt(string bin);

string asciiToBin(string ascii);

string binToAscii(string bin);

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

bool IsFileEmpty(std::ifstream& pFile);

#endif	/* FILES_H */

