#include <stdlib.h>

#include "pages_manager.h"
#include "common.h"

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
    
    int position(getPositionPage());
    
    string IDBloc = getNextIDBloc();
    
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
    if(! nUplet.empty()){
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
    ajouterAdressage(IDRelation, position);

    newPage.push_back(p);
    sauvegarderPages(newPage, true);
}

vector<int> getAdressesPages(string IDRelation) {
    string tmpIDRelation;
    string addrPage;
    string ligne;
    vector<int> adressesPages;
    ifstream fRelationPages(fichierRPages().c_str());
    if(fRelationPages) {
        while (getline(fRelationPages, ligne)) {
            tmpIDRelation = ligne.substr(0, 8);
            addrPage = ligne.substr(9, 16);
            if(IDRelation.compare(tmpIDRelation) == 0){
                adressesPages.push_back(bitset< 8 >(addrPage).to_ulong());
            }
        }
    } else {
        afficherPbmOuverture(fichierRPages());
    }
    return adressesPages; 
}

// Création un nouvel enregistrement pour la relation R
bool creerEnregistrement(string IDRelation, int nbMaxNUplets, string nUplet) {

    //Contiendra toutes les adresses des pages allouées pour R
    vector<int> adressesPages(getAdressesPages(IDRelation));
    const int tailleIDBloc(8);
    
    // Chargement des pages en mémoire vive
    vector<Page> pages = chargerPages();
    
    //Pour chaque adresse trouvée ci-dessus on regarde si la page
    //a une place libre pour l'enregistrement
    bool aucunePlaceLibre(true);
    if(adressesPages.size() > 0){
        for(int u(0); u < adressesPages.size(); ++u){
            for(int v(0); v < nbMaxNUplets; ++v) {
                if(pages[u].e[tailleIDBloc + v] == '0'){
                    // La zone de gestion indique qu'il reste une place dans cette page
                    // On écrit alors l'enregistrement à cet emplacement
                    int debutNuplet(tailleIDBloc + nbMaxNUplets + nUplet.size()*v);
                    for(int w(0); w < nUplet.size(); ++w) {
                        pages[u].e[debutNuplet + w] = nUplet[w];
                    }
                    // Le bit de présence est passé à 1
                    pages[u].e[tailleIDBloc + v] = '1';
                    sauvegarderPages(pages, false);
                    return true;
                }
            }
        }
    }
    // Si aucune place libre il faut créer une nouvelle Page
    if(aucunePlaceLibre) {
        allouerPages(IDRelation, nbMaxNUplets, nUplet);
        return true;
    }
}

// Rettourne le prochain identifiant de page possible
string getNextIDBloc() {
    vector<Page> pages = chargerPages();
    string IDBlocTMP("");
    string IDBlocMAX("00000000");
    int u;
    for(int i(0); i< pages.size(); ++i){
        IDBlocTMP.clear();
        for(u= 0; u< 8; ++u){
            IDBlocTMP += pages[i].e[u];
        }
        if(bitset< 8 >(IDBlocTMP).to_ulong() > bitset< 8 >(IDBlocMAX).to_ulong()){
            IDBlocMAX.clear();
            IDBlocMAX = IDBlocTMP;
        }
    }
    int p = bitset< 8 >(IDBlocMAX).to_ulong() + 1;
    return bitset< 8 >(p).to_string();
}

void afficherPagesBrut(){
    vector<Page> pages = chargerPages();
    int i, j;
    const int taillePage(512);
    for(i= 0; i< pages.size(); ++i){
        for(j= 0; j< taillePage; ++j){
            cout << pages[i].e[j];
        }
        cout << endl;
    }
}

// Désallocation d'une page qui n'a plus de nuplet
void desallouerPage(string IDPage) {
    //cout << "Désallocation de la page " << endl;
    vector<Page> pages = chargerPages();
    int i, j;
    string IDBlocTMP;
    bool blocTrouve(false);
    const int taillePage(512);
    for(i= 0; i< pages.size(); ++i){
        for(j= 0; j< 8; ++j){
            IDBlocTMP += pages[i].e[j];
        }
        if(IDPage.compare(IDBlocTMP) == 0){
            blocTrouve = true;
            // Suppression de la page et sauvegarde en mémoire persistante
            pages.erase(pages.begin() + i);
            sauvegarderPages(pages, false);
            // Suppression d'une ligne d'adresse dans R_Pages
            supprimerAdressage(i);
        }
    }
    if(!blocTrouve){
        cout << "Page non trouvée pour l'identifiant : " << IDPage << endl;
    }
}

