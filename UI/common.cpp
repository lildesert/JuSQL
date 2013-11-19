#include "common.h"

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

void PortableSleep(int sec) {
#   ifdef POSIX
        sleep(sec);
#   endif
#   ifdef WINDOWS
        Sleep(sec * 1000);
#   endif
}