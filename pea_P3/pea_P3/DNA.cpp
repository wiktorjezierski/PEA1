#include "stdafx.h"
#include "DNA.h"



DNA::DNA()
{
}


DNA::~DNA()
{
}

bool DNA::wczytaj(string nazwa_pliku)
{
	fstream plik;
	plik.open(nazwa_pliku + ".txt", ios::in);
	if (!plik.good())
	{
		cout << "niepoprawnie wczytany plik\n";
		return false;
	}
	else if (plik.good())
	{
		string tekst;

		getline(plik, tekst, '\n');
		stringstream konwersja;
		konwersja.clear();
		konwersja << tekst;
		konwersja >> ilosc_miast;
		size = ilosc_miast;

		zrodlowa = new int *[ilosc_miast];

		for (int i = 0; i < ilosc_miast; i++)
		{
			zrodlowa[i] = new int[ilosc_miast];
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
				konwersja >> zrodlowa[i][j];
			}

			string tekst2;
			getline(plik, tekst2, '\n');
			stringstream konwersja;
			konwersja.clear();
			konwersja << tekst2;
			konwersja >> zrodlowa[i][ilosc_miast - 1];
		}
		return true;
	}
}

void DNA::wyswietl_wczytane_miasta()
{
	for (int i = 0; i < ilosc_miast; i++)
	{
		for (int j = 0; j < ilosc_miast; j++)
		{
			cout << zrodlowa[i][j] << " ";
		}
		cout << endl;
	}
}

int DNA::droga_miedzy_miastami(int pierwsze, int drugie)
{
	if (pierwsze < ilosc_miast && drugie < ilosc_miast)	//zabezpieczenie przed przekroczeniem zakresu tablicy
		return zrodlowa[pierwsze][drugie];
	else
		return -1;
}

void DNA::generuj_warunki_poczatkowe()
{
	for (int i = 0; i < size - 1; i++)
	{
			genom gen;
			int pierwsze = rand() % ilosc_miast;
			int drugie = rand() % ilosc_miast;
			if (pierwsze == drugie)
			{
				drugie++;
			}
				gen.dodaj(pierwsze, drugie, droga_miedzy_miastami(pierwsze, drugie));
				lista_genomow.push_back(gen);
	}
}

//dodanie kolejnego miasta do sciezki
void DNA::generuj()
{
	volatile bool test = true;
	for (int i = 0; i < lista_genomow.size(); i++)	
	{
		//cout << "generuj " << i << endl;
		test = true;
		while (test) 
		{
			int pierwsze = rand() % ilosc_miast;
			int drugie = rand() % ilosc_miast;
			
			if (lista_genomow[i].zawiera_raz(pierwsze) == true && lista_genomow[i].nie_zawiera(drugie) == true
				|| lista_genomow[i].zawiera_raz(drugie) == true && lista_genomow[i].nie_zawiera(pierwsze) == true)
			{
				lista_genomow[i].dodaj(pierwsze, drugie, droga_miedzy_miastami(pierwsze, drugie));
				test = false;
			}
		}
	}
}

void DNA::odrzuc_najgorsze()
{
	int temp = 999999;
	int nr_elementu;
	for (int i = 0; i < lista_genomow.size(); i++)
	{
		if (lista_genomow[i].dlugosc_drogi < temp)
		{
			temp = lista_genomow[i].dlugosc_drogi;
			nr_elementu = i;
		}
	}

	lista_genomow.erase(lista_genomow.begin() + nr_elementu);
}

int DNA::wybierz_najlepsze()
{
	int temp = 0;
	int nr_elementu;
	for (int i = 0; i < lista_genomow.size(); i++)
	{
		if (lista_genomow[i].dlugosc_drogi > temp)
		{
			temp = lista_genomow[i].dlugosc_drogi;
			nr_elementu = i;
		}
	}

	return nr_elementu;
}

int DNA::selekcja_naturalna()
{
	for (int i = 0; i < size - 2; i++)
	{
		//cout << "generuj " << i << endl;
		generuj();

		if (lista_genomow.size() > 1)
			odrzuc_najgorsze();
	}

	if (lista_genomow.size() > 1)
		return wybierz_najlepsze();
	else
		return 0;
}

void DNA::zarzadzaj()
{
	generuj_warunki_poczatkowe();
	int wybor = selekcja_naturalna();
	////wyswietl_wszystko();
	wyswietl(wybor);
	////wyswietl_wszystko();
	lista_genomow.clear();
}

void DNA::menu()
{
	int wybor = 666;
	int wybor2;
	bool czy_wczytano = false;
	string nazwaPliku;

	cout << "Podaj rozmiar plecaka: ";
	//cin >> pojemnosc;
	system("cls");

	while (wybor != 0) {
		wybor2 = 666;
		cout << "\tMENU\n";
		cout << "Wybierz opcje:\n";
		cout << "-----------------------------\n";
		cout << "1. Wczytaj z pliku\n";
		//cout << "2. Wygeneruj losowo\n";
		cout << "2. Algorytm Genetyczny\n";
		cout << "0. EXIT\n";
		cout << "-----------------------------\n\n";
		cin >> wybor;
		switch (wybor)
		{
		case 1:
			cout << "Podaj nazwe pliku:\n";
			cin >> nazwaPliku;
			czy_wczytano = wczytaj(nazwaPliku);
			wyswietl_wczytane_miasta();
			cout << "\n";
			break;
		//case 2:
			/*cout << "Wygeneruj losowo()\nIle elementow wygenerowac?\n> ";
			cin >> ilosc_elementow;
			czy_wczytano = losowo(ilosc_elementow);
			wyswietl_po_wczytaniu();
			cout << "\n";
			break;*/

		case 2:
			cout << "\nUruchomiono algorytm genetyczny\n";
			if (czy_wczytano)
			{
				int ile;
				/*QueryPerformanceFrequency(&Frequently);
				for (int i = 0; i < 30; i++)
				{
				performanceCountStart = startTimer();
				zarzadzaj();
				performanceCountEnd = stopTimer();
				tm = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;
				tm2 = tm * 1000.0 / Frequently.QuadPart;
				cout << tm2 << endl;
				}*/
				cout << "podaj liczbe krzyzowan\n>";
				cin >> ile;
				cout << "podaj liczbe osobnikow\n>";
				cin >> ile;
				zarzadzaj();
				//wyswietl_programowanie_dynamiczne();
			}
			else
			{
				cout << endl << "Nie wczytano wartosci\n";
			}
			break;
		//case 5:
		//	cout << "\nUruchomiono algorytm przegladu zupelnego\n";
		//	if (czy_wczytano)
		//	{
		//		przeglad_zupelny();
		//		wyswietl_przeglad_zupelny();
		//	}
		//	else
		//	{
		//		cout << endl << "Nie wczytano wartosci\n";
		//	}
		//	break;
		default:
			break;
		}
	}
}


void DNA::wyswietl(int wybor)
{
	lista_genomow[wybor].wyswietl();
}

void DNA::wyswietl_wszystko()
{
	for each (genom g in lista_genomow)
	{
		g.wyswietl();
		cout << endl;
	}
}


LARGE_INTEGER DNA::startTimer()
{
	LARGE_INTEGER start;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&start);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return start;
}
LARGE_INTEGER DNA::stopTimer()
{
	LARGE_INTEGER stop;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&stop);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return stop;
}