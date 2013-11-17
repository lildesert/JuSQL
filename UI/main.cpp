#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

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
    //Chargement des pages en mémoire vive
    vector<string> tabSchema; // Tableau contenant le schéma de la base
    vector<string> tabBlocs; // Tableau des blocs
    
    creerEnregistrement("00000001", 3);
    
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