#include "interface.h"

using namespace std;

// Affichage du menu de l'application
int MenuPrincipal () {
	char e_aigu=0x82;
	char e_grave=0x8A;

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

	if(Schema::GetInstance().getNom() != "")
	{
		string reponse = "";
		while(reponse != "O" && reponse != "N")
		{
			PrintLn("Attention la création d'un nouveau schéma supprimera le schéma existant, continuer ? (O/N)");
			cin >> reponse;
		}

		if(reponse == "O")
		{
			PrintLn("--------- Création d'un nouveau schéma ---------");
			PrintLn("");
			PrintLn("Entrez un nom pour le schéma : ");
			string nomS;
			cin >> nomS;
			Schema::GetInstance().setNom(nomS);

			PrintLn("");
			PrintLn("--------- Ajout de relations ---------");
			PrintLn("");
			bool addRel = true;
			while (addRel)
			{
				string answer = "";
				while(answer != "O" && answer != "N")
				{
					PrintLn("Ajouter une relation ? (O/N)");
					cin >> answer;
				}

				if(answer == "O")
				{
					PrintLn("Nom de la Relation : ");
					string nomR;
					cin >> nomR;

					Relation r(nomR);

					PrintLn("--------- Définition des attributs de " +r.getNom() +" ---------");

					bool addAtt = true;
					while (addAtt)
					{
						string answerA = "";
						while(answerA != "O" && answerA != "N")
						{
							PrintLn("Ajouter un attribut à la relation " +r.getNom() +" ? (O/N)");
							cin >> answerA;
						}

						if(answerA == "O")
						{
							PrintLn("Nom de l'attribut : ");
							string nomA;
							cin >> nomA;
					
							string typeA = "";
							while(typeA != "S" && typeA != "I")
							{
								PrintLn("Type de l'attribut " +nomA +" string(S) / int(I) : ");
								cin >> typeA;
							}

							PrintLn("Taille de l'attribut " +nomA +" : ");
							int tailleA;
							cin >> tailleA;

							Attribut a(nomA, typeA, tailleA);
							r.addAttribut(a);
						}
						else if(answerA == "N")
						{
							addAtt = false;
						}
					}

					Schema::GetInstance().addRelation(r);
				}
				else if(answer == "N")
				{
					addRel = false;
				}

			}

			PrintLn("Schéma enregistré !");
		}
		else if(reponse == "N")
		{
			PrintLn("Retour au menu de gestion du schéma...");
		}
	}
}