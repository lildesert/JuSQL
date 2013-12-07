#include "common.h"

#   ifdef _WIN32
#	include <windows.h>
#   endif


using namespace std;

//Affiche un menu dont le titre est passé en paramètre et dont les choix sont dans le tableau menuLn
int MenuCommon(string titre, vector<string> menuLn)
{
	ClearScreen();
	bool continuer(true);
    int choix= 0;
    while(continuer)
	{
		PrintLn("---------" +titre +"---------");
		PrintLn("");
		for (int i(0); i < menuLn.size() ; i++)
		{
			PrintLn(menuLn[i]);
		}
		cin >> choix;
		if(choix >= 1 && choix <= menuLn.size())
		{
			return choix;
		}
	}
}

//Ecrit le texte passé en paramètre dans la console puis insère un retour charriot
void PrintLn(string txt)
{
	cout << txt << endl;
}

//Efface la console
void ClearScreen()
{
	if (system("CLS")) system("clear");
	PrintLn("--------- JuSQL ---------");
}

//Stoppe l'exécution du programme pendant le nombre de secondes passées en paramètre
void PortableSleep(int sec) {
#   ifdef __linux__
        sleep(sec);
#   endif
#   ifdef _WIN32
        Sleep(sec * 1000);
#   endif
}

void saveIdIncrement(vector<int> idInc)
{
	//Save ids in file
}

vector<int> loadIdIncrement()
{
	//Load ids from file
	vector<int> result;
	return result;
}