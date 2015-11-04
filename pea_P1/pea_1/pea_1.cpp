// pea_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Macierz.h"
#include "Funkcje.h"

int main()
{	
	Macierz macierz;
	//macierz.wypisz_macierz();
	cout << "\nWyœwietliæ miasta po wy¿arzaniu? Y/N \n>";
	string abcd;
	cin >> abcd;
	if(abcd == "Y" || abcd == "y")
		macierz.wyswietl();
	macierz.~Macierz();
	//zarzadzaj();

	cin.ignore();
	cin.get();
	return 0;
}

