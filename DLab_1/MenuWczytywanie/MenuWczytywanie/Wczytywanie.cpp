
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;

void wczzytaj()
{
	string nazwa_pliku;
	srand(time(NULL));
	clock_t start, koniec;
	int menu;

	cout << "jesli chcesz wczytac i wyswietlic dane z pliku nacisnij 1\njesli chcesz wygenerowac losowa instancje nacisnij 2\n";
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

			plik_generuj << "\n" << rand() % (int)(pom_pojemnosc*0.5) + 1 << "\t" << rand() % pom_pojemnosc + 1;
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