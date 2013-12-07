#include "test.h"

using namespace std;

void tester() {
    cout << "Nombre de pages : " << chargerPages().size() << endl;
    // On réinitialise les fichiers
    cout << "Initialisation des fichiers." << endl;
    viderFichier(fichierBDD());
    viderFichier(fichierRPages());
    cout << "Taille du fichier Bdd : " << tailleFichier(fichierBDD()) << endl;
    cout << "Taille du fichier R_Pages : " << tailleFichier(fichierRPages()) << endl << endl;
    
    string IDRelation1("00000001");
    string IDRelation2("00000010");
    
    int nbMaxNuplet1(2);
    int nbMaxNuplet2(2);
    
    // Enregistrements
    string nuplet1 = intToBin(1) + asciiToBin("AZERTYUIOPQSDFGHJKLMWXCVB");
    string nuplet2 = intToBin(2) + asciiToBin("FGFGFGFGFGFGFGFGFGFGFGFGF");
    
    string nuplet3 = intToBin(1) + asciiToBin("Salade");
    string nuplet4 = intToBin(2) + asciiToBin("Tomate");
    
    
    cout << "Allocation d'une première page pour R1." << endl;
    allouerPages(IDRelation1, nbMaxNuplet1, nuplet1);
    cout << "Nombre de pages : " << chargerPages().size() << endl;
    afficherPage("00000001");
    cout << "Taille du fichier Bdd : " << tailleFichier(fichierBDD()) << endl;
    cout << "Taille du fichier R_Pages : " << tailleFichier(fichierRPages()) << endl << endl;
    
    
    cout << "Création d'un deuxième enregistrement pour R1." << endl;
    creerEnregistrement(IDRelation1, nbMaxNuplet1, nuplet2);
    cout << "Nombre de pages : " << chargerPages().size() << endl;
    afficherPage("00000001");
    cout << "Taille du fichier Bdd : " << tailleFichier(fichierBDD()) << endl;
    cout << "Taille du fichier R_Pages : " << tailleFichier(fichierRPages()) << endl << endl;
    
    
    cout << "Allocation d'une page pour R2 avec un premier enregistrement." << endl;
    allouerPages(IDRelation2, nbMaxNuplet2, nuplet2);
    cout << "Nombre de pages : " << chargerPages().size() << endl;
    cout << "Taille du fichier Bdd : " << tailleFichier(fichierBDD()) << endl;
    cout << "Taille du fichier R_Pages : " << tailleFichier(fichierRPages()) << endl << endl;
    
    
    cout << "Création d'un troisième enregistrement alors que nbMaxNuplet = 2" << endl;
    creerEnregistrement(IDRelation1, nbMaxNuplet1, nuplet3);
    cout << "Nombre de pages : " << chargerPages().size() << endl;
    cout << "Taille du fichier Bdd : " << tailleFichier(fichierBDD()) << endl;
    cout << "Taille du fichier R_Pages : " << tailleFichier(fichierRPages()) << endl << endl;
    
    
    cout << "Désallocation d'une page de R1" << endl;
    desallouerPage("00000001");
    cout << "Nombre de pages : " << chargerPages().size() << endl;
    cout << "Taille du fichier Bdd : " << tailleFichier(fichierBDD()) << endl;
    cout << "Taille du fichier R_Pages : " << tailleFichier(fichierRPages()) << endl << endl;
    
    
    cout << "Suppression des nuplets de R2 dont le champ 2 est égal à 'FGFGFGFGFGFGFGFGFGFGFGFGF'" << endl;
    deleteNupletByChamp(IDRelation2, 2, asciiToBin("FGFGFGFGFGFGFGFGFGFGFGFGF"));
    cout << "Nombre de pages : " << chargerPages().size() << endl;
    cout << "Taille du fichier Bdd : " << tailleFichier(fichierBDD()) << endl;
    cout << "Taille du fichier R_Pages : " << tailleFichier(fichierRPages()) << endl << endl;

}