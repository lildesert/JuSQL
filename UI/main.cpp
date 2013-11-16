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
    cout << "D�marrage de JuSQL..." << endl;
    //Chargement des pages en m�moire vive
    vector<string> tabSchema; // Tableau contenant le sch�ma de la base
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
				vector<string> menuLn(3);
				menuLn[0] = "1 - Cr�er un nouveau sch�ma";
				menuLn[1] = "2 - Modifier le sch�ma existant";
				menuLn[2] = "3 - Retour � l'accueil";
				int choix2 = menuCommon("Gestion du sch�ma de la BDD", menuLn);
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
