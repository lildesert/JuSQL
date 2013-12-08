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

	string serialFile = "schema.txt";
	ifstream deserialization(serialFile.c_str());
	if(deserialization)
	{
		if(!IsFileEmpty(deserialization))
		{
			boost::archive::text_iarchive ia(deserialization);
			ia >> Schema::GetInstance();
		}
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
							PortableSleep(2);
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
                cout << "2" << endl;
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
   
    return 0;
}
