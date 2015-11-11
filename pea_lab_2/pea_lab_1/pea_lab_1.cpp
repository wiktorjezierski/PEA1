// pea_lab_1.cpp : Defines the entry point for the console application.


#include "stdafx.h"
#include "Plecak.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "Program wykonuje algorytm programowania dynamicznego dla decyzyjnego  problemu plecakowego\n\n";

	Plecak*plecak= new Plecak();
	
	plecak->zarzadzaj();
	delete plecak;
	
	cin.ignore();
	cin.get();
	return 0;
}

