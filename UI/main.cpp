#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "files.h"
#include "pages_manager.h"
#include "content_manager.h"
#include "interface.h"

using namespace std; 

/*
 * 
 */
int main(int argc, char** argv) {
    cout << "Démarrage de JuSQL..." << endl;
    //Chargement des pages en mémoire vive
    vector<string> tabSchema; // Tableau contenant le schéma de la base
    vector<string> tabBlocs; // Tableau des blocs
    
    creerEnregistrement("00000001", 3);
    
    AfficherSchema(tabSchema);
        
    // Lancement du menu principal de l'application
    bool continuer = true;
    while (continuer) {
        int choix = menuPrincipal();
        switch (choix)
        {
            case 1: {
                cout << "1" << endl;
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

