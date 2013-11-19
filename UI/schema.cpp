#include "schema.h"

using namespace std;

Schema::Schema(void)
{
	idSchema = 0;
}

Schema::Schema(string nom)
{
	nomSchema = nom;
	idSchema = 0;
}

Schema::~Schema(void)
{
}

void Schema::addRelation(Relation r)
{
	(this->listRelation).push_back(r);
}
