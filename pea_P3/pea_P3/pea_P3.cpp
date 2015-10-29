// pea_P3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DNA.h"
#include "genom.h"

int main()
{
	DNA dna;
	cout << "start\n";
	dna.wczytaj("k2");
	dna.zarzadzaj();
	cout << "\nstop";
	cin.ignore();
	cin.get();
    return 0;
}

