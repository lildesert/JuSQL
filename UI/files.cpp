#include "files.h"
#include <time.h>

using namespace std;

/* Charge les pages d'un relation de la mémoire persistante vers
 * la mémoire vive.
 * Interval :
 * --> 64 si ASCII
 * --> 64*8= 512 si bit
 * Prend en référence le tableau des pages de la relation.
 */
void chargerPages(vector<string> & tabBlocs) {
    cout << "Chargement des pages ... ";
    string nomFichier("bdd.txt");
    
    int interval(512), i(0);
    ifstream fichier(nomFichier.c_str());
    int tailleF = tailleFichier(nomFichier);
    string ligne;
    if(fichier) {
        if(fichierPagesValide(nomFichier)){
            //Récupère la seule ligne du fichier
            getline(fichier, ligne);
            //Extraction de 8 caractères pas 8 caractères
            while(i < (tailleF / interval)) {
                tabBlocs.push_back(ligne.substr(0, interval).c_str());
                ligne = ligne.substr(interval);
                i++;
            }
            cout << "ok." << endl;
        } else {
            cout << endl << "ERREUR: Fichier Invalide : " << endl;
            cout << "- " << nomFichier << endl;
        }
    } else {
        cout << endl << "ERREUR: Impossible d'ouvrir le fichier :" << endl;
        cout << "- " << nomFichier << endl;
    }
}

/* Sauvegarde les pages d'un relation de la mémoire vive vers
 * la mémoire persistance.
 */
void sauvegarderPages(vector<string> & tabBlocs) {
    cout << "Enregistrement des pages dans le fichier ... ";
    string nomFichier("bdd.txt");
    ofstream fichier(nomFichier.c_str());
    if(fichier) {
        int i;
        for(i= 0; i< tabBlocs.size(); ++i) {
            if(tabBlocs[i].size() == 64) {
                fichier << tabBlocs[i] << endl;
            } else {
                cout << "Bloc " << i << "--> taille incorrecte." << endl;
            }
        }
        cout << "ok : " << i << " bloc(s) enregistré(s). " << endl;
    } else {
        cout << endl << "ERREUR: Impossible d'ouvrir le fichier :" << endl;
        cout << "- " << nomFichier << endl;
    }
}

/* Chargement du schéma de la bdd en mémoire vive.
 * Une relation :
 * - 1er cara : IDRelation
 * - 2/6 : nom du champ
 * - 7 : type de champ 
 */
void chargerSchema(vector<string> &tabSchema) {
    cout << "Chargement du schéma ... ";
    string nomFichier("schema.txt");
    ifstream fichier(nomFichier.c_str());
    
    int i(0);
    int tailleF = tailleFichier(nomFichier);
    string ligne;
    string table;

    string IDRelation, nomChamp, typeChamp;
    
    if(fichier) {
        getline(fichier, ligne); //Récupère la seule ligne du fichier
        while(fichier.tellg() <= tailleF) {
            
            //Extraction d'une table
            IDRelation = ligne.substr(0, 1).c_str();
            ligne = ligne.substr(1);
            nomChamp = ligne.substr(0, 5).c_str();
            ligne = ligne.substr(5);
            typeChamp = ligne.substr(0, 1).c_str();
            ligne = ligne.substr(1);
            
            //Reconstruction de la table
            table = IDRelation + nomChamp + typeChamp;
            tabSchema.push_back(table);
        }
        cout << "ok." << endl;
    } else {
        cout << endl << "ERREUR: Impossible d'ouvrir le fichier :" << endl;
        cout << "- " << nomFichier << endl;
    }
}

//Retourne le nombre de caractères d'un fichier
int tailleFichier(string nomFichier) {
    int taille(0);
    ifstream fichier(nomFichier.c_str());
    fichier.seekg(0, ios::end);
    taille = fichier.tellg();
    taille -= 1;
    return taille; 
}

/*Vérifie que le fichier de pages est composé de blocs de 512bits
 * Donc un multiple de 512 
 */
bool fichierPagesValide(string nomFichier){
    return (tailleFichier(nomFichier) % 512 == 0);
}

void enregistrerSchema() {
    ofstream fichier("schema.txt");
    if(fichier) {
        
    } else {
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }
}