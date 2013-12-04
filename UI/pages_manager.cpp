#include <stdlib.h>

#include "pages_manager.h"

using namespace std;

/* Allouer une page pour une relation R.
 * Cette allocation est réalisée directement dans le fichier.
 * Il est possible d'initaliser directement la page nouvellement allouée 
 * avec un enregistrement passé en paramètre.
 * @param string IDRelation[] : tableau 
 */
void allouerPages(string IDRelation, int nbMaxNuplets, string nUplet) {
    // Initialisations
    int i(0), j(0);
    const int taillePage(512);
    vector<Page> newPage;
    Page p;
    int adresseNouveauBloc;
    //Lecture des deux fichiers avec curseur à la fin
    ifstream fPages("UI/bdd.txt");
    ofstream fRelationPages("UI/R_Pages.txt");
    
    string IDBloc = '00000010';
    
    if(fPages) {
        fPages.seekg(0, ios::end);
        if(fRelationPages) {
            fRelationPages.seekp(0, ios::end);
            
            if(fPages.tellg() > 0) {
                //Sauvegarde de la position dans le fichier si bits
                adresseNouveauBloc = fPages.tellg() / 512;
                //Sauvegarde de la position dans le fichier si ASCII
                //adresseNouveauBloc = fPages.tellg() / 64;
            } 
            
            //Ecriture de l'octet de la l'identifiant du bloc
            for(i= 0; i< 8; i++){
                p.e[j] = IDBloc[i];
                ++j;
            }
            // Zone de gestion initialisée à zéro sauf si on intègre directement un enregistrement
            for(i= 0; i< nbMaxNuplets; ++i){
                if(nUplet.size() != 0 && i== 0) {
                    // On insère en même temps un enregistrement
                    p.e[j] = '1'; 
                } else {
                    p.e[j] = '0';
                }
                ++j;
            }
            if(nUplet && nUplet.size() > 0){
                // Insertion du N-Uplet passés en paramètres
                for(i= 0; i< nUplet.size(); ++i){
                    p.e[j] = nUplet[i];
                    ++j;
                }
            }
            //On réserve l'emplacement pour la page avec des 0
            while(j < taillePage) {
                p.e[j] = '0';
                ++j;
            }
            //Mise à jour du fichier Relation - Pages
            fRelationPages << endl << IDRelation;
            
            fRelationPages << bitset< 8 >( adresseNouveauBloc ).to_string();
            
            newPage.push_back(p);
            sauvegarderPages(newPage, 1, true);
        } else {
            afficherPbmOuverture("UI/R_Pages.txt");
        }
    } else {
        afficherPbmOuverture("UI/bdd.txt");
    }
}

/* Création un nouvel enregistrement pour la relation R
 * 
 */
bool creerEnregistrement(string IDRelation, int nbMaxNUplets, string nUplet) {

    //Contiendra toutes les adresses des pages allouées pour R
    vector<int> adressesPages;
    int i, j;
    const int tailleIDBloc(8);
    // Ouverture du fichier contenant toutes les adresses de pages allouées aux relations
    ifstream fRelationPages("UI/R_Pages.txt");
    if(fRelationPages) {
        string tmpIDRelation;
        string addrPage;
        
        string ligne;
        while (fRelationPages.getline(ligne)) {
            tmpIDRelation = ligne.substr(0, 8);
            addrPage = ligne.substr(9, 16);
            if(IDRelation.compare(tmpIDRelation)){
                adressesPages.push_back(bitset< 8 >(addrPage).to_ulong());
            }
        }
    } else {
        afficherPbmOuverture("UI/R_Pages.txt");
        return false;
    }
    // Chargement des pages en mémoire vive
    vector<Page> pages = chargerPages();
    //Pour chaque adresse trouvée ci-dessus on regarde si la page
    //a une place libre pour l'enregistrement
    bool aucunePlaceLibre(true);
    if(adressesPages.size() > 0){
        ifstream fPages("UI/bdd.txt");
        if(fPages) {
            string zoneLibre;
            for(int u(0); u < adressesPages.size(); ++u){
                for(int v(0); v < nbMaxNUplets; ++v) {
                    if(pages[u].e[tailleIDBloc + v] == "0"){
                        // La zone de gestion indique qu'il reste une place dans cette page
                        // On écrit alors l'enregistrement à cet emplacement
                        for(int w(0); w < nUplet.size(); ++w) {
                            pages[u].e[tailleIDBloc + nbMaxNUplets + w] = nUplet[w];
                        }
                        // Le bit de présence est passé à 1
                        pages[u].e[tailleIDBloc + v]pages[u] = "1";
                        sauvegarderPages(pages, false);
                        return true;
                    }
                }
            }
        } else {
            afficherPbmOuverture("UI/bdd.txt");
            return false;
        }
    }
    // Si aucune place libre il faut créer une nouvelle Page
    if(aucunePlaceLibre) {
        allouerPages(IDRelation, nbMaxNUplets, nUplet);
        return true;
    }
}

void AfficherPages() {
    cout << endl << "====== Affichage des pages ======" << endl;
    
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
            
            // ========== Attente fonction ======
            // Prendre les taillesChamps et types champs pour l'ID de relation
            // ============================
            
            for(j = 0; j< nbMaxNUplets; ++j){
                zoneGestion += fPages.get();
                ++i;
            }
            i += nbMaxNUplets;
            cout << "\tZone de gestion : " << zoneGestion << endl;
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