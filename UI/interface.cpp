#include "interface.h"
#include "files.h"
#include "pages_manager.h"

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
	menuLn[1] = "2 - Afficher le schéma";
	menuLn[2] = "3 - Retour à l'accueil";
	return MenuCommon("Gestion du schéma de la BDD", menuLn);
}

// Affichage du menu de la partie Requête
int MenuRequete() {

	vector<string> menuLn(6);
	menuLn[0] = "1 - Ajouter un Nuplet";
	menuLn[1] = "2 - Effacer un Nuplet";
	menuLn[2] = "3 - Afficher les Nuplets d'une relation";
	menuLn[3] = "4 - Sélection de Nuplet avec prédicat";
	menuLn[4] = "5 - Projection d'une relation sur tous ses attributs sauf un";
	menuLn[5] = "6 - Retour à l'accueil";
	return MenuCommon("Menu Requêtes", menuLn);
}

void CreateSchema()
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

void InterfaceCreateSchema()
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
			CreateSchema();
		}
		else if(reponse == "N")
		{
			PrintLn("Retour au menu de gestion du schéma...");
		}
	}
	else
	{
		CreateSchema();
	}

	PortableSleep(2);
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

		Retour();
	}
}

void Retour()
{
	PrintLn("");
	string answer = "";
	while(answer != "O")
	{
		PrintLn("Entrez 'O' pour revenir au menu précédent");
		cin >> answer;
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
			chaineRetour += intToBin(nb);
		}
		else
		{
			chaineRetour += asciiToBin(valueA);
			int taille = asciiToBin(valueA).size();
			int tailleChamp = a.GetTaille() * 8;
			if(taille != tailleChamp)
			{
				int manquant = tailleChamp - taille;
				for(int i = 0 ; i < manquant ; i++)
				{
					chaineRetour += "0";
				}
			}
		}
	}

	creerEnregistrement(intToBin8(r.GetId()), r.NbMaxNuplets(), chaineRetour);

	PrintLn("");
	PrintLn("Nuplet ajouté !");

	Retour();
}

void EffacerNuplet()
{
	ClearScreen();

	PrintLn("");
	PrintLn("");
	PrintLn("--------- Suppression d'un Nuplet ---------");

	PrintLn("");
	PrintLn("Veuillez entrer le nom de la relation dans laquelle vous souhaitez supprimer un nuplet : ");
	string relation;
	cin >> relation;

	Relation r = Schema::GetInstance().GetRelationByNom(relation);
	while(r.GetNom() == "")
	{
		PrintLn("");
		PrintLn("Cette relation n'existe pas dans le schéma " +Schema::GetInstance().getNom() +", veuillez entrer le nom d'une relation : ");
		cin >> relation;
		r = Schema::GetInstance().GetRelationByNom(relation);
	}


	PrintLn("");
	PrintLn("Veuillez entrer le nom de l'attribut de " +r.GetNom() +" sur lequel portera la condition de suppression : ");
	string attribut;
	cin >> attribut;

	Attribut a = r.GetAttributByNom(attribut);
	while(a.GetNom() == "")
	{
		PrintLn("");
		PrintLn("Cet attribut n'existe pas dans la relation " +r.GetNom() +", veuillez entrer le nom d'une attribut : ");
		cin >> attribut;
		a = r.GetAttributByNom(attribut);
	}

	string chaineRetour = "";

	PrintLn("Entrez la valeur pour l'attribut " +a.GetNom() +", type (" +a.GetType() +") : ");
	string valueA;
	cin >> valueA;

	if(a.GetType() == "I")
	{
		int nb = atoi(valueA.c_str());
		chaineRetour += intToBin(nb);
	}
	else
	{
		chaineRetour += asciiToBin(valueA);
		int taille = asciiToBin(valueA).size();
		int tailleChamp = a.GetTaille() * 8;
		if(taille != tailleChamp)
		{
			int manquant = tailleChamp - taille;
			for(int i = 0 ; i < manquant ; i++)
			{
				chaineRetour += "0";
			}
		}
	}

	deleteNupletByChamp(intToBin8(r.GetId()), a.GetPosition(), chaineRetour);

	PrintLn("");
	PrintLn("Nuplet(s) supprimé(s) !");

	Retour();

}

