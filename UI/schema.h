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
private:
	int idSchema;
	string nomSchema;
	vector<Relation> listRelation;
};

#endif	/* SCHEMA_H */