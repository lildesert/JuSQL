#include "interface.h"

using namespace std;

// Affichage du menu de l'application
int MenuPrincipal () {
	vector<string> menuLn(3);
	menuLn[0] = "1 - Gestion du schéma de la base";
	menuLn[1] = "2 - Exécuter du SQL";
	menuLn[2] = "3 - Quitter";
	return MenuCommon("Menu principal ", menuLn);
}

// Affichage du menu de la partie Schéma
int MenuSchema()
{
	vector<string> menuLn(3);
	menuLn[0] = "1 - Créer un nouveau schéma";
	menuLn[1] = "2 - Modifier le schéma existant";
	menuLn[2] = "3 - Retour à l'accueil";
	return MenuCommon("Gestion du schéma de la BDD", menuLn);
}

void CreateSchema()
{
	ClearScreen();
	PrintLn("--------- Création d'un nouveau schéma ---------");
	PrintLn("");
	PrintLn("Entrez un nom pour le schéma : ");
	string nomS;
	cin >> nomS;
	Schema::GetInstance().setNom(nomS);
	PrintLn("Schéma créé");
}