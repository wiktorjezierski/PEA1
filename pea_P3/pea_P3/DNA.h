#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <windows.h>
#include "genom.h"
using namespace std;

class DNA
{
public:
	DNA();
	~DNA();

	vector<genom> lista_genomow;
	int **zrodlowa;
	int ilosc_miast;
	int size;
	int osobnicy;

	LARGE_INTEGER performanceCountStart, performanceCountEnd, Frequently;
	double tm, tm2;

	bool wczytaj(string nazwa_pliku);
	void wyswietl_wczytane_miasta();
	int droga_miedzy_miastami(int pierwsze, int drugie);
	void generuj_warunki_poczatkowe();
	void generuj();
	void odrzuc_najgorsze();
	int wybierz_najlepsze();
	int selekcja_naturalna();
	void zarzadzaj();
	void menu();
	void wyswietl(int wybor);
	void wyswietl_wszystko();
	LARGE_INTEGER startTimer();
	LARGE_INTEGER stopTimer();
};

