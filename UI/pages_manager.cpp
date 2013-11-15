#include <stdlib.h>

#include "pages_manager.h"

using namespace std;

/* Allouer une page pour une relation R
 */
void allouerPages(string IDRelation, int nbMaxNuplets) {
    int taillePage(512);
    ofstream fPages("bdd.txt", ios::app); //Ouverture du fichier et curseur � la fin
    ofstream fRelationPages("R_Pages.txt", ios::app); //Ouverture du fichier et curseur � la fin
    
    if(fPages && fRelationPages) {
        int i;
        fPages << IDRelation; // Premier octet contenant l'identifiant de la relation
        // Zone de gestion initialis�e � z�ro ( Juste pour �tre clair )
        for(i= 0; i< nbMaxNuplets; ++i){ 
            fPages << 0;
        }
        //On r�serve l'emplacement pour la page avec des 0
        for(i= 0; i< (taillePage - 1 - nbMaxNuplets); ++i){ // -1 --> identifiant de la relation
            fPages << 0;
        }
        //Mise � jour du fichier Relation - Pages
        int adresseNouveauBloc(fPages.tellp());
        //Au passage, conversion integer to binary string
        fRelationPages << IDRelation << bitset< 8 >( adresseNouveauBloc ).to_string();
        
    } else {
        cout << endl << "ERREUR: Impossible d'ouvrir le fichier :" << endl;
        cout << "--> bdd.txt et/ou R_Pages.txt" << endl;
    }
}

/* Cr�er un nouvel enregistrement pour la relation R
 * A voir pour passer dynamiquement les valeurs souhait�es
 */
void creerEnregistrement(string IDRelation, int nbMaxNUplets) {
    //Faux Jeu de donn�es 
    string champsID("01000110"); // ID de type entier donc 1 octect.
    string champsContenu("0100011001000110010001100100011001000110"); //5 octets donc 5 caract�res.
    
    //Contiendra toutes les adresses des pages allou�es pour R
    vector<string> adressesPages;
    int i, j;
    // Ouverture du fichier contenant toutes les adresses de pages allou�es pour R
    ifstream fRelationPages("R_Pages.txt");
    if(fRelationPages) {
        string tmpIDRelation("");
        string addrPage("");
        fRelationPages.seekg(0, ios::end); //On se place � la fin du fichier pour conna�tre sa taille
        int tailleFichier = fRelationPages.tellg();
        fRelationPages.seekg(0, ios::beg); //On se replace au d�but du fichier
        if(tailleFichier != 0) { // Penser � contr�ler la validit� du fichier
            while(fRelationPages.tellg() < tailleFichier) { // Tant que l'on est pas � la fin du fichier
                addrPage = "";
                tmpIDRelation = "";
                for(i= 0; i < 8; ++i){ //Lecture de 8 bits
                    tmpIDRelation += fRelationPages.get();
                }
                if(IDRelation.compare(tmpIDRelation) == 0) { //Identifiants �gaux
                    for(j= 0; j < 8; ++j){
                        addrPage += fRelationPages.get();
                    }
                    adressesPages.push_back(addrPage);
                } else {
                    fRelationPages.seekg(8); //On passe directement � l'identifiant suivant
                }
            }
        }
    } else {
        cout << endl << "ERREUR: Impossible d'ouvrir le fichier : R_Pages.txt " << endl;
    }
    /*Pour chaque adresse trouv�e ci-dessus on regarde si la page
     * a une place libre pour l'enregistrement
     */
    bool aucunePlaceLibre(true);
    if(adressesPages.size() > 0){
        ifstream fPages("bdd.txt");
        if(fPages) {
            string bloc, zoneGestion, suiteFichier, ligne;
            vector<string> blocs; // Tableau de tous les blocs du fichier, que l'on remmettra dans le fichier � la fin
            int t = 0, tailleF(tailleFichier("bdd.txt"));

            while (t < tailleF) {
                // On prend 512 bits / caract�re � la fois
                bloc = ""; // On r�initialise le bloc
                for(int j= 0; j < 512; ++j) { // On prend le bloc / les 512 bits suivants
                    bloc += fPages.get();
                    ++t;
                }
                if(fPages.tellg() == (bitset< 8 >(adressesPages[i]).to_ulong() - 512)){
                    // Le bloc suivant fait partie des blocs possibles
                    // On regarde s'il y a de la place dans le bloc
                    zoneGestion = bloc.substr(8, nbMaxNUplets);
                    for(int z= 0; z < zoneGestion.size(); ++z) { // Pour chaque bit de la zone de gestion
                        cout << zoneGestion.at(z);
                        /*if(zoneGestion.at(j) ) { // Si la zone est libre 
                            // Cr�ation d'un fichier temporaire de recopie
                            ofstream fPages_tmp("tmp_bdd.txt");
                            if(fPages_tmp) {
                                // Retourne au d�but du fichier
                                fPages.seekp(0, ios::beg);
                                // On recopie tous les pages pr�c�dentes dans le fichier temporaire
                                getline(fPages, ligne);
                            suiteFichier = ligne.substr();
                            } else {
                                cout << endl << "ERREUR: Impossible d'ouvrir/cr�er le fichier temporaire : bdd_tmp.txt " << endl;
                            }
                        }*/
                        aucunePlaceLibre = false;
                    }  
                } else {
                    // On place le bloc en r�serve
                    blocs.push_back(bloc);
                }
            }
        } else {
            cout << endl << "ERREUR: Impossible d'ouvrir le fichier : bdd.txt" << endl;
        }
    }
    if(aucunePlaceLibre) { // Il faut alors cr�er une nouvelle Page
        ofstream fPages("bdd.txt");
        if(fPages){
            fPages.seekp(0, ios::end);
            string nouveauBloc;
            nouveauBloc = IDRelation;
            for(int c= 0; c< nbMaxNUplets; ++c){
                if(c == 0){
                    nouveauBloc += "1";
                } else {
                    nouveauBloc += "0";
                }
            }
            
        } else {
            cout << "ERREUR: Impossible d'ouvrir le fichier : bdd.txt";
        }
    }
}

