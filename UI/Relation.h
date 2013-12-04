#ifndef RELATION_H
#define	RELATION_H

#include <cstdlib>
#include <string>
#include <vector>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>

#include "Attribut.h"

class Relation
{
public:
	Relation();
	Relation(string nomR);
	~Relation(void);
	static int idIncrementRelation;
	void addAttribut(Attribut a);
private:
	int idRelation;
	string nomRelation;
	vector<Attribut> listAttribut;

	friend class boost::serialization::access;
        
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
		ar & idRelation;
		ar & nomRelation;
		ar & listAttribut;
    }
};

#endif	/* RELATION_H */