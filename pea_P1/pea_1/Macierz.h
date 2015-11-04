#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <time.h>
#include <windows.h>

using namespace std;

class Macierz
{
	//prywatne sk³adowe klasy
public:
	int poczatkowa_droga;
	int droga_aktualna;
	int ilosc_miast;
	long czas_wykonywania;
	int **macierz;
	int *miasta;
	float T;
	float T_min;
	float alpha;	//1 - symetryczny, 0 - asymetryczny
	bool wyjatek=false;
public:

	Macierz();
	//konstruktor parametrowy u¿ywany jest przy wykonywaniu pomiarów (testów)
	Macierz(string nazwa_pliku, float Temperatura_min, float Temperatura_max, float parametr_alfa);	
	~Macierz();

	void allokuj_macierz();	
	void wypisz_macierz();	
	void wyswietl();
	void losuj_kolejnosc_miast();	
	int policz_droge();	
	void symulowanie_wyzarzania();
	void generuj_macierz();
	void wczytaj_macierz(); 
	void wczytaj_macierz(string parametr_nazwa_pliku);
	
	LARGE_INTEGER startTimer();
	LARGE_INTEGER endTimer();
};
			
			
				
			
