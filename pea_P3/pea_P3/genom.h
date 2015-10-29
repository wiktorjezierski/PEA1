#pragma once
#include <vector>
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
};

