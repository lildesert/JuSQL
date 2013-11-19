#include "schema.h"

using namespace std;

int Schema::idIncrementSchema = 0;

Schema::Schema(void)
{
}

Schema::Schema(string nom)
{
	nomSchema = nom;
	idSchema = idIncrementSchema++;
}

Schema::~Schema(void)
{
}

void Schema::addRelation(Relation r)
{
	(this->listRelation).push_back(r);
}
