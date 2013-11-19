#include <stdlib.h>

#include "pages_manager.h"

using namespace std;

/* Allouer une page pour une relation R
 * si champs est à null alors allocation d'un bloc vide
 */
void allouerPages(string IDRelation, int nbMaxNuplets, list<string> nUplet) {
    int taillePage(512), i;
    ofstream fPages("UI/bdd.txt", ios::app); //Ouverture du fichier et curseur à la fin
    ofstream fRelationPages("UI/R_Pages.txt", ios::app); //Ouverture du fichier et curseur à la fin
    
    if(fPages) {
        if(fRelationPages) {
            int adresseNouveauBloc(fPages.tellp());
            fPages << IDRelation; // Premier octet contenant l'identifiant de la relation
            // Zone de gestion initialisée à zéro sauf si la map contient un n-uplet
            for(i= 0; i< nbMaxNuplets; ++i){
                if(nUplet.size() != 0 && i== 0) {
                    fPages << 1; // On insère en même temps un enregistrement
                } else {
                    fPages << 0;
                }
            }
            i= 0;
            if(nUplet.size() != 0){
                string champ;
                for(list<string>::iterator it= nUplet.begin(); it!= nUplet.end(); ++it) {
                    champ = *it;
                    i += champ.size();
                    fPages << champ; // Insertion du N-Uplet passé en paramètre
                }
            }
            //On réserve l'emplacement pour la page avec des 0
            while(i < taillePage - 8 - nbMaxNuplets) { // -8 --> identifiant de la relation
                fPages << "0";
                ++i;
            }
            //Mise à jour du fichier Relation - Pages
            //Au passage, conversion integer to binary string
            fRelationPages << IDRelation << bitset< 8 >( adresseNouveauBloc ).to_string();
        } else {
            afficherPbmOuverture("UI/R_Pages.txt");
        }
    } else {
        afficherPbmOuverture("UI/bdd.txt");
    }
}

/* Créer un nouvel enregistrement pour la relation R
 * A voir pour passer dynamiquement les valeurs souhaitées
 */
void creerEnregistrement(string IDRelation, int nbMaxNUplets, list<string> nUplet) {
    //Faux Jeu de données 
    string champsID("01000110"); // ID de type entier donc 1 octect.
    string champsContenu("0100011001000110010001100100011001000110"); //5 octets donc 5 caractères.
    
    //Contiendra toutes les adresses des pages allouées pour R
    vector<string> adressesPages;
    int i, j;
    // Ouverture du fichier contenant toutes les adresses de pages allouées pour R
    ifstream fRelationPages("UI/R_Pages.txt");
    if(fRelationPages) {
        string tmpIDRelation("");
        string addrPage("");
        fRelationPages.seekg(0, ios::end); //On se place à la fin du fichier pour connaitre sa taille
        int tailleFichier = fRelationPages.tellg();
        fRelationPages.seekg(0, ios::beg); //On se replace au début du fichier
        if(tailleFichier != 0) { // Penser à contrôler la validité du fichier
            while(fRelationPages.tellg() < tailleFichier) { // Tant que l'on est pas à la fin du fichier
                addrPage = "";
                tmpIDRelation = "";
                for(i= 0; i < 8; ++i){ //Lecture de 8 bits
                    tmpIDRelation += fRelationPages.get();
                }
                if(IDRelation.compare(tmpIDRelation) == 0) { //Identifiants égaux
                    for(j= 0; j < 8; ++j){
                        addrPage += fRelationPages.get();
                    }
                    adressesPages.push_back(addrPage);
                } else {
                    fRelationPages.seekg(8); //On passe directement à l'identifiant suivant
                }
            }
        }
    } else {
        afficherPbmOuverture("UI/R_Pages.txt");
    }
    /*Pour chaque adresse trouvée ci-dessus on regarde si la page
     * a une place libre pour l'enregistrement
     */
    bool aucunePlaceLibre(true);
    if(adressesPages.size() > 0){
        ifstream fPages("UI/bdd.txt");
        if(fPages) {
            string bloc, zoneGestion, suiteFichier, ligne;
            vector<string> blocs; // Tableau de tous les blocs du fichier, que l'on remmettra dans le fichier à la fin
            int t = 0, tailleF(tailleFichier("UI/bdd.txt"));

            while (t < tailleF) {
                // On prend 512 bits / caractère à la fois
                bloc = ""; // On réinitialise le bloc
                for(int j= 0; j < 512; ++j) { // On prend le bloc / les 512 bits suivants
                    bloc += fPages.get();
                    ++t;
                }
                if(fPages.tellg() = (bitset< 8 >(adressesPages[i]).to_ulong() - 512)){
                    // Le bloc suivant fait partie des blocs possibles
                    // On regarde s'il y a de la place dans le bloc
                    zoneGestion = bloc.substr(8, nbMaxNUplets);
                    for(int z= 0; z < zoneGestion.size(); ++z) { // Pour chaque bit de la zone de gestion
                        cout << zoneGestion.at(z);
                        /*if(zoneGestion.at(j) ) { // Si la zone est libre 
                            // Création d'un fichier temporaire de recopie
                            ofstream fPages_tmp("tmp_bdd.txt");
                            if(fPages_tmp) {
                                // Retourne au début du fichier
                                fPages.seekp(0, ios::beg);
                                // On recopie tous les pages précédentes dans le fichier temporaire
                                getline(fPages, ligne);
                            suiteFichier = ligne.substr();
                            } else {
                                cout << endl << "ERREUR: Impossible d'ouvrir/créer le fichier temporaire : bdd_tmp.txt " << endl;
                            }
                        }*/
                        aucunePlaceLibre = false;
                    }  
                } else {
                    // On place le bloc en réserve
                    blocs.push_back(bloc);
                }
            }
        } else {
            afficherPbmOuverture("UI/bdd.txt");
        }
    }
    // Si aucune place libre il faut créer une nouvelle Page
    if(aucunePlaceLibre) {
        ofstream fPages("UI/bdd.txt");
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
            afficherPbmOuverture("UI/bdd.txt");
        }
    }
}