void AfficherPagesByRelation()
{
	ClearScreen();

	PrintLn("");
	PrintLn("");
	PrintLn("--------- Affichage des nuplets d'une Relation ---------");

	PrintLn("");
	PrintLn("Veuillez entrer le nom de la relation dont vous voulez afficher les nuplets : ");
	string relation;
	cin >> relation;

	Relation r = Schema::GetInstance().GetRelationByNom(relation);
	while(r.GetNom() == "")
	{
		PrintLn("");
		PrintLn("Cette relation n'existe pas dans le schéma " +Schema::GetInstance().getNom() +", veuillez entrer le nom d'une relation : ");
		cin >> relation;
		r = Schema::GetInstance().GetRelationByNom(relation);
	}

	PrintLn("");
	AfficherPages(intToBin8(r.GetId()));

	Retour();
}

void SelectWithPredicat()
{
	ClearScreen();

	PrintLn("");
	PrintLn("");
	PrintLn("--------- Sélection de Nuplet avec prédicat ---------");

	PrintLn("");
	PrintLn("Veuillez entrer le nom de la relation dans laquelle vous souhaitez sélectionner un/des nuplet(s) : ");
	string relation;
	cin >> relation;

	Relation r = Schema::GetInstance().GetRelationByNom(relation);
	while(r.GetNom() == "")
	{
		PrintLn("");
		PrintLn("Cette relation n'existe pas dans le schéma " +Schema::GetInstance().getNom() +", veuillez entrer le nom d'une relation : ");
		cin >> relation;
		r = Schema::GetInstance().GetRelationByNom(relation);
	}


	PrintLn("");
	PrintLn("Veuillez entrer le nom de l'attribut de " +r.GetNom() +" sur lequel portera la condition de sélection : ");
	string attribut;
	cin >> attribut;

	Attribut a = r.GetAttributByNom(attribut);
	while(a.GetNom() == "")
	{
		PrintLn("");
		PrintLn("Cet attribut n'existe pas dans la relation " +r.GetNom() +", veuillez entrer le nom d'une attribut : ");
		cin >> attribut;
		a = r.GetAttributByNom(attribut);
	}

	string chaineRetour = "";

	PrintLn("Entrez la valeur pour l'attribut " +a.GetNom() +", type (" +a.GetType() +") : ");
	string valueA;
	cin >> valueA;

	if(a.GetType() == "I")
	{
		int nb = atoi(valueA.c_str());
		chaineRetour += intToBin(nb);
	}
	else
	{
		chaineRetour += asciiToBin(valueA);
		int taille = asciiToBin(valueA).size();
		int tailleChamp = a.GetTaille() * 8;
		if(taille != tailleChamp)
		{
			int manquant = tailleChamp - taille;
			for(int i = 0 ; i < manquant ; i++)
			{
				chaineRetour += "0";
			}
		}
	}

	selectByChamp(intToBin8(r.GetId()), a.GetPosition(), chaineRetour);

	Retour();
}

void ProjectionWithoutOneAtt()
{
	ClearScreen();

	PrintLn("");
	PrintLn("");
	PrintLn("--------- Sélection de Nuplet avec prédicat ---------");

	PrintLn("");
	PrintLn("Veuillez entrer le nom de la relation sur laquelle vous souhaitez réaliser la projection : ");
	string relation;
	cin >> relation;

	Relation r = Schema::GetInstance().GetRelationByNom(relation);
	while(r.GetNom() == "")
	{
		PrintLn("");
		PrintLn("Cette relation n'existe pas dans le schéma " +Schema::GetInstance().getNom() +", veuillez entrer le nom d'une relation : ");
		cin >> relation;
		r = Schema::GetInstance().GetRelationByNom(relation);
	}

	PrintLn("");
	PrintLn("Veuillez entrer le nom de l'attribut de " +r.GetNom() +" à enlever de la projection : ");
	string attribut;
	cin >> attribut;

	Attribut a = r.GetAttributByNom(attribut);
	while(a.GetNom() == "")
	{
		PrintLn("");
		PrintLn("Cet attribut n'existe pas dans la relation " +r.GetNom() +", veuillez entrer le nom d'une attribut : ");
		cin >> attribut;
		a = r.GetAttributByNom(attribut);
	}

	Relation tmpRel = r;
	tmpRel.GetAttributs().erase(tmpRel.GetAttributs().begin() + a.GetPosition());
	tmpRel.SetNom(r.GetNom() +"TMP");
	Schema::GetInstance().addRelationTMP(r);

	Retour();
}
