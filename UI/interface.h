#ifndef INTERFACE_H
#define	INTERFACE_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "common.h"
#include "schema.h"

int MenuPrincipal();

int MenuSchema();

void CreateSchema();

void PrintSchema();

int MenuSQL();

void AjoutNuplet();

void EffacerNuplet();

#endif	/* INTERFACE_H */