// Ajoute une adresse de bloc pour la relation R
void ajouterAdressage(string IDRelation, int position){
    ofstream fRelationPages(fichierRPages().c_str(), ios::app);
    if(fRelationPages) {
        fRelationPages.seekp(0, ios::end);
        fRelationPages << IDRelation;
        fRelationPages << bitset< 8 >( position ).to_string() << endl;
    } else {
        afficherPbmOuverture(fichierRPages());
    }
}

// Supprime l'adressage d'une page pour une relation
// En paramètre : la position de la page
void supprimerAdressage(int position) {
    string ligne, adresse(std::bitset< 8 >( position ).to_string());
    vector<string> all;
    ifstream fRelationPages(fichierRPages().c_str());
        
    if(fRelationPages) {
        fRelationPages.seekg(0, ios::beg);
        while(getline(fRelationPages, ligne)){
            if(adresse.compare(ligne.substr(8, 15)) != 0){
                all.push_back(ligne);
            }
        }
        fRelationPages.close();
        ofstream fRPagesTMP(fichierRPages().c_str());
        if(fRPagesTMP) {
            for(int i(0); i< all.size(); ++i){
                fRPagesTMP << all[i] << endl;
            }
        } else {
            afficherPbmOuverture(fichierRPages().c_str());
        }
    } else {
        afficherPbmOuverture(fichierRPages());
    }    
}

// Retourne la liste des identifiants des pages concernées
int deleteNupletByChamp(string IDRelation, int numChamp, string ref) {
    vector<Page> pages(chargerPages());
    vector<int> adressesPages(getAdressesPages(IDRelation));
    int i, j, k;
    const int tailleIDBloc(8);
    // Normalement fonction à implémenter
    int tailleEnregistrement(232);
    int nbMaxNuplet(2);
    vector<int> taillesChamps;
    taillesChamps.push_back(32);
    taillesChamps.push_back(200);
    bool pageVide(true);
    
    if(numChamp <= taillesChamps.size()){
        return 0;
    }
    // Déplacement pour aller au champ concerné
    int deplacementChamp(0);
    for(i= 0; i< numChamp; ++i){
        deplacementChamp +=  taillesChamps[i]; 
    }
    int deplacement = tailleIDBloc + nbMaxNuplet + deplacementChamp;
    cout << "test" << endl;
    string champTMP("");
    for(i= 0; i< adressesPages.size(); ++i) {
        for(j= 0; j< nbMaxNuplet; ++j){
            champTMP.clear();
            if(pages[i].e[tailleIDBloc + j] == '1') {
                for(k= 0; k< taillesChamps[i + 1]; ++k){
                    champTMP += pages[i].e[deplacement + j * tailleEnregistrement + k];
                }
                if(ref.compare(champTMP) == 0) {
                    //Suppression de l'enregistrement
                    pages[i].e[tailleIDBloc + j] = '0';
                }
            }
            // Vérification que la page n'est pas vide
        }
        pageVide = true;
        for(j= 0; j< nbMaxNuplet; ++j){
            if(pages[i].e[tailleIDBloc + j] == '1') {
                pageVide = false;
            }
        }
        if(pageVide){
            string IDPage("");
            for(int w(0); w< tailleIDBloc; ++w){
                IDPage += pages[i].e[w];
            }
            desallouerPage(IDPage);
        }
    }
    sauvegarderPages(pages, false);
}

// Affiche le contenu d'une Page dont l'identifiant est donné en paramètre
void afficherPage(string IDPage) {
    vector<Page> pages = chargerPages();
    int i, j;
    string IDBlocTMP;
    bool blocTrouve(false);
    const int taillePage(512);
    for(i= 0; i< pages.size(); ++i){
        IDBlocTMP.clear();
        for(j= 0; j< 8; ++j){
            IDBlocTMP += pages[i].e[j];
        }
        if(IDPage.compare(IDBlocTMP) == 0){
            blocTrouve = true;
            for(j= 0; j< taillePage; ++j){
                cout << pages[i].e[j];
            }
        }
    }
    cout << endl;
    if(!blocTrouve){
        cout << "Page non trouvée pour l'identifiant : " << IDPage << endl;
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
    
	int tailleF(tailleFichier(PathUnixWin("bdd.txt"))), i(0), j, y(1), oldI(0);
    string idRelation, zoneGestion, type, champsString, champs;
    int nbChamps(listTypesChamps.size());
    int tailleChamps, champsInt, taillePage(512);
    
    ifstream fPages(PathUnixWin("bdd.txt"));
    
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
        afficherPbmOuverture(PathUnixWin("bdd.txt"));
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