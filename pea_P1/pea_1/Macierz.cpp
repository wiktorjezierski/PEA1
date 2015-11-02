#include "stdafx.h"
#include "Macierz.h"

Macierz::Macierz()
{
	srand(time(NULL));
	int menu;
	cout << "Algorytm  wyzarzania dla problemu komiwojarzera\n";
	cout << "1 - wczytaj z pliku\n2 - generowanie automatyczne\n";
	cin >> menu;
	if (menu == 1)
	{
		wczytaj_macierz();
		//	wypisz_macierz();
	}
	if (menu == 2)
	{
		generuj_macierz();
	}
}

Macierz::Macierz(string nazwa_pliku, float Temperatura_min, float Temperatura_max, float parametr_alfa)
{
	T = Temperatura_max;
	T_min = Temperatura_min;
	alpha = parametr_alfa;
	//niezbêdne do poprawnego generowania wartoœci pseudolosowych
	srand(time(NULL));
	wczytaj_macierz(nazwa_pliku);
}

Macierz::~Macierz()
{
	//zwolnienie pamieci
	if (wyjatek == false)
	{
		for (int i = 0; i < ilosc_miast; i++)
		{
			delete[] macierz[i];
		}

		delete[] macierz;
		delete[] miasta;
	}
}

void Macierz::allokuj_macierz()
{
	//próba z³apania wyj¹tku polegaj¹cego na chêci 
	//allokowania zbyt du¿ego obszarze pamiêci przez u¿ytkownika 
	//aplikacja wyœwietli komunikat lecz nie zamknie siê zamoistnie  program nie przeprowadza walidacji :) wrowadzanych danych 
	try
	{
		macierz = new int *[ilosc_miast];
	}
	catch (exception& e)
	{

		cout << "Standard exception: " << e.what() << endl;
		wyjatek = true;
		getchar();

	}
	try
	{
		miasta = new int[ilosc_miast];
	}
	catch (exception& e)
	{

		cout << "Standard exception: " << e.what() << endl;
		wyjatek = true;
		getchar();

	}
	for (int i = 0; i < ilosc_miast; i++)
	{
		miasta[i] = -1;
	}
	for (int i = 0; i < ilosc_miast; i++)
	{
		try
		{
			macierz[i] = new int[ilosc_miast];
		}
		catch (exception& e)
		{

			cout << "Standard exception: " << e.what() << endl;
			wyjatek = true;
			getchar();
			break;
		}
	}
}

void Macierz::wypisz_macierz()
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

void Macierz::wyswietl()
{
	for (int i = 0; i < ilosc_miast; i++)
	{
		cout << miasta[i]<<" ";
	}
}

void Macierz::losuj_kolejnosc_miast()
{
	int numer_zamienianego_miasta;
	//pocz¹tkowo miasta s¹ ostawione w  kolejnoœci rosn¹cej
	for (int i = 0; i < ilosc_miast; i++)
	{
		miasta[i] = i;
	}
	//kazde miasto zamieniamy z losowo wybranym
	for (int i = 0; i < ilosc_miast; i++)
	{
		do
		{
			numer_zamienianego_miasta = rand() % ilosc_miast;
		} while (i == numer_zamienianego_miasta);

		swap(miasta[i], miasta[numer_zamienianego_miasta]);
	}
}

int Macierz::policz_droge()
{
	int wynik = 0;

	int nr_miasta_poczatkowego;
	int nr_miasta_docelowego;

	for (int i = 0; i < ilosc_miast - 1; i++)
	{
		nr_miasta_poczatkowego = miasta[i];
		nr_miasta_docelowego = miasta[i + 1];
		wynik = wynik + macierz[nr_miasta_poczatkowego][nr_miasta_docelowego];
		if (i == ilosc_miast - 2)
		{
			nr_miasta_poczatkowego = miasta[ilosc_miast - 1];
			nr_miasta_docelowego = miasta[0];

			wynik = wynik + macierz[nr_miasta_poczatkowego][nr_miasta_docelowego];
		}

	}

	return wynik;
}

void Macierz::symulowanie_wyzarzania()
{
	int numer_pierwszego_miasta;
	int numer_drugiego_miasta;
	int droga_po_swap;
	float p;
	float losowa;
	while (T > T_min)
	{
		numer_pierwszego_miasta = rand() % ilosc_miast;
		numer_drugiego_miasta = rand() % ilosc_miast;
		swap(miasta[numer_pierwszego_miasta], miasta[numer_drugiego_miasta]);
		droga_po_swap = policz_droge();
		p = exp(-((droga_po_swap - droga_aktualna) / T));
		losowa = float(rand()) / (RAND_MAX);
		if (droga_po_swap < droga_aktualna || (losowa < p))
		{
			droga_aktualna = droga_po_swap;
		}
		else
		{
			swap(miasta[numer_drugiego_miasta], miasta[numer_pierwszego_miasta]);
		}

		T = T*alpha;
		T -= 1;
	}

}

