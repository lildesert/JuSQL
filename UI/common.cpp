#include "common.h"
#include "files.h"
#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>

#   ifdef _WIN32
#	include <windows.h>
#   endif

#   ifdef __linux__
#       include <unistd.h>
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
	string serialIdFile = PathUnixWin("idRelAtt.txt");
	ofstream saveId(serialIdFile.c_str());
	if(saveId)
	{
		//Save ids in file
		for (auto &id : idInc)
		{
			saveId << id;
			saveId << "|";
		}
	}
}

vector<int> loadIdIncrement()
{
	string serialIdFile = PathUnixWin("idRelAtt.txt");
	//Load ids from file
	vector<int> result;

	ifstream loadId(serialIdFile.c_str());
	if(loadId)
	{
		if(!IsFileEmpty(loadId))
		{
			string chaine;
			loadId >> chaine;
			vector<string> tabResult;
			boost::split(tabResult, chaine, boost::is_any_of("|"));
			for (auto &s : tabResult)
			{
				if(s != "")
				{
					result.push_back(atoi(s.c_str()));
				}
			}
		}
	}

	return result;
}

string PathUnixWin(string path)
{
	#   ifdef __linux__
        return "UI/" +path;
	#   endif

	#   ifdef _WIN32
		return path;
	#   endif
}

