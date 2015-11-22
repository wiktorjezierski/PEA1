#pragma once
#include <vector>
#include <iostream>
class genom
{
public:
	genom();
	~genom();

	vector<int*> droga;
	int dlugosc_drogi;

	void dodaj(int skad, int dokad, int wartosc);
	void wyswietl();
	bool zawiera_raz(int miasto);
	bool nie_zawiera(int miasto);

	static void mutacja(genom &g1, genom &g2, int begin, int end);
};

