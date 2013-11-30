#ifndef SCHEMA_H
#define	SCHEMA_H

#include <cstdlib>
#include <string>
#include <vector>
#include "Relation.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class Schema
{
public:
	void addRelation(Relation r);
	static int idIncrementSchema;
	void setNom(string nom);
	void setId(int id);

	static Schema& GetInstance()
	{
		static Schema s;
		return s;
	}

private:
	Schema() {};
	Schema(const Schema&);
    Schema& operator=(const Schema&); 
	int idSchema;
	string nomSchema;
	vector<Relation> listRelation;
};
#endif	/* SCHEMA_H */