#include "schema.h"

using namespace std;

int menuCommon(string titre, vector<string> menuLn)
{
	bool continuer(true);
    int choix= 0;
    while(continuer)
	{
		println("---------" +titre +"---------");
		println("Menu ");
		for (int i(0); i < menuLn.size() ; i++)
		{
			println(menuLn[i]);
		}
		cin >> choix;
		if(choix > 1 && choix < menuLn.size())
		{
			continuer = false;
		}
	}

	return choix;
}

void println(string txt)
{
	cout << txt << endl;
}