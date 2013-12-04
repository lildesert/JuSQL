#ifndef ATTRIBUT_H
#define	ATTRIBUT_H

#include <cstdlib>
#include <string>
#include <vector>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

using namespace std;

class Attribut
{
public:
	Attribut(string nomA, string typeA, string tailleA);
	~Attribut(void);
	Attribut();
	static int idIncrementAttribut;
private:
	int idAttribut;
	string nomAttribut;
	string typeAttribut;
	string tailleAttribut;

	friend class boost::serialization::access;
        
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
		ar & idAttribut;
		ar & nomAttribut;
		ar & typeAttribut;
		ar & tailleAttribut;
    }
};

#endif	/* ATTRIBUT_H */