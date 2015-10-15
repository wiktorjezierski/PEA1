# pragma once
#include "stdafx.h"
#include <algorithm>
#include <stdio.h>
#include <time.h>
#include <ctime>
#include <chrono>

using namespace std;


struct Przedmiot
{
	int rozmiar;
	int wartosc;
	double wartosc_do_rozmiaru;
	Przedmiot(int parametr_rozmiar, int parametr_wartosc)
	{
		this->rozmiar = parametr_rozmiar;
		this->wartosc = parametr_wartosc;
		//wartosc i rozmiar sa rzutowane na double po to aby wynik dzielenia posiada³ czesc ulamkowa
		this->wartosc_do_rozmiaru = (double)(wartosc) / (double)(rozmiar);

	}
};
class Plecak
{
	
	int pojemnosc;
	int ilosc_elementow;
	vector<Przedmiot> wektor_przedmiotow;
	vector<int>wektor_liczb;
	int **tablica_wartosci=NULL;

public:
	Plecak()
	{
		string nazwa_pliku;	    
		int menu;

		cout << "jesli chcesz wczytac dane z pliku nacisnij 1\njesli chcesz wygenerowac losowa instancje nacisnij 2\n";
		cin >> menu;
		
		if (menu == 1)
		{
			cout << "\npodaj nazwe pliku z instancja testowa\n";
			cin >> nazwa_pliku;
		}
		if (menu == 2)
		{
			ofstream plik_generuj;
			int pom_pojemnosc;
			int pom_ilosc_elementow;
			plik_generuj.open("generowany.txt");
			cout << "Podaj pojemnosc plecaka\n";
			cin >> pom_pojemnosc;
			plik_generuj << "\n" << pom_pojemnosc;
			cout << "Podaj ilosc elementow\n";
			cin >> pom_ilosc_elementow;
			plik_generuj << "\n" << pom_ilosc_elementow;

			for (int i = 0; i < pom_ilosc_elementow; i++)
			{
				
					plik_generuj << "\n" << rand() %(int) (pom_pojemnosc*0.5) + 1 << "\t" << rand() % pom_pojemnosc + 1;
			}
			nazwa_pliku = "generowany.txt";
			plik_generuj.close();			
			
		}

			if (menu == 1 || menu == 2)
			{
			if (wczytaj_plik_testowy(nazwa_pliku))
			{
				//pobranie pojemnosci plecaka, oraz usuniecie tej danej z wektora
				pojemnosc = wektor_liczb.front();
				//usuniecie pierwszego elementu wektora
				wektor_liczb.erase(wektor_liczb.begin());
				//pobranie ilosci elementow, oraz usuniecie tej danej z wektora
				ilosc_elementow = wektor_liczb.front();
				//usuniecie pierwszego elementu wektora
				wektor_liczb.erase(wektor_liczb.begin());
				cout << "Problem plecakowy\nzlodziej ma do dyspozycji\t" << ilosc_elementow << " elementow\n" << "pojemnosc plecaka wynosi\t" << pojemnosc << "\n";
				if (wektor_liczb.size() == 2 * ilosc_elementow)
				{
					//stworzenie wektora zawierajacego elementy plecaka
					for (int i = 0; i < wektor_liczb.size(); i = i + 2)
					{
						wektor_przedmiotow.push_back(Przedmiot(wektor_liczb[i], wektor_liczb[i + 1]));
					}

					tablica_wartosci = new  int*[ilosc_elementow+1];
					for (int i = 0; i < ilosc_elementow+1; i++)
					{
						tablica_wartosci[i] = new int[pojemnosc+1];
						
					}
					programowanie_dynamiczne();
				}
			}
			else
			{
				cout << "Niepoprawna ilosc wczytanych wartosci\nalgorytm nie wykona sie :(\n";
			}
												
		}		
		
		
	}
	Plecak(string nazwa_pliku)
	{
		if (wczytaj_plik_testowy(nazwa_pliku))
		{
			//pobranie pojemnosci plecaka, oraz usuniecie tej danej z wektora
			pojemnosc = wektor_liczb.front();
			//usuniecie pierwszego elementu wektora
			wektor_liczb.erase(wektor_liczb.begin());
			//pobranie ilosci elementow, oraz usuniecie tej danej z wektora
			ilosc_elementow = wektor_liczb.front();
			//usuniecie pierwszego elementu wektora
			wektor_liczb.erase(wektor_liczb.begin());
			cout << "Problem plecakowy\nzlodziej ma do dyspozycji\t" << ilosc_elementow << " elementow\n" << "pojemnosc plecaka wynosi\t" << pojemnosc << "\n";
			if (wektor_liczb.size() == 2 * ilosc_elementow)
			{
				//stworzenie wektora zawierajacego elementy plecaka
				for (int i = 0; i < wektor_liczb.size(); i = i + 2)
				{
					wektor_przedmiotow.push_back(Przedmiot(wektor_liczb[i], wektor_liczb[i + 1]));
				}

				tablica_wartosci = new  int*[ilosc_elementow + 1];
				for (int i = 0; i < ilosc_elementow + 1; i++)
				{
					tablica_wartosci[i] = new int[pojemnosc + 1];

				}
			programowanie_dynamiczne();
			}
		}
		else
		{
			cout << "Niepoprawna ilosc wczytanych wartosci\nalgorytm nie wykona sie :(\n";
		}
	}
	~Plecak()
	{
		wektor_przedmiotow.erase(wektor_przedmiotow.begin(), wektor_przedmiotow.end());
		wektor_liczb.erase(wektor_liczb.begin(), wektor_liczb.end());
		if (tablica_wartosci!=NULL)
		{

			for (int i = 0; i <= ilosc_elementow; i++)
			{
				delete[] tablica_wartosci[i];

			}
			delete[] tablica_wartosci;
		}
	}
	bool wczytaj_plik_testowy(string nazwa_pliku)
	{
		vector<string> wektor_odczytu;
		fstream plik;
		plik.open(nazwa_pliku, ios::in);
		if (plik.good())
		{
			//wczytanie ca³ego pliku, ka¿da linia jest oddzielnym elementem wektora_odczytu
			string linia;
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
						wektor_liczb.push_back(atoi(sub.c_str()));
					}

				} while (strumien);
			}
			return true;
		}
		else 
		{
			cout << "Niepoprawny odczyt pliku\n";
			return false;
		}

	}
	void  programowanie_dynamiczne()
	{
		//srand(time(NULL));
		//clock_t start, koniec;
		//start = clock();
		auto begin = std::chrono::high_resolution_clock::now();
		for (int i = 0; i <= ilosc_elementow;i++)
		{
			tablica_wartosci[i][0] = 0;
		}
		for (int i = 0; i <= pojemnosc; i++)
		{
			tablica_wartosci[0][i] = 0;
		}

		for (int i = 1; i <= ilosc_elementow;i++)
		{
			for (int j = 0; j <= pojemnosc; j++)
			{
				if (wektor_przedmiotow[i-1].rozmiar > j)
				{
					tablica_wartosci[i][j] = tablica_wartosci[i - 1][j];
				}
				else
				{
					tablica_wartosci[i][j] = max(tablica_wartosci[i - 1][j], wektor_przedmiotow[i-1].wartosc + tablica_wartosci[i - 1][j - wektor_przedmiotow[i-1].rozmiar]);
				}
			}
		}
		//koniec = clock();
		auto end = chrono::high_resolution_clock::now();
		cout << "\n"<<chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "ms" << endl;
		bool log = true;
		int wiersz = ilosc_elementow;
		int kolumna = pojemnosc;
		do
		{
			if (tablica_wartosci[wiersz][kolumna] == tablica_wartosci[wiersz-1][kolumna])
			{
				wiersz--;
			}
			else 
			{
				cout << "\n wartosc elementu\t" << wektor_przedmiotow[wiersz-1].wartosc << "\t rozmiar \t"<<wektor_przedmiotow[wiersz-1].rozmiar;
			
				kolumna = kolumna - wektor_przedmiotow[wiersz-1].rozmiar;
				wiersz--;
			}
			if (kolumna < 0 || wiersz == 0)
			{
				log = false;
			}

		} while (log);

		cout << "\n\nnajlepsze rozwiazanie\t" << tablica_wartosci[ilosc_elementow][pojemnosc];
		
		
	}	
	

	
};