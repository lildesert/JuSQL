#include <stdlib.h>

#include "pages_manager.h"
#include "common.h"
#include "Relation.h"
#include "schema.h"

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
    int tailleNuplet(Schema::GetInstance().GetRelationById(IDRelation).GetTailleNuplet());
    
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
                    for(int a(nUplet.size()); a < tailleNuplet - nUplet.size(); ++a){
                        pages[u].e[debutNuplet + a] = '0';
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

    // Initialisations des variables en fonction de la relation concernée
    int tailleEnregistrement(Schema::GetInstance().GetRelationById(IDRelation).GetTailleNuplet());
    int nbMaxNuplet(Schema::GetInstance().GetRelationById(IDRelation).NbMaxNuplets());
    vector<int> taillesChamps(Schema::GetInstance().GetRelationById(IDRelation).GetTaillesAttributs());
    
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

void AfficherPages(string IDRelation) {
    cout << endl << "====== Affichage des pages ======" << endl;
    cout << "Relation : " << IDRelation << endl;
    
    int tailleIDBloc(8);
    int nbMaxNUplets(Schema::GetInstance().GetRelationById(IDRelation).NbMaxNuplets());
    vector<int> listTaillesChamps(Schema::GetInstance().GetRelationById(IDRelation).GetTaillesAttributs());
    vector<string> listTypesChamps(Schema::GetInstance().GetRelationById(IDRelation).GetTypesAttributs());
    int tailleNuplet(Schema::GetInstance().GetRelationById(IDRelation).GetTailleNuplet());
    
    vector<Page> pages(chargerPages());
    vector<int> adressesPages(getAdressesPages(IDRelation));
    
    string champ("");
    int i, j, k, l;
    int nbChamps(listTaillesChamps.size());
    int departNuplet, departChamp;
    
    // Pour toutes les adresses de pages
    for(i= 0; i< adressesPages.size(); ++i) {
        cout << "Page " << i + 1 << " : " << endl;
        // Pour tous les enregistrements de la page i
        for(j= 0; j< nbMaxNUplets; ++j){
            departChamp = 0;
            if(pages[i].e[tailleIDBloc + j] == '1'){
                cout << "\tEnregistrement " << j + 1 << " : " << endl;
                // Pour tous les champs de l'enregistrement j
                for(k= 0; k< nbChamps; ++k){
                    champ.clear(); 
                    departNuplet = tailleIDBloc + nbMaxNUplets + j*tailleNuplet;
                    // Pour tous les bits du champ k
                    for(l= 0; l< listTaillesChamps[k]*8; ++l){
                        champ += pages[i].e[departNuplet + departChamp + l];
                    }
                    departChamp += listTaillesChamps[k]*8;
                    // Affichage du champ en focntion de son type
                    if(listTypesChamps[k].compare("I") == 0){
                        if(champ.size() == 8) {
                            cout << "\t\tChamps " << k + 1 << " : " << bin8ToInt(champ) << endl;
                        } else if (champ.size() == 4){
                            cout << "\t\tChamps " << k + 1 << " : " << binToInt(champ) << endl;
                        } else {
                            cout << "\t\tChamps " << k + 1 << " : " << champ << endl;
                        }
                    } else {
                        cout << "\t\tChamps " << k + 1 << " : " << binToAscii(champ) << endl;
                    }                   
                }
            }
        }
    }
}