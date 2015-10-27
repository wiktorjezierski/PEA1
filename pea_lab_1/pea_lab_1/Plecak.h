#pragma once
#include "stdafx.h"
#include <algorithm>
#include <stdio.h>
#include <time.h>
#include <ctime>
#include <queue>
#include <functional>
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
		//wartosc i rozmiar sa rzutowane na double po to aby wynik dzielenia posiada� czesc ulamkowa
		this->wartosc_do_rozmiaru = (double)(wartosc) / (double)(rozmiar);
	}
};
struct Wezel
{
	 int poziom;
	 int indeks;
	 int ograniczenie;	
	 int waga;
	 int wartosc;
	Wezel *przodek;
	Wezel *lewy_potomek;
	Wezel *prawy_potomek;
	Wezel()	{}
};
bool porownaj(Przedmiot pierwszy, Przedmiot drugi)
{
	if (pierwszy.wartosc_do_rozmiaru > drugi.wartosc_do_rozmiaru)
	{
		return true;
	}
	else
	{
		return false;
	}
}

class priority_queue_my
{
public:
	vector<Wezel*> wezly;

	void push(Wezel* element)
	{
		bool test = false;
		if (size() == 0)
		{
			wezly.push_back(element);
		}
		else
		{
			for (int i = 0; i < size(); i++)	//albo ta petla albo sortuj
			{
				if (wezly[i]->ograniczenie < element->ograniczenie)
				{
					volatile int pozycja;
					if (i > 0)
						pozycja = i - 1;
					else
						pozycja = 0;

					wezly.insert(wezly.begin() + pozycja, element);
					test = true;
					break;
				}
			}

			if (test == false)
				wezly.push_back(element);
		}		
	}

	int size()
	{
		return wezly.size();
	}

	Wezel* front()
	{
		return wezly[0];
	}

	void pop()
	{
		wezly.erase(wezly.begin());
	}

	bool isEmpty()
	{
		if (wezly.size() == 0)
			return true;
		else
			return false;
		return true;
	}

};

class Plecak
{
	Wezel *najlepszy;
	queue<Wezel*>kolejka_wezlow;			// do branch and bound
	priority_queue_my kolejka_priorytetowa;	//do best first
	vector<Przedmiot> aktualnie_best;		//do przegladu zupelnego

	int pojemnosc;
	int ilosc_elementow;
	
	vector<Przedmiot> wektor_przedmiotow;
	vector<int>wektor_liczb;

public:
	Plecak()
	{}
	~Plecak()
	{
		wektor_przedmiotow.erase(wektor_przedmiotow.begin(), wektor_przedmiotow.end());
		wektor_liczb.erase(wektor_liczb.begin(), wektor_liczb.end());
		remove("generowany.txt");
	}
	
	void set_pojemnosc(int pojemnosc)
	{
		this->pojemnosc = pojemnosc;
	}

	int ograniczenie(int poziom, int waga_chwilowa, int wartosc_chwilowa)
	{		    
			for (int i = poziom; i < wektor_przedmiotow.size() ;i++)
			{
			    
				if (waga_chwilowa + wektor_przedmiotow[i].rozmiar < pojemnosc)
				{
					waga_chwilowa = waga_chwilowa + wektor_przedmiotow[i].rozmiar;
					wartosc_chwilowa = wartosc_chwilowa + wektor_przedmiotow[i].wartosc;
				}
				else
				{
					double roznica = pojemnosc - waga_chwilowa;
				
					wartosc_chwilowa = wartosc_chwilowa + roznica /wektor_przedmiotow[i].rozmiar*wektor_przedmiotow[i].wartosc;
					break;
				}
			}
			
			return wartosc_chwilowa;
	}

