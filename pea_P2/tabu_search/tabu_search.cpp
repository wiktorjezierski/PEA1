#include "stdafx.h"
#include "tabu.h"
#include "conio.h"
#include <ctime>


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


int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));
	int dzialanie;
	int **odleglosci;
	string filename;

	int liczba_iteracji, rozmiar_tabu, max_bezowocnych,rozmiar_sasiedztwa;

	Macierz M(0);
	
	dzialanie = 1;
	while (dzialanie != 0) 
	{
		cout << "1 - generuj losowa macierz" << endl
			<< "2 - wczytaj macierz z pliku" << endl
			<< "3 - uruchom Tabu Search" << endl
			//<< "4 - testowanie i pomiary czasu" << endl
			<< "0 - wyjdz z programu" << endl;

		cout << "> ";
		cin >> dzialanie;

		switch (dzialanie)
		{
		case 1:
		{
			int ile;
			cout << "Podaj liczbe miast: ";
			cin >> ile;
			Macierz M1(ile);
			M = M1;

			break;
		}

		case 2:
		{
			cout << "Podaj nazwe pliku" << endl;
			cin >> filename;
			Macierz M2(filename);
			M = M2;
			odleglosci = M.macierz;
			cout << endl;
			M.wyswietl();
			cout << endl;

			break;
		}
		case 3:
		{
			cout << "Liczba iteracji algorytmu: ";
			cin >> liczba_iteracji;
			cout << "Rozmiar tabu: ";
			cin >> rozmiar_tabu;
			cout << "Liczba bezowocnych iteracji, po ktorych zmieniamy miejsce poszukiwan: ";
			cin >> max_bezowocnych;
			cout << "Rozmiar sasiedztwa: ";
			cin >> rozmiar_sasiedztwa;

			QueryPerformanceFrequency(&Frequently);
				Trasa T(M);
				Tabu tabu(T);

				cout << "\nDlugosc trasy na poczatku: " << T.dlugosc_trasy << endl;
				cout << "Trasa na poczatku algorytmu: ";
				Trasa solution = tabu.tabu_search(M.macierz, liczba_iteracji, rozmiar_tabu, max_bezowocnych, rozmiar_sasiedztwa);
				
				cout << "\nDlugosc trasy na koncu: " << solution.dlugosc_trasy << endl;
				cout << "Trasa na koncu algorytmu: ";
				solution.wyswietl_trase();
				cout << endl << endl;
				
				
				break;
			
		}

		case 4:
		{
			string nazwa_pliku;
			cout << "Nazwa pliku: ";
			cin >> nazwa_pliku;
			cout << "Liczba iteracji algorytmu: ";
			cin >> liczba_iteracji;
			cout << "Rozmiar tabu: ";
			cin >> rozmiar_tabu;
			cout << "Liczba bezowocnych iteracji, po ktorych zmieniamy miejsce poszukiwan: ";
			cin >> max_bezowocnych;
			cout << "Rozmiar sasiedztwa: ";
			cin >> rozmiar_sasiedztwa;

			string nazwa;
			nazwa = "WYNIKI";

			ofstream plik("WYNIKI.txt");
			//for(int i=0; i<14;i++)
			//{
			//Macierz M4(nazwy_plikow[i]);

			Macierz M4(nazwa_pliku);
			M = M4;
			clock_t start, koniec;
			long int czas;
			Trasa T(M);
			Tabu tabu(T);

			start = clock();
			Trasa solution = tabu.tabu_search(M.macierz, liczba_iteracji, rozmiar_tabu, 10, rozmiar_sasiedztwa);
			koniec = clock();
			czas = (long)(koniec - start);
			solution.wyswietl_trase();
			cout << "DLUGOSC TRASY: " << solution.dlugosc_trasy << endl;
			cout << "CZAS: " << czas << endl;

			plik << nazwa_pliku << " " << M.ilosc_miast << " " << solution.dlugosc_trasy << " " << czas << endl;
			//plik<<nazwy_plikow[i]<<" "<<solution.dlugosc_trasy<<" "<<czas<<endl;
			//}
			break;
		}
		}
	}
	cin.ignore();
	cin.get();
	return 0;
}