void AfficherPages() {
    cout << endl << "====== Affichage brut des pages ======" << endl;
    
    //======= ATTENTE DE LA FONCTION DE JULIEN =======
    int nbMaxNUplets(5);
    //================================================
    
    //======= ATTENTE DE LA FONCTION DE JULIEN =======
    list <int> listTaillesChamps;
    listTaillesChamps.push_back(8); // 1 entier
    listTaillesChamps.push_back(40); // 5 caractères
    //================================================
    
    //======= ATTENTE DE LA FONCTION DE JULIEN =======
    list <string> listTypesChamps;
    listTypesChamps.push_back("id");
    listTypesChamps.push_back("char[5]");
    //================================================
    
    int tailleF(tailleFichier("UI/bdd.txt")), i(0), j, y(1), oldI(0);
    string idRelation, zoneGestion, type, champsString, champs;
    int nbChamps(listTypesChamps.size());
    int tailleChamps, champsInt, taillePage(512);
    
    ifstream fPages("UI/bdd.txt");
    
    if(fPages) {
        while(i < tailleF){
            // Réinitialisations 
            idRelation = "";
            zoneGestion = "";
            oldI = i;
            cout << y << ". " << "Bloc :" << endl;
            for(j = 0; j< 8; ++j){
                idRelation += fPages.get();
            }
            i += 8;
            cout << "\tIDRelation : " << idRelation << endl;
            for(j = 0; j< nbMaxNUplets; ++j){
                zoneGestion += fPages.get();
                ++i;
            }
            i += nbMaxNUplets;
            cout << "\tZone de gestion : " zoneGestion << endl;
            for(j = 0; j< nbMaxNUplets; ++j){
                zoneGestion += fPages.get();
            }
            i += nbMaxNUplets;
            list<int>::iterator itTailleChamps= listTaillesChamps.begin();
            for(list<string>::iterator it= listTypesChamps.begin(); it!= listTypesChamps.end(); ++it) {
                type = *it;
                tailleChamps = *itTailleChamps;
                ++itTailleChamps;
                for(j = 0; j< tailleChamps; ++j){
                    champs += fPages.get();
                }
                i += tailleChamps;
                if(type == "id"){
                    champsInt = bitset< 8 >(champs).to_ulong();
                } else if (type == "char"){
                    
                } else {
                    cout << "Aucun type ne correspond. Impossible d'afficher les pages de la base." << endl;
                }
            }
            i += taillePage - (i - oldI);
            ++y;
        }
    } else {
        afficherPbmOuverture("UI/bdd.txt");
    }
    cout << endl;
}

void AfficherPagesLisiblement() {
    cout << "====== Affichage lisible des pages ======" << endl;
    string bloc;
    
    cout << endl;
}

void AfficherSchema(vector<string> &tabSchema) {
    cout << endl << "====== Affichage brut du schéma ======" << endl;
    for(int i(0); i< tabSchema.size(); ++i) {
        cout << i << ". " << tabSchema[i] << endl;
    }
    cout << endl;
}

/*void AfficherSchemaLisiblement(vector<string> &tabSchema) {
    cout << endl << "====== Affichage lisible du schéma ======" << endl;
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

/*vector<string> getTableChamps(string table){
    vector<string> champs;
    table.substr(1).c_str();
}*/

/*if(typeChamp == "A") { //Entier
                contenu = ligne.substr(0, 1).c_str();
                ligne = ligne.substr(1);
            } else if (typeChamp == "B") { //String
                contenu = ligne.substr(0, 10).c_str();
                ligne = ligne.substr(10);
            }*/