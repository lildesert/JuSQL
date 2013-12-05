#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <list>
//#include <boost/archive/text_oarchive.hpp>
//#include <boost/archive/text_iarchive.hpp>


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

    std::ifstream deserialization("UI/Schema.txt");
	if(deserialization)
	{
		//boost::archive::text_iarchive ia(deserialization);
		//ia >> Schema::GetInstance();
	}
    
    //tester();
    
    // Lancement du menu principal de l'application
    bool continuer = true;
	int choix = MenuPrincipal();
    while (continuer) {
        switch (choix)
        {
            case 1: {
				int choix2 = MenuSchema();
				switch(choix2)
				{
					case 1: {
						CreateSchema();
						PortableSleep(3);
						choix2 = MenuSchema();
						break;
					}
					case 2: {
						cout << "2" << endl;
						break;
					}
					case 3: {
						choix = MenuPrincipal();
						break;
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

	std::ofstream serialization("UI/Schema.txt");
	if(serialization)
	{
		boost::archive::text_oarchive oa(serialization);
		oa << const_cast<Schema &>(Schema::GetInstance());
	}
     
    return 0;
}
