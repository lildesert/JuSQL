#include "test.h"

using namespace std;

void tester() {
    // On réinitialise les fichiers
    viderFichier(fichierBDD());
    viderFichier(fichierRPages());
    
    string nuplet("10101010101010101001");
    allouerPages("10101010", 15, nuplet);
}