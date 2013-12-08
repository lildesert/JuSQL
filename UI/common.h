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

void PortableSleep(int sec);

void saveIdIncrement(vector<int> idInc);

vector<int> loadIdIncrement();

string PathUnixWin(string path);

#endif	/* COMMON_H */