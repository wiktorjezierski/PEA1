#include "Trasa.h"
#include <vector>
#include <list>
#include <fstream>

class Tabu
{
public:

	Trasa trasa;

	Tabu(Trasa &T)
	{
		this->trasa = T;
	}

	//funkcja wybiera najlepszego s¹siada (najkrótsza droga)
	Trasa wybierz_sasiada(int **tab,Trasa route, list<Trasa> tabu,int rozmiar_sasiedztwa)
	{
		Trasa sasiad = route;
		Trasa najlepszy_sasiad = sasiad;
		
		int rand1, rand2;

		for (unsigned int i = 0; i < rozmiar_sasiedztwa - 1; i++)
		{
			do
			{
			rand1 = rand() % sasiad.trasa.size();
			rand2 = rand() % sasiad.trasa.size();
			}while(rand1==rand2);
				//sasiad.invert(i,j);
				sasiad.swap(rand1,rand2);
				//sasiad.wyswietl_trase();

				sasiad.policz_droge(tab);
				najlepszy_sasiad.policz_droge(tab);

				//jeœli mamy krótsz¹ trasê, której nie ma na liscie tabu, to nadpisujemy jako najlepszego s¹siada
				if (sasiad.dlugosc_trasy < najlepszy_sasiad.dlugosc_trasy && !sprawdz_w_tabu(tabu, sasiad))
					najlepszy_sasiad = sasiad;
				
				sasiad.swap(rand1, rand2);
		}
			return najlepszy_sasiad;
	}

	//funkcja zwraca true, gdy znajdzie trase na liscie tabu
	bool sprawdz_w_tabu(list<Trasa> lista, Trasa route)
	{
		for (list<Trasa>::iterator i = lista.begin(); i != lista.end(); i++)
		{
			if (*i == route)
			{
			    //cerr << (*i).dlugosc_trasy<< " = " << route.dlugosc_trasy << "\n";
				return true;
			}
		}
		return false;
	}

//wlasciwa funkcja tabu search
Trasa tabu_search(int **tab, int liczba_iteracji, int tabu_max, int tabuTime, int rozmiar_sasiedztwa)
{
	Trasa solution = trasa;
	solution.wyswietl_trase();
	solution.mieszaj(tab);
	//solution.wyswietl_trase();
	//cerr<<"MIESZANA:";
	Trasa route = solution;				// Aktualnie rozpatrywana droga
	//route.wyswietl_trase();

	//licznik bezowocnych iteracji
	int iteracje = 0;

	//int rand1, rand2;

	list<Trasa> tabu = list<Trasa>();

	
	for (int i = 1; i <= liczba_iteracji; i++)
	{
		iteracje++;

		route = wybierz_sasiada(tab, route, tabu,rozmiar_sasiedztwa);
		if(tabu.size() == tabu_max) 
		{
			tabu.pop_back();
		}
		tabu.push_front(route);
		
		if(iteracje > tabuTime)
		{
			{
				route.mieszaj(tab);    //przeskakujemy w inny rejon rozwiazan, jesli bylo duzo bezowocnych iteracji
				iteracje = 0;
			}
		}
						
		//jesli znajdujemy mniejsza droge, to przypisujemy ja do rozwiazania i zerujemy licznik bezowocnych iteracji
		if (route.policz_droge(tab) < solution.policz_droge(tab))
		{
			iteracje = 0;
			solution = route;
			//solution.wyswietl_trase();
			//cout << solution.dlugosc_trasy << endl;
		}
	}
	
	return solution;
}

};