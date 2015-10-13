// pea_lab_1.cpp : Defines the entry point for the console application.
//autor Kacper Przezak 200616

#include "stdafx.h"
#include "Plecak.h"


int _tmain(int argc, _TCHAR* argv[])
{
	
	cout << "Program wykonuje algorytm branch and bound dla problemu plecakowego\n\n";
	Plecak*plecak= new Plecak();
	plecak->zarzadzaj();
	plecak->~Plecak();


	

	

	system("pause");
	return 0;
}

