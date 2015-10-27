// MenuWczytywanie.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main()
{
	int wybor = 666;
	int wybor2 = 666;
	string nazwaPliku;
	int rozmPlecaka;
	
	cout << "Podaj rozmiar plecaka: ";
	cin >> rozmPlecaka;
	system("cls");

	while (wybor != 0) {
		cout << "\tMENU\n";
		cout << "Wybierz opcje:\n";
		cout << "-----------------------------\n";
		cout << "1. Wczytaj z pliku\n";
		cout << "2. Wygeneruj losowo\n";
		cout << "3. Zmien rozmiar plecaka\n";
		cout << "0. EXIT\n";
		cout << "-----------------------------\n\n";
		cin >> wybor;
			switch (wybor)
			{
			case 1:
				cout << "Podaj nazwe pliku:\n";
				//cin >> nazwaPliku;
				cout << "Wczytaj_z_pliku()";
				cout << "\n";
				system("cls");
				break;
			case 2:
				cout << "Wygeneruj losowo()";
				cout << "\n";
				system("cls");
				break;
			case 3:
				cout << "Zmien rozmiar()";
				cout << "\n";
				system("cls");
				break;
			default:
				break;
			}
			while (wybor2 != 0) {
				cout << "\tWybierz algorytm:\n";
				cout << "-----------------------------\n";
				cout << "1. Branch and bound\n";
				cout << "2. Best First\n";
				cout << "3. Przeglad zupelny\n";
				cout << "0. BACK\n";
				cout << "-----------------------------\n\n";
				cin >> wybor2;
				switch (wybor2)
				{
				case 1:
					system("cls");
					cout << "Branch and bound()";
					cin.get();
					system("cls");
					break;
				case 2:
					system("cls");
					cout << "Best First()";
					cin.get();
					system("cls");
					break;
				case 3:
					system("cls");
					cout << "Przeglad zupelny()";
					cin.get();
					system("cls");
					break;
				case 0:
					system("cls");
				default:
					break;
				}
			}

	}

    return 0;
}