	void branch_and_bound()
	{		
		Wezel nie_ustawiony;
		najlepszy = NULL;
		Wezel *lewy;
		Wezel *prawy;
		for (int i = 0; i < wektor_przedmiotow.size(); i++)
		{			
			if (i==0)
			{
				Wezel *wezel=new Wezel();
				wezel->przodek = NULL;
				wezel->lewy_potomek = &nie_ustawiony;
				wezel->prawy_potomek = &nie_ustawiony;
				wezel->poziom = i;
				wezel->ograniczenie = ograniczenie(0, 0, 0);
				wezel->waga = 0;
				wezel->wartosc = 0;
				kolejka_wezlow.push(wezel);
				najlepszy = wezel;
				
			}
			volatile int pomocnicza = kolejka_wezlow.size();
			//cout << "\n" << pomocnicza;
			for (int j = 0; j < pomocnicza; j++)
			{
				Wezel *pom = kolejka_wezlow.front();
				//usuniecie elementu z pocz�tku kolejki
				kolejka_wezlow.pop();
				//ustawianie lewego potomka
				if (pom->lewy_potomek == &nie_ustawiony)
				{
					lewy=new Wezel();
					pom->lewy_potomek = lewy;
					lewy->przodek = pom;
					lewy->wartosc = pom->wartosc + wektor_przedmiotow[i].wartosc;
					lewy->waga = pom->waga + wektor_przedmiotow[i].rozmiar;
					lewy->poziom = pom->poziom + 1;
					lewy->indeks = 1;
					if (lewy->waga > pojemnosc)
					{
						lewy->ograniczenie = 0;
						//gdy weze� jest nieobiecuj�cy 
						lewy->lewy_potomek = NULL;
						lewy->prawy_potomek = NULL;
					}
					else
					{
						lewy->ograniczenie = ograniczenie(lewy->poziom, lewy->waga, lewy->wartosc);
						if (lewy->ograniczenie < najlepszy->wartosc) //ograniczenie = wartosc chwilowa // nieobiecujacy
						{
							lewy->lewy_potomek = NULL;
							lewy->prawy_potomek = NULL;
						}	
						else										//obiecujacy
						{
							lewy->lewy_potomek = &nie_ustawiony;
							lewy->prawy_potomek = &nie_ustawiony;
						}						
						if (lewy->wartosc > najlepszy->wartosc)
						{
							najlepszy = lewy;
						}						
					}
					kolejka_wezlow.push(lewy);				
				}
				if (pom->prawy_potomek==&nie_ustawiony)
				{
					prawy = new Wezel();
					pom->prawy_potomek = prawy;
					prawy->przodek = pom;
					prawy->wartosc = pom->wartosc;
					prawy->waga = pom->waga;
					prawy->poziom = pom->poziom + 1;
					prawy->indeks = 0;

					if (prawy->waga > pojemnosc)
					{
						prawy->ograniczenie = 0;
						//gdy weze� jest nieobiecuj�cy 
						prawy->lewy_potomek = NULL;
						prawy->prawy_potomek = NULL;
					}
					else
					{
						prawy->ograniczenie = ograniczenie(prawy->poziom, prawy->waga, prawy->wartosc);						

						if (prawy->ograniczenie < najlepszy->wartosc)
						{
							prawy->lewy_potomek =NULL;
							prawy->prawy_potomek =NULL;
						}
						else
						{
							prawy->lewy_potomek = &nie_ustawiony;
							prawy->prawy_potomek = &nie_ustawiony;
						}
						if (prawy->wartosc > najlepszy->wartosc)
						{
							najlepszy = prawy;
						}
					}

					kolejka_wezlow.push(prawy);
				}
			}				
		}
	}

