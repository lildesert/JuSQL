#include "schema.h"

using namespace std;

int menuGenerique(string titre, vector<string> menuLn)
{
	bool continuer(true);
    int choix= 0;
    while(continuer)
	{
		cout << "---------" +titre +"---------" << endl << "Menu " << endl;
		for (int i(0); i < menuLn.size() ; i++)
		{
			cout << menuLn[i] << endl;
		}
		cin >> choix;
		if(choix > 1 && choix < menuLn.size())
		{
			continuer = false;
		}
	}

	return choix;
}