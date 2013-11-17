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
    cout << "Démarrage de JuSQL..." << endl;
    //Chargement des pages en mémoire vive
    vector<string> tabSchema; // Tableau contenant le schéma de la base
    vector<string> tabBlocs; // Tableau des blocs
    
    list<string> nUplet;
    nUplet.push_back("00100101"); // ID
    nUplet.push_back("000000010000000100000001"); // Trois caractères
    allouerPages("00000001", 3, nUplet);
    //creerEnregistrement("00000001", 3, NULL);
    
    AfficherSchema(tabSchema);
        
    // Lancement du menu principal de l'application
    bool continuer = true;
    while (continuer) {
        int choix = menuPrincipal();
        switch (choix)
        {
            case 1: {
				vector<string> menuLn(3);
				menuLn[0] = "1 - Créer un nouveau schéma";
				menuLn[1] = "2 - Modifier le schéma existant";
				menuLn[2] = "3 - Retour à l'accueil";
				int choix2 = menuCommon("Gestion du schéma de la BDD", menuLn);
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