	void best_first()
	{
		Wezel nie_ustawiony;
		najlepszy = NULL;
		Wezel *lewy;
		Wezel *prawy;
		//for (int i = 0; i < wektor_przedmiotow.size(); i++)
		//{					
				Wezel *wezel = new Wezel();			//warunki poczatkowe
				wezel->przodek = NULL;
				wezel->lewy_potomek = &nie_ustawiony;
				wezel->prawy_potomek = &nie_ustawiony;
				wezel->poziom = 0;
				wezel->ograniczenie = ograniczenie(0, 0, 0);
				wezel->waga = 0;
				wezel->wartosc = 0;
				kolejka_priorytetowa.wezly.push_back(wezel);
				najlepszy = wezel;
		
			volatile int pomocnicza = wektor_przedmiotow.size();
			
			for (int j = 0; j < pomocnicza; j++)
			//while(kolejka_priorytetowa.size() > 0)
			{
				Wezel *pom = kolejka_priorytetowa.front();
				//usuniecie elementu z pocz�tku kolejki
				kolejka_priorytetowa.pop();
				//ustawianie lewego potomka
				if (pom->lewy_potomek == &nie_ustawiony)
				{
					lewy = new Wezel();
					pom->lewy_potomek = lewy;
					lewy->przodek = pom;
					lewy->wartosc = pom->wartosc + wektor_przedmiotow[pom->poziom].wartosc;
					lewy->waga = pom->waga + wektor_przedmiotow[pom->poziom].rozmiar;
					lewy->poziom = pom->poziom + 1;
					lewy->indeks = 1;
					if (lewy->waga > pojemnosc)
					{
						lewy->ograniczenie = 0;
						//gdy weze� jest nieobiecuj�cy 
						lewy->lewy_potomek = NULL;
						lewy->prawy_potomek = NULL;
					}
					else
					{
						lewy->ograniczenie = ograniczenie(lewy->poziom, lewy->waga, lewy->wartosc);
						if (lewy->ograniczenie < najlepszy->wartosc) 
						{
							lewy->lewy_potomek = NULL;
							lewy->prawy_potomek = NULL;
						}
						else										//obiecujacy
						{
							lewy->lewy_potomek = &nie_ustawiony;
							lewy->prawy_potomek = &nie_ustawiony;
						}
						if (lewy->wartosc > najlepszy->wartosc)
						{
							najlepszy = lewy;
						}
					}
					kolejka_priorytetowa.push(lewy);
				}
				if (pom->prawy_potomek == &nie_ustawiony)
				{
					prawy = new Wezel();
					pom->prawy_potomek = prawy;
					prawy->przodek = pom;
					prawy->wartosc = pom->wartosc;
					prawy->waga = pom->waga;
					prawy->poziom = pom->poziom + 1;
					prawy->indeks = 0;

					if (prawy->waga > pojemnosc)
					{
						prawy->ograniczenie = 0;
						//gdy weze� jest nieobiecuj�cy 
						prawy->lewy_potomek = NULL;
						prawy->prawy_potomek = NULL;
					}
					else
					{
						prawy->ograniczenie = ograniczenie(prawy->poziom, prawy->waga, prawy->wartosc);

						if (prawy->ograniczenie < najlepszy->wartosc)
						{
							prawy->lewy_potomek = NULL;
							prawy->prawy_potomek = NULL;
						}
						else
						{
							prawy->lewy_potomek = &nie_ustawiony;
							prawy->prawy_potomek = &nie_ustawiony;
						}
						if (prawy->wartosc > najlepszy->wartosc)
						{
							najlepszy = prawy;
						}

					}
					kolejka_priorytetowa.push(prawy);
				}
			}
	}

	void przeglad_zupelny()
	{
		vector<int> skladowe;
		vector<Przedmiot> temp1;

		int kombinacje = pow(2, wektor_przedmiotow.size());
		int best_wartosc = 0;
		int liczba_dziesietna;

		for (int i = 0; i < kombinacje; i++)		//for po wszystkich kombinacjach
		{
			int aktualna_wartosc = 0;
			int aktualny_rozmiar = 0;
			skladowe.clear();
			temp1.clear();
			liczba_dziesietna = i;

			while (liczba_dziesietna > 0)		//rozklad na dwojkowe
			{
				skladowe.push_back(liczba_dziesietna % 2);
				liczba_dziesietna = liczba_dziesietna / 2;
			}

			for (int j = 0; j < skladowe.size(); j++)	//funkcja bioraca elementy tam gdzie jest 1
			{
				if (skladowe[j] == 1)
				{
					aktualny_rozmiar += wektor_przedmiotow[j].rozmiar;	
					aktualna_wartosc += wektor_przedmiotow[j].wartosc; 
					temp1.push_back(wektor_przedmiotow[j]);
				}
			}

			if (aktualny_rozmiar <= pojemnosc && aktualna_wartosc > best_wartosc)
			{
				best_wartosc = aktualna_wartosc;
				aktualnie_best.clear();
				for (int k = 0; k < temp1.size(); k++)
				{
					aktualnie_best.push_back(temp1[k]);	//przepisanie najlepszej kombinacji
				}
			}
		}

		wyswietl_przeglad_zupelny();
	}

	void wyswietl_wybrane_elementy()
	{
		Wezel *tymczasowy;
		tymczasowy = najlepszy;
		bool log = false;
		vector<Wezel*>wektor_wskaznikow;
		while (tymczasowy != NULL)
		{
			wektor_wskaznikow.push_back(tymczasowy);
			tymczasowy = tymczasowy->przodek;
		}
		Wezel*pom;
		cout << "!"<<endl;
		for (int i = wektor_wskaznikow.size() - 1; i > 0; i--)
		{
			pom = wektor_wskaznikow[i];
			if (wektor_wskaznikow[i - 1] == pom->lewy_potomek)
			{
				//cout << "\nnumer elementu: " << pom->poziom;
				cout << "\twartosc: " << wektor_przedmiotow[pom->poziom].wartosc;
				cout << "\trozmiar: " << wektor_przedmiotow[pom->poziom].rozmiar;
			}
		}
	}

