#ifndef FILES_H
#define	FILES_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void afficherPbmOuverture(string nomFichier);

void viderFichier(string nomFichier);

void chargerPages(vector<string> & tabBlocs);

void chargerSchema(vector<string> &tabSchema);

void enregistrerSchema();

void sauvegarderPages(vector<string> & tabBlocs);

bool fichierPagesValide(string nomFichier);

void enregistrerSchema();

int tailleFichier(string nomFichier);

#endif	/* FILES_H */

