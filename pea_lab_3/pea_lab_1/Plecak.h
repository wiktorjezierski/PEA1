#pragma once
#include <time.h>
#include <Windows.h>

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
	vector<Przedmiot> aktualnie_best;
	int **tablica_wartosci = NULL;

	LARGE_INTEGER performanceCountStart, performanceCountEnd, Frequently;
	double tm, tm2;
	LARGE_INTEGER startTimer()
	{
		LARGE_INTEGER start;
		DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
		QueryPerformanceCounter(&start);
		SetThreadAffinityMask(GetCurrentThread(), oldmask);
		return start;
	}
	LARGE_INTEGER stopTimer()
	{
		LARGE_INTEGER stop;
		DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
		QueryPerformanceCounter(&stop);
		SetThreadAffinityMask(GetCurrentThread(), oldmask);
		return stop;
	}

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
			cout << "4. Algorytm programowania dynamicznego\n"
				 << "5. Algorytm przegladu zupelnego\n";
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
				cin >> ilosc_elementow;
				czy_wczytano = losowo(ilosc_elementow);
				wyswietl_po_wczytaniu();
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
					/*QueryPerformanceFrequency(&Frequently);
					for (int i = 0; i < 30; i++)
					{
						performanceCountStart = startTimer();
						programowanie_dynamiczne();
						performanceCountEnd = stopTimer();
						tm = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;
						tm2 = tm * 1000.0 / Frequently.QuadPart;
						cout << tm2 << endl;
					}*/
					programowanie_dynamiczne();
					wyswietl_programowanie_dynamiczne();
				}
				else
				{
					cout << endl << "Nie wczytano wartosci\n";
				}
				break;
			case 5:
				cout << "\nUruchomiono algorytm przegladu zupelnego\n";
				if (czy_wczytano)
				{
					przeglad_zupelny();
					wyswietl_przeglad_zupelny();
				}
				else
				{
					cout << endl << "Nie wczytano wartosci\n";
				}
				break;
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

	int MaxWartosc()
	{
		int temp = MININT;
		for each (Przedmiot item in wektor_przedmiotow)
		{
			if (item.wartosc > temp)
			{
				temp = item.wartosc;
			}
		}

		return temp;
	}

	void wyswietl_programowanie_dynamiczne()
	{
		bool log = true;
		int wiersz = ilosc_elementow;
		int kolumna = pojemnosc;
		int rozmiar = 0;
		do
		{
			if (tablica_wartosci[wiersz][kolumna] == tablica_wartosci[wiersz - 1][kolumna])
			{
				wiersz--;
			}
			else
			{
				cout << "\n wartosc elementu\t" << wektor_przedmiotow[wiersz - 1].wartosc << "\t rozmiar \t" << wektor_przedmiotow[wiersz - 1].rozmiar;
				rozmiar += wektor_przedmiotow[wiersz - 1].rozmiar;

				kolumna = kolumna - wektor_przedmiotow[wiersz - 1].rozmiar;
				wiersz--;
			}
			if (kolumna < 0 || wiersz == 0)
			{
				log = false;
			}

		} while (log);

		cout << "\n\nsumaryczna wartosc: " << tablica_wartosci[ilosc_elementow][pojemnosc]
			<< "\nsumaryczny rozmiar " << rozmiar << endl << endl;
	}

	void wyswietl_przeglad_zupelny()
	{
		int wartosc = 0,
			waga = 0;
		for each (Przedmiot item in aktualnie_best)
		{
			cout << "wartosc: " << item.wartosc << "\trozmiar " << item.rozmiar << endl;
			wartosc += item.wartosc;
			waga += item.rozmiar;
		}
		cout << "\nsumaryczna wartosc: " << wartosc << "\nsumaryczny rozmiar " << waga << endl << endl;
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
		int p_max = MaxWartosc();
		int poziom = ilosc_elementow * p_max;
		int y = 0;

		tablica_wartosci = new  int*[ilosc_elementow + 1];
		for (int i = 0; i <= ilosc_elementow; i++)
		{
			tablica_wartosci[i] = new int[poziom + 1];
		}



		for (int i = 0; i <= ilosc_elementow; i++)
		{
			tablica_wartosci[i][0] = 0;
		}

		for (int i = 1; i <= poziom; i++)
		{
			tablica_wartosci[0][i] = MAXINT;
		}
		

		for (int i = 1; i <= ilosc_elementow; i++)
		{
			
			for (int j = 1; j <= poziom; j++)
			{
				if ((j - wektor_przedmiotow[i-1].wartosc) < 0 || tablica_wartosci[i - 1][j - wektor_przedmiotow[i-1].wartosc] == MAXINT)
				{
					tablica_wartosci[i][j] = tablica_wartosci[i - 1][j];
				}
				else
				{
					tablica_wartosci[i][j] = min(tablica_wartosci[i - 1][j], 
						wektor_przedmiotow[i-1].rozmiar + tablica_wartosci[i - 1][j - wektor_przedmiotow[i-1].wartosc]);
				}
			}
		}

		for (int i = 0; i <= ilosc_elementow; i++)
		{

			for (int j = 0; j <= poziom; j++)
			{
				if (tablica_wartosci[i][j] == MAXINT)
				{
					cout << "MAX ";
				}
				else
					cout << tablica_wartosci[i][j] << " ";
			}
			cout << endl << endl;
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
};