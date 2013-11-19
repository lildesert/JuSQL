#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "files.h"
#include "pages_manager.h"
#include "content_manager.h"
#include "interface.h"
#include "schema.h"
#include "common.h"

using namespace std; 

/*
 * 
 */
int main(int argc, char** argv) {
    //Chargement des pages en m�moire vive
    vector<string> tabSchema; // Tableau contenant le sch�ma de la base
    vector<string> tabBlocs; // Tableau des blocs
    
    //Réinitialisation == A enlever pour soutenance
    viderFichier("UI/bdd.txt");
    viderFichier("UI/R_pages.txt");
    
    //list<string> nUplet;
    //nUplet.push_back("00100101"); // ID
    //nUplet.push_back("000000010000000100000001"); // Trois caractères
    //allouerPages("00000001", 3, nUplet);
    //creerEnregistrement("00000001", 3, NULL);
    
    AfficherSchema(tabSchema);
        
    // Lancement du menu principal de l'application
    bool continuer = true;
	int choix = MenuPrincipal();
    while (continuer) {
        switch (choix)
        {
            case 1: {
				int choix2 = MenuSchema();
				switch(choix2)
				{
					case 1: {
						CreateSchema();
						break;
					}
					case 2: {
						cout << "2" << endl;
						break;
					}
					case 3: {
						choix = MenuPrincipal();
						break;
					}
				}
                break;
            }
            case 2: {
                cout << "2" << endl;
                break;
            }
            case 3: {
                continuer = false;
                break;
            }
        }
    }
    cout << "--------- Exit ---------" << endl;
    return 0;
}
