#ifndef COMMON_H
#define	COMMON_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int MenuCommon(string titre, vector<string> menuLn);

void PrintLn(string txt);

void ClearScreen();

#endif	/* COMMON_H */