#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "files.h"
#include "pages_manager.h"
#include "content_manager.h"
#include "interface.h"
#include "schema.h"
#include "common.h"
#include "test.h"

using namespace std; 

/*
 * 
 */
int main(int argc, char** argv) {

	#   ifdef _WIN32
        setlocale(LC_ALL,"");
	#   endif

	string serialFile = PathUnixWin("schema.txt");
	ifstream deserialization(serialFile.c_str());
	if(deserialization)
	{
		if(!IsFileEmpty(deserialization))
		{
			boost::archive::text_iarchive ia(deserialization);
			ia >> Schema::GetInstance();
		}
	}

	vector<int> idIncLoad = loadIdIncrement();
	if(idIncLoad.size() != 0)
	{
		Relation::idIncrementRelation = idIncLoad[0];
		Attribut::idIncrementAttribut = idIncLoad[1];
	}

	//Test de la fonction NbMaxNuplet
	/*Relation r("test");
	Attribut a1("id", "int", 4);
	Attribut a2("lib", "string", 4);
	r.addAttribut(a1);
	r.addAttribut(a2);
	Schema::GetInstance().addRelation(r);

	int test = Schema::GetInstance().GetRelationById("00000001").NbMaxNuplets();*/
    

    tester();
    
    // Lancement du menu principal de l'application
    bool continuer = true;
	int choix = MenuPrincipal();
    while (continuer) {
        switch (choix)
        {
            case 1: {
				int choix2 = MenuSchema();
				bool continuer2 = true;
				while(continuer2)
				{
					switch(choix2)
					{
						case 1: {
							CreateSchema();
							choix2 = MenuSchema();
							break;
						}
						case 2: {
							PrintSchema();
							choix2 = MenuSchema();
							break;
						}
						case 3: {
							choix = MenuPrincipal();
							continuer2 = false;
							break;
						}
					}
				}
                break;
            }
            case 2: {
                int choix3 = MenuSQL();
				bool continuer3 = true;
				while(continuer3)
				{
					switch(choix3)
					{
						case 1: {
							AjoutNuplet();
							choix3 = MenuSQL();
							break;
						}
						case 2: {
							choix3 = MenuSQL();
							break;
						}
						case 3: {
							choix3 = MenuSQL();
							break;
						}
						case 4: {
							choix = MenuPrincipal();
							continuer3 = false;
							break;
						}
					}
				}
                break;
            }
            case 3: {
                continuer = false;
                break;
            }
        }
    }
    cout << "--------- Exit ---------" << endl;

	ofstream serialization(serialFile.c_str());
	if(serialization)
	{
		if(Schema::GetInstance().getNom() != "")
		{
			boost::archive::text_oarchive oa(serialization);
			oa << const_cast<Schema &>(Schema::GetInstance());
		}
	}

	vector<int> idIncSave;
	idIncSave.push_back(Relation::idIncrementRelation);
	idIncSave.push_back(Attribut::idIncrementAttribut);
	saveIdIncrement(idIncSave);
   
    return 0;
}