void Macierz::generuj_macierz()
{

	LARGE_INTEGER performanceCountStart, performanceCountEnd;
	double tm;

	cout << "Liczba miast\t";
	cin >> ilosc_miast;
	cout << "Temperatura minimalna\t";
	cin >> T_min;
	cout << "Temperatura startowa\t";
	cin >> T;
	//cout << "Wspolczynnik Alfa\t";	 //docelowo to ukryc
	//cin >> alpha;
	alpha = 1;


	//tworzenie macierzy zawierajacej koszt przejscia miedzy miastami
	allokuj_macierz();

	int losowa;
	for (int i = 0; i < ilosc_miast; i++)
	{
		for (int j = 0; j < ilosc_miast; j++)
		{
			if (i == j)
			{
				//po³¹czeniu danego miasta ze samym sob¹ przypisujemy zerowy koszt
				macierz[i][j] = 0;
			}
			else
			{
				do
				{
					losowa = rand() % 10;
				} while (losowa == 0);
				macierz[i][j] = losowa;

			}
		}
	}

	losuj_kolejnosc_miast();
	poczatkowa_droga = policz_droge();
	cout << "\nDroga na poczatku algorytmu\t" << poczatkowa_droga << "\n";
	droga_aktualna = poczatkowa_droga;
	//clock_t start, koniec;
			
		performanceCountStart = startTimer();
		symulowanie_wyzarzania();
		performanceCountEnd = endTimer();
		long czas_wykonania = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;
		cout << "\nDroga po wyzarzaniu \t" << droga_aktualna << "\n";
		cout << "\nCzas wykonania algorytmu w ms wynosi\t" << czas_wykonania << "\n";	//to potem ukryc
	

}

void Macierz::wczytaj_macierz()
{
	LARGE_INTEGER performanceCountStart, performanceCountEnd;
	double tm;

	vector<string>wektor_odczytu;
	vector<int>wektor_odczytu_liczb;
	string nazwa_pliku;
	string linia;
	cout << "Podaj nazwe pliku\n";
	cin >> nazwa_pliku;
	nazwa_pliku += ".txt";
	fstream plik;

	plik.open(nazwa_pliku, ios::in);
	if (!plik.good())
	{
		cout << "Blad podczas wczytywania pliku\n";
	}
	else if (plik.good())
	{
		cout << "Wczytano plik\n";

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
		cout << "\nilosc miats\t" << wektor_odczytu_liczb[0];
		ilosc_miast = wektor_odczytu_liczb[0];
		allokuj_macierz();
		wektor_odczytu_liczb.erase(wektor_odczytu_liczb.begin());
		if (wektor_odczytu_liczb.size() != pow(ilosc_miast, 2))
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
			cout << "\nTemperatura minimalna\t";
			cin >> T_min;
			cout << "temperature startowa\t";
			cin >> T;
			/*cout << "Wspolczynnik alfa\t";
			cin >> alpha;*/
			alpha = 1;
			losuj_kolejnosc_miast();
			poczatkowa_droga = policz_droge();
			cout << "\ndroga na poczatku algorytmu\t" << poczatkowa_droga << "\n";
			droga_aktualna = poczatkowa_droga;

			/*for (int i = 0; i < 10; i++)
			{*/
				performanceCountStart = startTimer();
				symulowanie_wyzarzania();
				performanceCountEnd = endTimer();
				long czas_wykonania = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;
				cout << "\nDroga po wyzarzaniu wynosi\t" << droga_aktualna << "\n";
				cout << "\nCzas wykonania algorytmu w ms wynosi\t" << czas_wykonania << "\n";
			//}
		}
	}
}

void Macierz::wczytaj_macierz(string parametr_nazwa_pliku)
{
	vector<string>wektor_odczytu;
	vector<int>wektor_odczytu_liczb;
	string nazwa_pliku = parametr_nazwa_pliku;
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

		ilosc_miast = wektor_odczytu_liczb[0];
		allokuj_macierz();
		wektor_odczytu_liczb.erase(wektor_odczytu_liczb.begin());
		if (wektor_odczytu_liczb.size() != pow(ilosc_miast, 2))
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

			losuj_kolejnosc_miast();
			poczatkowa_droga = policz_droge();
			//	cout << "\nPoczatkowo droga wynosi\t" << poczatkowa_droga << "\n";
			clock_t start, koniec;
			start = clock();
			symulowanie_wyzarzania();
			koniec = clock();
			long czas_wykonania = (long)(koniec - start);
			czas_wykonywania = czas_wykonania;
			//cout << "\nDroga po wyzarzaniu wynosi\t" << droga_aktualna << "\n";
			//	cout << "\nCzas wykonania algorytmu w ms wynosi\t" << czas_wykonania << "\n";
		}
	}
}

LARGE_INTEGER Macierz::startTimer()
{
	LARGE_INTEGER start;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&start);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return start;
}
LARGE_INTEGER Macierz::endTimer()
{
	LARGE_INTEGER stop;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&stop);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return stop;
}