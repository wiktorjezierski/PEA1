#include "macierz.h"
#include <vector>
#include <algorithm>

using namespace std;

//trasa reprezentuje kolejnosc odwiedzanych miast, kazda zawiera wektor oraz dlugosc trasy
class Trasa
{
public:
	vector<int> trasa;
	int dlugosc_trasy;

	Trasa(){}


	Trasa(Macierz &M)
	{
		for(int i=0;i<M.ilosc_miast;i++)
		{
			trasa.push_back(M.trasa[i]);
		}
		dlugosc_trasy = M.policz_droge();
	}


	//konstruktor kopiujacy
	Trasa(Trasa const &T)
	{
		for(unsigned int i=0; i<T.trasa.size(); i++)
		{
			trasa.push_back(T.trasa[i]);
		}
		dlugosc_trasy = T.dlugosc_trasy;
	}


	//wyswietla kolejnosc odwiedzania miast
	void wyswietl_trase()
	{
		cout<<endl<<"TRASA: "<<endl;
		for(unsigned int i=0; i<trasa.size();i++)
		{
			cout<<trasa[i]<<" ";
		}
		cout<<endl;
	}

	//operator przypisania
	void operator=(Trasa &T)
	{
		trasa = T.trasa;
		dlugosc_trasy = T.dlugosc_trasy;
		
	}

	//zamienia 2 wartosci miejscami
	void swap(int i, int j)
	{
		int temp = trasa[i];
		trasa[i] = trasa[j];
		trasa[j] = temp;

	}
	//odwraca kolejnosc elementow od i do j, np. 1 2 3 4 5 -> 4 3 2 1 5
	void invert(int i, int j)
	{
		while(i!=j && i!=--j)
		{
			swap(i,j);
			++i;
		}
	}
	
	//zwraca dlugosc na podstawie otrzymanej macierzy
	int policz_droge(int **tab)
	{
		int ilosc_miast = trasa.size();
		int wynik = 0;

		int pocz;
		int kon;

		for (int i = 0; i < ilosc_miast - 1; i++)
		{
			pocz = trasa[i];
			kon = trasa[i + 1];
			wynik = wynik + tab[pocz][kon];
			if (i == ilosc_miast - 2)
			{
				pocz = trasa[ilosc_miast - 1];
				kon = trasa[0];

				wynik = wynik + tab[pocz][kon];
			}

		}
		dlugosc_trasy = wynik;
		return wynik;
	}

	//funkcja miesza kolejnoœæ odwiedzania
	void mieszaj(int **tab)
	{
		random_shuffle(trasa.begin(),trasa.end());
		policz_droge(tab);
	}

	//operator porownania
	bool operator==(const Trasa& droga) const
{
	if (equal(trasa.begin(), trasa.end(), droga.trasa.begin())) return true;
	return false;
}
};