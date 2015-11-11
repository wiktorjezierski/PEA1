# pragma once
#include <algorithm>
#include <time.h>

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
	Plecak(){}
	
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