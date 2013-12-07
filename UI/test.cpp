#include "test.h"

using namespace std;

void tester() {
    // On réinitialise les fichiers
    viderFichier(fichierBDD());
    viderFichier(fichierRPages());
    
    string IDRelation1("00000001");
    string IDRelation2("00000010");
    
    int nbMaxNuplet1(2);
    int nbMaxNuplet2(2);
    
    // Enregistrements
    string nuplet1 = intToBin(1) + asciiToBin("AZERTYUIOPQSDFGHJKLMWXCVB");
    string nuplet2 = intToBin(2) + asciiToBin("FGFGFGFGFGFGFGFGFGFGFGFGF");
    
    string nuplet3 = intToBin(1) + asciiToBin("Salade");
    string nuplet4 = intToBin(2) + asciiToBin("Tomate");
    
    cout << "Taille du fichier Bdd : " << tailleFichier(fichierBDD()) << endl;
    cout << "Taille du fichier R_Pages : " << tailleFichier(fichierRPages()) << endl << endl;
    
    // Allocation d'une première page pour R1
    allouerPages(IDRelation1, nbMaxNuplet1, nuplet1);
    
    vector<Page> pages = chargerPages();
    cout << "Nombre de pages : " << pages.size() << endl;
    
    afficherPage("00000001");
    
    cout << "Taille du fichier Bdd : " << tailleFichier(fichierBDD()) << endl;
    cout << "Taille du fichier R_Pages : " << tailleFichier(fichierRPages()) << endl << endl;
    
    // Création d'un deuxième enregistrement
    creerEnregistrement(IDRelation1, nbMaxNuplet1, nuplet2);
    
    pages = chargerPages();
    cout << "Nombre de pages : " << pages.size() << endl;
    
    afficherPage("00000001");
    cout << endl << endl;
    
    // Alloca
    allouerPages(IDRelation2, nbMaxNuplet2, nuplet2);
    
    pages = chargerPages();
    cout << "Nombre de pages : " << pages.size() << endl;
    
    cout << "Taille du fichier Bdd : " << tailleFichier(fichierBDD()) << endl;
    cout << "Taille du fichier R_Pages : " << tailleFichier(fichierRPages()) << endl << endl;
    
    //creerEnregistrement(IDRelation1, nbMaxNuplet1, nuplet3);
    
    //cout << "Taille du fichier Bdd : " << tailleFichier(fichierBDD()) << endl;
    //cout << "Taille du fichier R_Pages : " << tailleFichier(fichierRPages()) << endl << endl;
    
    // Désallocation d'une page pour R1
    //desallouerPage(IDRelation1);
    
    //cout << "Taille du fichier Bdd : " << tailleFichier(fichierBDD()) << endl;
    //cout << "Taille du fichier R_Pages : " << tailleFichier(fichierRPages()) << endl << endl;
}