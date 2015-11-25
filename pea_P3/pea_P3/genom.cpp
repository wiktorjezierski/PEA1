#include "stdafx.h"
#include "genom.h"


genom::genom()
{
	dlugosc_drogi = 0;
}


genom::~genom()
{
}

void genom::dodaj(int skad, int dokad, int wartosc)
{
	int * tab = new int[3];
	tab[0] = skad;
	tab[1] = dokad;
	tab[2] = wartosc;

	droga.push_back(tab);
	dlugosc_drogi += wartosc;
}
//funkcja do sprawdzenia poprawnosci
void genom::wyswietl()
{
	for (int i = 0; i < droga.size(); i++)
	{
		cout << droga[i][0] << " " << droga[i][1] << " " << droga[i][2] << "\n";
	}
}

bool genom::zawiera_raz(int miasto)
{
	int temp = 0;

	for (int i = 0; i < droga.size(); i++)
	{
		if (temp > 1)
			return false;

		if (droga[i][0] == miasto)
			temp++;
		if (droga[i][1] == miasto)
			temp++;
	}
	
	if (temp == 1)
		return true;
	else
		return false;
}

bool genom::nie_zawiera(int miasto)
{
	for (int i = 0; i < droga.size(); i++)
	{
		if (droga[i][0] == miasto || droga[i][1] == miasto)
			return false;
	}
		return true;
}

//void genom::mutacja(genom g1, genom g2, int begin, int end)
//{
//	vector<int*> temp;
//
//	for (int i = begin; i <= end; i++)
//	{
//		temp.push_back(g1.droga[i]);
//		g1.droga.erase(g1.droga.begin() + i);
//		g1.droga.insert(g1.droga.begin + i,g2.droga[i]);
//
//		g2.droga.erase(g2.droga.begin() + i);
//		g2.droga.insert(g2.droga.begin + i, temp[i]);
//	}
//}




