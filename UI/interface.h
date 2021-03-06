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

void InterfaceCreateSchema();

void CreateSchema();

void PrintSchema();

int MenuRequete();

void AjoutNuplet();

void EffacerNuplet();

void AfficherPagesByRelation();

void Retour();

void SelectWithPredicat();

void ProjectionWithoutOneAtt();

#endif	/* INTERFACE_H */

