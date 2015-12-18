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

	Przedmiot(){}
};
class Plecak
{	
	int pojemnosc;
	int ilosc_elementow;
	int p_max;
	float Epsylon;
	vector<Przedmiot> wektor_przedmiotow;
	vector<int>wektor_liczb;
	vector<Przedmiot> aktualnie_best;
	int **tablica_wag = NULL;
	int **indeksy = NULL;

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
		if (tablica_wag!=NULL)
		{
			for (int i = 0; i <= ilosc_elementow; i++)
			{
				delete[] tablica_wag[i];

			}
			delete[] tablica_wag;
		}

		if (indeksy != NULL)
		{
			for (int i = 0; i <= ilosc_elementow; i++)
			{
				delete[] indeksy[i];

			}
			delete[] indeksy;
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
				cout << "\nUruchomiono algorytm Aproksymacyjnego FPTAS problemu plecakowego\n";
				if (czy_wczytano)
				{
					/*cout << "Podaj Epsylon \n>";
					cin >> Epsylon;

					QueryPerformanceFrequency(&Frequently);
					for (int i = 0; i < 30; i++)
					{
						performanceCountStart = startTimer();

						programowanie_dynamiczne();
						performanceCountEnd = stopTimer();
						tm = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;
						tm2 = tm * 1000.0 / Frequently.QuadPart;
						cout << tm2 << endl;
					}*/


					cout << "Podaj Epsylon \n>";
					cin >> Epsylon;
					programowanie_dynamiczne();
					//wyswietl_programowanie_dynamiczne();
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

	void MaxWartosc()
	{
		int temp = MININT;
		for each (Przedmiot item in wektor_przedmiotow)
		{
			if (item.wartosc > temp)
			{
				temp = item.wartosc;
			}
		}

		p_max = temp;
	}

	void skalowanie()
	{
		float K;

		MaxWartosc();

		K = (Epsylon * p_max) / ilosc_elementow;

		for each (Przedmiot item in wektor_przedmiotow)
		{
			item.wartosc = (int)(item.wartosc / K);
		}
	}

	void wyswietl_programowanie_dynamiczne()
	{
		bool log = true;
		int wiersz = ilosc_elementow;
		int kolumna = 5;
		int rozmiar = 0;
		do
		{
			if (tablica_wag[wiersz][kolumna] == tablica_wag[wiersz - 1][kolumna])
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

		cout << "\n\nsumaryczna wartosc: " << tablica_wag[ilosc_elementow][pojemnosc]
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

	void wyswietl()
	{
		int x;
		for (int i = ilosc_elementow * p_max - 1; i > 0; i--)
		{
			if (indeksy[ilosc_elementow][i] != -1)
			{
				x = i;
				break;
			}
				
		}
		int y = ilosc_elementow;
		int temp = 0;
		boolean guard = true;
		Przedmiot p;
		while (temp != -1 && guard == true)
		{
			guard = false;
			if (y >= 0 && x >= 0) 
			{
				temp = indeksy[y][x];
				p = wektor_przedmiotow[indeksy[y][x] - 1];
				cout << "wartosc:\t" << p.wartosc << " waga\t" << p.rozmiar << endl;
				x -= p.rozmiar;
				y -= p.wartosc;
				guard = true;
			}
		}
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
		int poziom;
		int y = 0;
		int profit = 0;
		int waga_calkowita = 0;
		//vector<Przedmiot> wynik;

		skalowanie();
		MaxWartosc();
		poziom = ilosc_elementow * p_max;

		tablica_wag = new  int*[ilosc_elementow + 1];
		for (int i = 0; i <= ilosc_elementow; i++)
		{
			tablica_wag[i] = new int[poziom + 1];
		}

		indeksy = new int*[ilosc_elementow + 1];
		for (int i = 0; i <= ilosc_elementow; i++)
		{
			indeksy[i] = new int[poziom + 1];
		}


		for (int i = 0; i <= ilosc_elementow; i++)
		{
			tablica_wag[i][0] = 0;
			indeksy[i][0] = -1;
		}

		for (int i = 1; i <= poziom; i++)
		{
			tablica_wag[0][i] = MAXINT;
			indeksy[0][i] = -1;
		}
		

		for (int i = 1; i <= ilosc_elementow; i++)
		{
			
			for (int j = 1; j <= poziom; j++)
			{
				if ((j - wektor_przedmiotow[i-1].wartosc) < 0 || tablica_wag[i - 1][j - wektor_przedmiotow[i-1].wartosc] == MAXINT)
				{
					tablica_wag[i][j] = tablica_wag[i - 1][j];
					indeksy[i][j] = -1;
				}
				else
				{
					tablica_wag[i][j] = min(tablica_wag[i - 1][j], 
						wektor_przedmiotow[i-1].rozmiar + tablica_wag[i - 1][j - wektor_przedmiotow[i-1].wartosc]);
					indeksy[i][j] = i;
				}

				if (tablica_wag[ilosc_elementow][j] <= pojemnosc)
				{
					profit = j;
					waga_calkowita = tablica_wag[i][j];
				}
			}
		}

		

		cout << "wartosc: " << profit << endl;
		cout << "waga: " << waga_calkowita << endl;

		//for (int i = 0; i <= ilosc_elementow; i++)
		//{

		//	for (int j = 0; j <= poziom; j++)
		//	{
		//		if (tablica_wag[i][j] == MAXINT)
		//			cout << "8 ";
		//		else
		//		cout << tablica_wag[i][j] << " ";
		//	}
		//	cout << endl << endl;
		//}

		//wyswietl();
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