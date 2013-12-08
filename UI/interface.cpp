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
	menuLn[1] = "2 - Afficher le schéma";
	menuLn[2] = "3 - Retour à l'accueil";
	return MenuCommon("Gestion du schéma de la BDD", menuLn);
}

// Affichage du menu de la partie SQL
int MenuSQL() {

	vector<string> menuLn(4);
	menuLn[0] = "1 - Ajouter un Nuplet";
	menuLn[1] = "2 - Effacer un Nuplet";
	menuLn[2] = "3 - Sélectionner un Nuplet";
	menuLn[3] = "4 - Retour à l'accueil";
	return MenuCommon("Menu SQL", menuLn);
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
			Schema::GetInstance().DeleteAllRelations();

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

					PrintLn("--------- Définition des attributs de " +r.GetNom() +" ---------");

					bool addAtt = true;
					while (addAtt)
					{
						string answerA = "";
						while(answerA != "O" && answerA != "N")
						{
							PrintLn("Ajouter un attribut à la relation " +r.GetNom() +" ? (O/N)");
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

void PrintSchema()
{
	ClearScreen();
	if(Schema::GetInstance().getNom() == "")
	{
		PrintLn("Aucun schéma n'a été défini, retour au menu...");
		PortableSleep(2);
	}
	else
	{
		PrintLn("");
		PrintLn("");
		PrintLn("");
		PrintLn("--------- Schéma : " +Schema::GetInstance().getNom() +" ---------");
		PrintLn("");

		for (auto &r : Schema::GetInstance().GetRelations())
		{
			PrintLn("");
			PrintLn("-----------------------------------------");
			PrintLn("--------- Relation : " +r.GetNom() +" ---------");
			PrintLn("");

			for (auto &a : r.GetAttributs())
			{
				PrintLn("");
				PrintLn("--------- Attribut : " +a.GetNom() +" ---------");
				string type = "";
				if(a.GetType() == "S")
				{
					type = "string";
				}
				else if(a.GetType() == "I")
				{
					type = "int";
				}
				PrintLn("--------- Type : " +type +" ---------");
				PrintLn("--------- Taille : " +to_string(a.GetTaille()) +" octet(s) ---------");
				PrintLn("");
			}

			PrintLn("-----------------------------------------");
		}

		PrintLn("");
		string answer = "";
		while(answer != "O")
		{
			PrintLn("Entrez 'O' pour revenir au menu précédent");
			cin >> answer;
		}
	}
}

void AjoutNuplet()
{
	ClearScreen();

	PrintLn("");
	PrintLn("");
	PrintLn("--------- Ajout d'un Nuplet ---------");

	PrintLn("");
	PrintLn("Veuillez entrer le nom de la relation dans laquelle vous souhaitez ajouter un nuplet : ");
	string relation;
	cin >> relation;

	Relation r = Schema::GetInstance().GetRelationByNom(relation);;
	while(r.GetNom() == "")
	{
		PrintLn("");
		PrintLn("Cette relation n'existe pas dans le schéma " +Schema::GetInstance().getNom() +", veuillez entrer le nom d'une relation : ");
		cin >> relation;
		r = Schema::GetInstance().GetRelationByNom(relation);
	}

	string chaineRetour = "";
	for (auto &a : r.GetAttributs())
	{
		PrintLn("Entrez une valeur pour l'attribut " +a.GetNom() +", type (" +a.GetType() +") : ");
		string valueA;
		cin >> valueA;

		if(a.GetType() == "I")
		{
			int nb = atoi(valueA.c_str());
			const int taille = a.GetTaille();
			chaineRetour += bitset< 32 >( nb ).to_string();
		}

	}

}