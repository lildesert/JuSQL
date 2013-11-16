#include "schema.h"

using namespace std;

//Menu du bundle schema
void menuSchema()
{
	bool continuer(true);
    int choix= 0;
    while(continuer)
	{
		cout << "--------- Gestion du sch�ma de la BDD ---------" << endl << "Menu " << endl;
		cout << "1 - Cr�er un nouveau sch�ma" << endl;
		cout << "2 - Modifier le sch�ma existant" << endl;
		cout << "3 - Retour � l'accueil" << endl;
		cin >> choix;
		if(choix == 1 || choix == 2 || choix == 3)
		{
			continuer = false;
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
					cout << "3" << endl;
                break;
				}
			}
		}
		else
		{
			cout << "Choix impossible, veuillez ressaisir un nombre compris entre 1 et 3" << endl;
			cin >> choix;
		}
	}
}