#ifndef ATTRIBUT_H
#define	ATTRIBUT_H

#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

class Attribut
{
public:
	Attribut(void);
	~Attribut(void);
	static int idIncrementAttribut;
private:
	int idAttribut;
	string nomAttribut;
	string typeAttribut;
};

#endif	/* ATTRIBUT_H */