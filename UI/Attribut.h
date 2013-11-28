#ifndef ATTRIBUT_H
#define	ATTRIBUT_H

#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

class Attribut
{
public:
	Attribut(string nomA, string typeA, string tailleA);
	~Attribut(void);
	static int idIncrementAttribut;
private:
	int idAttribut;
	string nomAttribut;
	string typeAttribut;
	string tailleAttribut;
};

#endif	/* ATTRIBUT_H */