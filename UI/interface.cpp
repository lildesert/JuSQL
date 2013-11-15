#include "interface.h"

using namespace std;

// Affichage du menu de l'application
int menuPrincipal () {
    bool continuer(true);
    int choix= 0;
    while(continuer) {
        cout << "--------- JuSQL ---------" << endl << "Menu " << endl;
        cout << "1 - Gestion du schéma de la base." << endl;
        cout << "2 - Exécuter du SQL" << endl;
        cout << "3 - Quitter" << endl;
        cin >> choix;
        if(choix == 1 || choix == 2 || choix == 3) continuer = false;
    }
    return choix;
}