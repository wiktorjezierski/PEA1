# pragma once
#include "stdafx.h"
#include <algorithm>
#include <stdio.h>
#include <time.h>
//#include <ctime>

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
	int **tablica_wartosci = NULL;

public:
	Plecak()
	{
		//string nazwa_pliku;	    
		//int menu;
		//
		//cout << "jesli chcesz wczytac dane z pliku nacisnij 1\njesli chcesz wygenerowac losowa instancje nacisnij 2\n";
		//cin >> menu;
		//
		//if (menu == 1)
		//{
		//	cout << "\npodaj nazwe pliku z instancja testowa\n";
		//	cin >> nazwa_pliku;
		//}
		//if (menu == 2)
		//{
		//	ofstream plik_generuj;
		//	int pom_pojemnosc;
		//	int pom_ilosc_elementow;
		//	plik_generuj.open("generowany.txt");
		//	cout << "Podaj pojemnosc plecaka\n";
		//	cin >> pom_pojemnosc;
		//	plik_generuj << "\n" << pom_pojemnosc;
		//	cout << "Podaj ilosc elementow\n";
		//	cin >> pom_ilosc_elementow;
		//	plik_generuj << "\n" << pom_ilosc_elementow;
		//
		//	for (int i = 0; i < pom_ilosc_elementow; i++)
		//	{
		//		
		//			plik_generuj << "\n" << rand() %(int) (pom_pojemnosc*0.5) + 1 << "\t" << rand() % pom_pojemnosc + 1;
		//	}
		//	nazwa_pliku = "generowany.txt";
		//	plik_generuj.close();			
		//	
		//}
		//
		//	if (menu == 1 || menu == 2)
		//	{
		//	if (wczytaj_plik_testowy(nazwa_pliku))
		//	{
		//		//pobranie pojemnosci plecaka, oraz usuniecie tej danej z wektora
		//		pojemnosc = wektor_liczb.front();
		//		//usuniecie pierwszego elementu wektora
		//		wektor_liczb.erase(wektor_liczb.begin());
		//		//pobranie ilosci elementow, oraz usuniecie tej danej z wektora
		//		ilosc_elementow = wektor_liczb.front();
		//		//usuniecie pierwszego elementu wektora
		//		wektor_liczb.erase(wektor_liczb.begin());
		//		cout << "Problem plecakowy\nzlodziej ma do dyspozycji\t" << ilosc_elementow << " elementow\n" << "pojemnosc plecaka wynosi\t" << pojemnosc << "\n";
		//		if (wektor_liczb.size() == 2 * ilosc_elementow)
		//		{
		//			//stworzenie wektora zawierajacego elementy plecaka
		//			for (int i = 0; i < wektor_liczb.size(); i = i + 2)
		//			{
		//				wektor_przedmiotow.push_back(Przedmiot(wektor_liczb[i], wektor_liczb[i + 1]));
		//			}
		//
		//			tablica_wartosci = new  int*[ilosc_elementow+1];
		//			for (int i = 0; i < ilosc_elementow+1; i++)
		//			{
		//				tablica_wartosci[i] = new int[pojemnosc+1];
		//				
		//			}
		//			programowanie_dynamiczne();
		//		}
		//	}
		//	else
		//	{
		//		cout << "Niepoprawna ilosc wczytanych wartosci\nalgorytm nie wykona sie :(\n";
		//	}
		//										
		//}			
	}

	//Plecak(string nazwa_pliku)
	//{
	//	if (wczytaj_plik_testowy(nazwa_pliku))
	//	{
	//		//pobranie pojemnosci plecaka, oraz usuniecie tej danej z wektora
	//		pojemnosc = wektor_liczb.front();
	//		//usuniecie pierwszego elementu wektora
	//		wektor_liczb.erase(wektor_liczb.begin());
	//		//pobranie ilosci elementow, oraz usuniecie tej danej z wektora
	//		ilosc_elementow = wektor_liczb.front();
	//		//usuniecie pierwszego elementu wektora
	//		wektor_liczb.erase(wektor_liczb.begin());
	//		cout << "Problem plecakowy\nzlodziej ma do dyspozycji\t" << ilosc_elementow << " elementow\n" << "pojemnosc plecaka wynosi\t" << pojemnosc << "\n";
	//		if (wektor_liczb.size() == 2 * ilosc_elementow)
	//		{
	//			//stworzenie wektora zawierajacego elementy plecaka
	//			for (int i = 0; i < wektor_liczb.size(); i = i + 2)
	//			{
	//				wektor_przedmiotow.push_back(Przedmiot(wektor_liczb[i], wektor_liczb[i + 1]));
	//			}
	//
	//			tablica_wartosci = new  int*[ilosc_elementow + 1];
	//			for (int i = 0; i < ilosc_elementow + 1; i++)
	//			{
	//				tablica_wartosci[i] = new int[pojemnosc + 1];
	//
	//			}
	//		programowanie_dynamiczne();
	//		}
	//	}
	//	else
	//	{
	//		cout << "Niepoprawna ilosc wczytanych wartosci\nalgorytm nie wykona sie :(\n";
	//	}
	//}

	~Plecak()
	{
		wektor_przedmiotow.clear();
		wektor_liczb.clear();
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

	void zarzadzaj()
	{
		int wybor = 666;
		int wybor2;
		bool czy_wczytano = false;
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
			cout << "4. Algorytm programowania dynamicznego\n";
			cout << "0. EXIT\n";
			cout << "-----------------------------\n\n";
			cin >> wybor;
			switch (wybor)
			{
			case 1:
				cout << "Podaj nazwe pliku:\n";
				cin >> nazwaPliku;
				czy_wczytano = wczytaj_z_pliku(nazwaPliku);
				wyswietl_po_wczytaniu();
				cout << "\n";
				break;
			case 2:
				cout << "Wygeneruj losowo()\nIle elementow wygenerowac?\n> ";
				int ile;
				cin >> ile;
				czy_wczytano = losowo(ile);
				cout << "\n";
				break;
			case 3:
				cout << "podaj nowy rozmiar plecaka: ";
				cin >> pojemnosc;
				cout << "\n";
				break;
			case 4:
				cout << "\nUruchomiono algorytm programowania dynamicznego\n";
				if (czy_wczytano)
				{
					programowanie_dynamiczne();
				}
				else
				{
					cout << endl << "Nie wczytano wartosci\n";
				}
			default:
				break;
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

			/*tablica_wartosci = new  int*[ilosc_elementow + 1];
			for (int i = 0; i < ilosc_elementow + 1; i++)
			{
				tablica_wartosci[i] = new int[pojemnosc + 1];
			}*/

			return true;
		}
		else
		{
			cout << "blednda nazwa pliku\n";
			return false;
		}

	}

	void wyswietl_po_wczytaniu()
	{
		for each (Przedmiot item in wektor_przedmiotow)
		{
			cout << "rozmiar: " << item.rozmiar << " wartosc: " << item.wartosc << endl;
		}

		cout << endl;
	}

	bool losowo(int ilosc)
	{
		srand(time(NULL));
		wektor_przedmiotow.clear();
		for (int i = 0; i < ilosc; i++)
		{
			Przedmiot item(rand() % ilosc, rand() % ilosc);
			wektor_przedmiotow.push_back(item);
		}

		/*tablica_wartosci = new  int*[ilosc_elementow + 1];
		for (int i = 0; i < ilosc_elementow + 1; i++)
		{
			tablica_wartosci[i] = new int[pojemnosc + 1];
		}*/
		return true;
	}

	void  programowanie_dynamiczne()
	{
		tablica_wartosci = new  int*[ilosc_elementow + 1];
		for (int i = 0; i < ilosc_elementow + 1; i++)
		{
			tablica_wartosci[i] = new int[pojemnosc + 1];
		}

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

		cout << "\n\nnajlepsze rozwiazanie\t" << tablica_wartosci[ilosc_elementow][pojemnosc] << endl;
	}		
};