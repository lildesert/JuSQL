#ifndef SCHEMA_H
#define	SCHEMA_H

#include <cstdlib>
#include <string>
#include <vector>
#include "Relation.h"

class Schema
{
public:
	Schema(void);
	~Schema(void);
	Schema(string nom);
	void addRelation(Relation r);
	static int idIncrementSchema;
private:
	int idSchema;
	string nomSchema;
	vector<Relation> listRelation;
};

#endif	/* SCHEMA_H */