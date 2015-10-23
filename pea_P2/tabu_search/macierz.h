#pragma once
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

class Macierz
{
public:

	int **macierz;
	vector<int> trasa;

	int ilosc_miast;
	int ile;

	void doPliku()
	{
		fstream plik;
		plik.open("2.txt", ios::out);

		for (int i = 0; i < ile; i++)
		{
			for (int j = 0; j < ile; j++)
			{
				plik << macierz[i][j]<<" ";
			}

			plik << endl;
		}
		
	}

	//tworzymy losowa macierz o podanym rozmiarze
	Macierz(int ile)
	{
		this -> ile = ile;
		ilosc_miast = ile;
		macierz = new int *[ile];

		for(int i=0; i<ilosc_miast; i++)
		{
			macierz[i] = new int[ile];
		}

		int losowa;
		for (int i = 0; i < ile; i++)
		{
			for (int j = 0; j < ile; j++)
			{
				if (i == j)
				{
					macierz[i][j] = 0;
				}
				else
				{
					do
					{
						losowa = rand() % 50;
					} while(losowa == 0);
					macierz[i][j] = losowa;

				}
			}
		}
		losuj_kolejnosc_miast();
		//wyswietl();
		//doPliku();
	}

	Macierz(string nazwa_pliku)
	{
		/*vector<string> wektor_odczytu;
		vector<int> wektor_odczytu_liczb;
		string linia;
		fstream plik;

		plik.open(nazwa_pliku, ios::in);
		if (!plik.good())
		{
			cout << "niepoprawny odczyt pliku wejsciowego\n";
		}
		else if (plik.good())
		{
			cout << "Poprawny odczyt pliku wejsciowego\n";
		
			while (!plik.eof())
			{
				getline(plik, linia);
				wektor_odczytu.push_back(linia);
				
			}
			for each (string linia in wektor_odczytu)
			{
				stringstream strumien(linia);
				do
				{
					string sub;
					strumien >> sub;
					if (atoi(sub.c_str()))
					{
						
						wektor_odczytu_liczb.push_back(atoi(sub.c_str()));
						
					}
					else if (sub == "0")
					{
						wektor_odczytu_liczb.push_back(0);
					}



				} while (strumien);
			}
			cout << "\nilosc miast\t" << wektor_odczytu_liczb[0]<<endl;

			ilosc_miast = wektor_odczytu_liczb[0];

		macierz = new int *[ilosc_miast];

		for(int i=0; i<ilosc_miast; i++)
		{
			macierz[i] = new int[ilosc_miast];
		}

			wektor_odczytu_liczb.erase(wektor_odczytu_liczb.begin());
			if (wektor_odczytu_liczb.size()!=pow(ilosc_miast,2))
			{
				cout << "\nNie wczytano wszystkich wartosci z pliku\nprogram zakonczy swoje dzialanie\n";

			}
			else
			{
				int i = 0;
				int j = 0;
				for each  (int pom  in wektor_odczytu_liczb)
				{

					macierz[j][i%ilosc_miast] = pom;

					if (i%ilosc_miast == (ilosc_miast - 1))
					{
						j++;
					}
					i++;
				}
			}

		}
		losuj_kolejnosc_miast();*/
		wczytajPlik(nazwa_pliku);
		//wyswietl();
	}

	void wczytajPlik(string nazwa)
	{
		fstream plik;
		plik.open(nazwa+".txt", ios::in);
		if (!plik.good())
		{
			cout << "niepoprawnie wczytany plik\n";
		}else if (plik.good())
		{
			string tekst;

			getline(plik, tekst, '\n');
			stringstream konwersja;
			konwersja.clear();
			konwersja << tekst;
			konwersja >> ilosc_miast;

			macierz = new int *[ilosc_miast];

			for (int i = 0; i < ilosc_miast; i++)
			{
				macierz[i] = new int[ilosc_miast];
			}

			//dodac wczytywanie z pliku konwersje i wrzucenie do tablicy

			for (int i = 0; i < ilosc_miast; i++)
			{
				for (int j = 0; j < ilosc_miast - 1; j++)
				{
					string tekst1;
					getline(plik, tekst1, ' ');
					stringstream konwersja;
					konwersja.clear();
					konwersja << tekst1;
					konwersja >> macierz[i][j];
				}

				string tekst2;
				getline(plik, tekst2, '\n');
				stringstream konwersja;
				konwersja.clear();
				konwersja << tekst2;
				konwersja >> macierz[i][ilosc_miast - 1];
			}

			losuj_kolejnosc_miast();
		}
	}

	void wyswietl()
	{
		for (int i = 0; i < ilosc_miast; i++)
		{
			for (int j = 0; j < ilosc_miast; j++)
			{
				cout << macierz[i][j] << " ";
			}
			cout << endl;
		}
	}
	//losuje pocz¹tkow¹ trasê
	void losuj_kolejnosc_miast()
	{
		int numer_zamienianego_miasta;
		//wypisujemy wszystkie miasta
		for (int i = 0; i < ilosc_miast; i++)
		{
			trasa.push_back(i);
		}
		//kazde miasto zamieniamy z losowo wybranym
		for (int i = 0; i < ilosc_miast; i++)
		{
			numer_zamienianego_miasta = rand() % ilosc_miast;
			swap(trasa[i], trasa[numer_zamienianego_miasta]);
		}
		/*for (int i = 0; i < ilosc_miast; i++)
		{
		cerr << "\n" << miasta[i];
		}*/
	}

	//zwraca d³ugoœæ aktualnej drogi
	int policz_droge()
	{
		int wynik = 0;

		int pocz;
		int kon;

		for (int i = 0; i < ilosc_miast - 1; i++)
		{
			pocz = trasa[i];
			kon = trasa[i + 1];
			wynik = wynik + macierz[pocz][kon];
			if (i == ilosc_miast - 2)
			{
				pocz = trasa[ilosc_miast - 1];
				kon = trasa[0];

				wynik = wynik + macierz[pocz][kon];
			}

		}

		return wynik;
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
		while(i!=j)
		{
			swap(i,j);
			i++;
			j--;
		}
	}

	//funkcja miesza kolejnoœæ odwiedzania
	void mieszaj()
	{
		random_shuffle(&trasa[0],&trasa[ilosc_miast]);
	}

	void operator =(const Macierz &M)
	{
		macierz = M.macierz;
		ilosc_miast = M.ilosc_miast;
		trasa = M.trasa;
	}


	//wyswietla kolejnosc odwiedzania miast
	void wyswietl_trase()
	{
		cout<<endl<<"TRASA: "<<endl;
		for(int i=0; i<ilosc_miast;i++)
		{
			cout<<trasa[i]<<" ";
		}
		cout<<endl;
	}

	//wyœwietla macierz d³ugoœci po³¹czeñ
	void wyswietl_macierz()
	{
		for (int i = 0; i < ilosc_miast; i++)
		{
			for (int j = 0; j < ilosc_miast; j++)
			{
				cout << "\t" << macierz[i][j];
			}
			cout << "\n";
		}
	}
};