void AfficherPages(vector<string> &tabBlocs) {
    cout << endl << "====== Affichage brut des pages ======" << endl;
    for(int i(0); i< tabBlocs.size(); ++i) {
        cout << i << ". " << tabBlocs[i] << endl;
    }
    cout << endl;
}

void AfficherPagesLisiblement(vector<string> &tabBlocs) {
    cout << "====== Affichage lisible des pages ======" << endl;
    string bloc;
    for(int i(0); i< tabBlocs.size(); ++i) {
        bloc = tabBlocs[i];
        cout << i << ". IDRelation: " << getBlocIDRelation(bloc) << " // Contenu: " << getBlocContent(bloc) << endl;
    }
    cout << endl;
}

void AfficherSchema(vector<string> &tabSchema) {
    cout << endl << "====== Affichage brut du sch�ma ======" << endl;
    for(int i(0); i< tabSchema.size(); ++i) {
        cout << i << ". " << tabSchema[i] << endl;
    }
    cout << endl;
}

/*void AfficherSchemaLisiblement(vector<string> &tabSchema) {
    cout << endl << "====== Affichage lisible du sch�ma ======" << endl;
    string IDRelation, nomChamp, typeChamp, table;
    for(int i(0); i< tabSchema.size(); ++i) {
        table = tabSchema[i]; 
        while(){
            IDRelation = getTableIDRelation(table);
            nomChamp = getTableNom(table)  
        }
        cout << i << ". IDRelation : " << tabSchema[i] << endl;
    }
    cout << endl;
}*/

string getBlocIDRelation(string bloc){
    return bloc.substr(0, 1).c_str();
}

string getBlocContent(string bloc){
    return bloc.substr(1).c_str();
}

string getTableIDRelation(string table){
    return table.substr(0, 1);
}

vector<string> getTableChamps(string table){
    /*vector<string> champs;
    table.substr(1).c_str();*/
}

/*if(typeChamp == "A") { //Entier
                contenu = ligne.substr(0, 1).c_str();
                ligne = ligne.substr(1);
            } else if (typeChamp == "B") { //String
                contenu = ligne.substr(0, 10).c_str();
                ligne = ligne.substr(10);
            }*/