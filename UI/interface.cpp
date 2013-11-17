#include "interface.h"

using namespace std;

// Affichage du menu de l'application
int MenuPrincipal () {
	vector<string> menuLn(3);
	menuLn[0] = "1 - Gestion du sch�ma de la base";
	menuLn[1] = "2 - Ex�cuter du SQL";
	menuLn[2] = "3 - Quitter";
	return MenuCommon("Menu principal ", menuLn);
}

// Affichage du menu de la partie Sch�ma
int MenuSchema()
{
	vector<string> menuLn(3);
	menuLn[0] = "1 - Cr�er un nouveau sch�ma";
	menuLn[1] = "2 - Modifier le sch�ma existant";
	menuLn[2] = "3 - Retour � l'accueil";
	return MenuCommon("Gestion du sch�ma de la BDD", menuLn);
}

void CreateSchema()
{
	PrintLn("--------- Cr�ation d'un nouveau sch�ma ---------");
	PrintLn("");
	PrintLn("Entrez un nom pour le sch�ma : ");
	string nomS;
	cin >> nomS;
	Schema s(nomS);
	PrintLn("Sch�ma cr��");
}