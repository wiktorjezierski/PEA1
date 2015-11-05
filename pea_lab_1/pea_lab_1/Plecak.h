#pragma once
#include "stdafx.h"
#include <algorithm>
#include <stdio.h>
#include <time.h>
#include <ctime>
#include <queue>
#include <functional>
#include <cstdlib>
using namespace std;


class Przedmiot
{
public: 
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

	static bool porownaj(Przedmiot pierwszy, Przedmiot drugi)
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
					wezly.insert(wezly.begin() + i, element);
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

	void wyswietl()
	{
		for (int i = 0; i < wezly.size(); i++)
		{
			cout << wezly[i]->ograniczenie << " ";
		}
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

public:
	Plecak()
	{}
	~Plecak()
	{
		wektor_przedmiotow.erase(wektor_przedmiotow.begin(), wektor_przedmiotow.end());
		remove("generowany.txt");
	}
	
	void set_pojemnosc(int pojemnosc)
	{
		this->pojemnosc = pojemnosc;
	}
	int get_pojemnosc()
	{
		return pojemnosc;
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
				//usuniecie elementu z pocz¹tku kolejki
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
						//gdy weze³ jest nieobiecuj¹cy 
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
						//gdy weze³ jest nieobiecuj¹cy 
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
				//usuniecie elementu z pocz¹tku kolejki
				kolejka_priorytetowa.pop();
				//ustawianie lewego potomka
				if (pom->lewy_potomek == &nie_ustawiony && pom->poziom >= 0 && pom->poziom < wektor_przedmiotow.size())
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
						//gdy weze³ jest nieobiecuj¹cy 
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
						//gdy weze³ jest nieobiecuj¹cy 
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

				/*kolejka_priorytetowa.wyswietl();
				cout << endl;*/
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
	}

	void wyswietl_wybrane_elementy()
	{
		Wezel *tymczasowy;
		tymczasowy = najlepszy;
		vector<Wezel*>wektor_wskaznikow;
		wektor_wskaznikow.clear();
		while (tymczasowy != NULL)
		{
			wektor_wskaznikow.push_back(tymczasowy);
			tymczasowy = tymczasowy->przodek;
		}
		Wezel*pom;
		for (int i = wektor_wskaznikow.size() - 1; i > 0; i--)
		{
			pom = wektor_wskaznikow[i];
				if (wektor_wskaznikow[i - 1] == pom->lewy_potomek)
				{
					cout << endl;
					pom->poziom;
					if (pom->poziom >= 0 && pom->poziom < wektor_przedmiotow.size())
					{
						cout << "wartosc: " << wektor_przedmiotow[pom->poziom].wartosc;
						cout << "\trozmiar: " << wektor_przedmiotow[pom->poziom].rozmiar;
					}
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
	
	void wyswietl_po_wczytaniu()
	{
		for each (Przedmiot item in wektor_przedmiotow)
		{
			cout << "rozmiar: " << item.rozmiar << " wartosc: " << item.wartosc << endl;
		}
	}

	void zarzadzaj()
	{
		int wybor = 666;
		int wybor2;
		bool czy_wczytano;
		string nazwaPliku;

		cout << "Podaj rozmiar plecaka: ";
		cin >> pojemnosc;
		system("cls");

		while (wybor != 0) {
			wybor2 = 666;
			cout << "\tMENU\n";
			cout << "Wybierz opcje:\n";
			cout << "-----------------------------\n";
			cout << "1. Wczytaj z pliku\n";
			cout << "2. Wygeneruj losowo\n";
			cout << "3. Zmien rozmiar plecaka\n";
			cout << "0. EXIT\n";
			cout << "-----------------------------\n\n";
			cin >> wybor;
			switch (wybor)
			{
			case 1:
				cout << "Podaj nazwe pliku:\n";
				cin >> nazwaPliku;
				czy_wczytano = wczytaj_z_pliku(nazwaPliku);
				cout << "\n";
				wyswietl_po_wczytaniu();
				//system("cls");
				break;
			case 2:
				cout << "Wygeneruj losowo()\nIle elementow wygenerowac?\n> ";
				int ile;
				cin >> ile;
				czy_wczytano = losowo(ile);
				cout << "\n";
				//system("cls");
				break;
			case 3:
				cout << "podaj nowy rozmiar plecaka: ";				
				cin >> pojemnosc;
				cout << "\n";
				//system("cls");
				break;
			default:
				break;
			}
			while (wybor2 != 0 && czy_wczytano == true) {
				cout << "\tWybierz algorytm:\n";
				cout << "-----------------------------\n";
				cout << "1. Branch and bound\n";
				cout << "2. Best First\n";
				cout << "3. Przeglad zupelny\n";
				cout << "0. BACK\n";
				cout << "-----------------------------\n\n";
				cin >> wybor2;
				switch (wybor2)
				{
				case 1:
					//system("cls");
					branch_and_bound();
					wyswietl_wybrane_elementy();
					cin.get();
					//system("cls");
					break;
				case 2:
					//system("cls");
					best_first();
					wyswietl_wybrane_elementy();
					cin.get();
					//system("cls");
					break;
				case 3:
					//system("cls");
					przeglad_zupelny();
					wyswietl_przeglad_zupelny();
					cin.get();
					//system("cls");
					break;
				case 0:
					//system("cls");
				default:
					break;
				}
			}
		}
	}

	bool wczytaj_z_pliku(string nazwa_pliku)
	{
		fstream plik;
		string tekst1;
		stringstream ss;

		plik.open(nazwa_pliku + ".txt", ios::in);

		if (plik.good())
		{
			wektor_przedmiotow.clear();
			stringstream konwersja;
			getline(plik, tekst1, '\n');
			konwersja.clear();
			konwersja << tekst1;
			konwersja >> ilosc_elementow;

			for (int i = 0; i < ilosc_elementow; i++)
			{
				int temp1, temp2;

				getline(plik, tekst1, ' ');			//wczytanie z pliku tekstu do znaku '/'
				konwersja.clear();
				konwersja << tekst1;
				konwersja >> temp1;						//przypisanie zmiennej w obiekcie wartosci				

				getline(plik, tekst1, '\n');			//wczytanie z pliku tekstu do znaku '/'
				konwersja.clear();
				konwersja << tekst1;
				konwersja >> temp2;						//przypisanie zmiennej w obiekcie wartosci			

				Przedmiot item(temp1, temp2);
				wektor_przedmiotow.push_back(item);
			}
			plik.close();
			sort(wektor_przedmiotow.begin(), wektor_przedmiotow.end(), Przedmiot::porownaj);
			return true;
		}
		else
		{
			cout << "blednda nazwa pliku\n";
			return false;
		}

	}

	bool losowo(int ilosc)
	{
		wektor_przedmiotow.clear();
		for (int i = 0; i < ilosc; i++)
		{
			Przedmiot item(rand() % ilosc, rand() % ilosc);
			wektor_przedmiotow.push_back(item);
			sort(wektor_przedmiotow.begin(), wektor_przedmiotow.end(), Przedmiot::porownaj);
		}
		return true;
	}
};