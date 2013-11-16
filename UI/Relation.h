#ifndef RELATION_H
#define	RELATION_H

#include <cstdlib>
#include <string>
#include <vector>
#include "Attribut.h"

class Relation
{
public:
	Relation(void);
	~Relation(void);
private:
	int idRelation;
	string nomRelation;
	vector<Attribut> listAttribut;
};

#endif	/* RELATION_H */