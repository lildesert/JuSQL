#include "files.h"
#include <time.h>

using namespace std;

// Pour changer de mode de sauvegarde facilement
// 1 ASCII
// 2 Binaire
int modeF() {
    return 2;
}

// Retourne le chemin du fichier de bdd
string fichierBDD() {
    string f("UI/bdd.txt");
    return f;
}

// Retourne le chemin du fichier Relation - Pages
string fichierRPages() {
    string f("UI/R_Pages.txt");
    return f;
}

void afficherPbmOuverture(string nomFichier){
    cout << endl << "ERREUR: Impossible d'ouvrir le fichier :" << nomFichier << endl;
}

void viderFichier(string nomFichier){
    //Cette ouverture supprime le contenu existant
    ofstream fichier(nomFichier.c_str()); 
    if(! fichier){
        afficherPbmOuverture(nomFichier);
    }
}

// Retourne la position d'une page dans le fichier Bdd
// en fonction du codage implémenté
int getPositionPage() {
    ifstream fPages(fichierBDD().c_str());
    int position(-1);
    if(fPages) {
        fPages.seekg(0, ios::end);
        if(fPages.tellg() > 0 && modeF() == 2) {
            position = fPages.tellg() / 512;
        } else if (fPages.tellg() > 0 && modeF() == 1) {
            position = fPages.tellg() / 64;
        } else {
            position = 0;
        }
    } else {
        afficherPbmOuverture(fichierBDD());
    }
    return position;
}

/* Charge les pages depuis la mémoire persistantes vers la mémoire vive
 */
vector<Page> chargerPages() {
    cout << "Chargement des pages ... ";
    const int taillePage(512);
    ifstream fBDD(fichierBDD().c_str());
    char cara;
    string chaine;
    int i(0), j(0), y;
    Page p;
    vector <Page> pages;
    
    if(fBDD){
        while(fBDD.get(cara)){
            if(j < taillePage) {
                //Si il est nécessaire de convertir de l'ASCII vers le binaire
                chaine = std::bitset< 8 >( cara ).to_string();
                //Si directement binaire
                p.e[j] = cara;
            }
            ++j;
            if(j == taillePage) {
                pages.push_back(p);
            }
            ++i;
        }
    } else {
        afficherPbmOuverture(fichierBDD());
    }
    return pages;
}

/* Sauvegarde les pages d'une relation de la mémoire vive vers
 * la mémoire persistance.
 */
void sauvegarderPages(vector<Page> pages, bool aLaFin) {
    const int taillePage(512);
    int i(0);
    string chaine("");
    ofstream fBDD;
    if(aLaFin){ // Insertion à la fin du fichier
        fBDD.open(fichierBDD().c_str(), ios::app);
    } else { // Ecrasement de l'existant
        fBDD.open(fichierBDD().c_str());
    }
    if(fBDD) {
        cout << "Enregistrement des pages dans le fichier ... ";
        for(i= 0; i< pages.size(); ++i)  {
            for(int j= 0; j< taillePage; ++j) {
                chaine += pages[i].e[j];
                if(chaine.size() == 8){
                    
                    //En caractères ASCII
                    //fBDD << char(bitset< 8 >(chaine).to_ulong());
                    
                    //En bits
                    fBDD << chaine;
 
                    chaine.clear();
                }
            }
        }
        cout << "ok : " << i << " bloc(s) enregistré(s). " << endl;
    } else {
        afficherPbmOuverture(fichierBDD());
    }
}

void chargerSchema(vector<string> &tabSchema) {
    cout << "Chargement du sch�ma ... ";
    string nomFichier("schema.txt");
    ifstream fichier(nomFichier.c_str());
    
    int i(0);
    int tailleF = tailleFichier(nomFichier);
    string ligne;
    string table;

    string IDRelation, nomChamp, typeChamp;
    
    if(fichier) {
        getline(fichier, ligne); //R�cup�re la seule ligne du fichier
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

//Retourne le nombre de caract�res d'un fichier
int tailleFichier(string nomFichier) {
    int taille(0);
    ifstream fichier(nomFichier.c_str());
    fichier.seekg(0, ios::end);
    taille = fichier.tellg();
    taille -= 1;
    return taille; 
}

/*Vérifie que le fichier de pages est composé de blocs de 512bits
 * Donc un multiple de 512 en bits et 64 en ASCII
 */
bool fichierPagesValide(string nomFichier, bool modeASCII){
    if(modeASCII){
        return (tailleFichier(nomFichier) % 64 == 0);
    } else {
        return (tailleFichier(nomFichier) % 512 == 0);
    }
}