	void wyswietl_przeglad_zupelny()
	{
		for each (Przedmiot item in aktualnie_best)
		{
			cout << "wartosc: " << item.wartosc << "\trozmiar " << item.rozmiar << endl;
		}
	}

	void zarzadzaj()	//tu wstawic menu damiana
	{
		int menu;
		cout << "\nwybor algorytmu\n 1 - branch and bound\n 2 - best first\n 3 - przeglad zupelny\n>";
		cin >> menu;
		
		if (menu == 1)
		{
			cout << "\nwybrales algorytm branch and bound\n";
			branch_and_bound();
		}
		else if (menu == 2)
		{
			cout << "\nwybrales algorytm best first\n";
			best_first();
		}
		else if (menu == 3)
		{
			przeglad_zupelny();
		}

		int wybor;
		cout << "\njesli chcesz wyswietlic elemety posortowane wedlug ilorazu wartosci do wagi nacisnij 1 \n>";
		cin >> wybor;
		if (wybor == 1)
		{
			for each (Przedmiot przedmiot in wektor_przedmiotow)
			{
				cout << "\nromiar: " << przedmiot.rozmiar << "\twartosc: " << przedmiot.wartosc;

				printf(" wartosc do rozmiaru %f", przedmiot.wartosc_do_rozmiaru);
			}
		}
		cout << "\nwartosc:\t" << najlepszy->wartosc << "\nwaga:\t" << najlepszy->waga << endl;
		cout << "\njesli chcesz wyswietlic elemety znajdujace sie w plecaku nacisnij 1 \n>";
		cin >> wybor;
		if (wybor == 1)
		{
			wyswietl_wybrane_elementy();
		}
	}

	void wczzytaj()
	{
		string nazwa_pliku;
		srand(time(NULL));
		clock_t start, koniec;
		int menu;

		cout << "jesli chcesz wczytac i wyswietlic dane z pliku nacisnij 1\njesli chcesz wygenerowac losowa instancje nacisnij 2\n>";
		cin >> menu;

		if (menu == 1)
		{
			cout << "\npodaj nazwe pliku z instancja testowa\n>";
			cin >> nazwa_pliku;
		}
		if (menu == 2)
		{
			ofstream plik_generuj;
			int pom_pojemnosc;
			int pom_ilosc_elementow;
			plik_generuj.open("generowany.txt");

			cout << "Podaj pojemnosc plecaka\n>";
			cin >> pom_pojemnosc;
			plik_generuj << pom_pojemnosc;
			pom_pojemnosc++;//wazne
			cout << "Podaj ilosc elementow\n>";
			cin >> pom_ilosc_elementow;
			plik_generuj << "\n" << pom_ilosc_elementow;
			
			for (int i = 0; i < pom_ilosc_elementow; i++)
			{
				plik_generuj << "\n" << rand() % (int)(pom_pojemnosc*0.5) + 1 << " " << rand() % (pom_pojemnosc + 1);
			}
			nazwa_pliku = "generowany";
			plik_generuj.close();

		}

		if (menu == 1 || menu == 2)
		{
			if (wczytaj_plik_testowy(nazwa_pliku + ".txt"))
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

					for each (Przedmiot p in wektor_przedmiotow)
					{
						cout << "rozmiar " << p.rozmiar << " wartosc " << p.wartosc << endl;
					}
				}
			}
			else
			{
				cout << "Niepoprawna ilosc wczytanych wartosci\nalgorytm nie wykona sie :(\n";
			}
			//sortowanie wektora zawierajacego przedmioty funkcja sort z STL, 
			sort(wektor_przedmiotow.begin(), wektor_przedmiotow.end(), porownaj);
		}
	}

	bool wczytaj_plik_testowy(string nazwa_pliku)
	{
		vector<string> wektor_odczytu;
		fstream plik;
		plik.open(nazwa_pliku, ios::in);
		if (plik.good())
		{
			//wczytanie ca�ego pliku, ka�da linia jest oddzielnym elementem wektora_odczytu
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

};