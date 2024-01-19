#include <cstdlib>
#include <ctime>

#include "../status.h"
#include "pobliskiepola.h"


void zainicjalizuj_gre(Plansza *plansza) {
	// Generuje bezpieczny start, sprawdzając pola wokól pola startowego
	int pole = plansza->pole_now;
	int *spisz_pola = spisz_pobliskie_pola(plansza, pole);
	for (int i = 0; i <= 8; i++) {
		plansza->pola[spisz_pola[i]].sprawdzone_pole = true;
		plansza->pola[spisz_pola[i]].jest_bomba = false;
	}
	
	// Wygenerowanie min
	srand((int)time(0)); // Generuje losowy seed w zależności od obecnego czasu
	int m = 0;
	int zakres = plansza->width * plansza->height;
	while (m < plansza->miny) {
		//Generuje losowe pole w zakresie pól planszy na które stawia mine póki nie będzie ich tyle ile ustawił gracz
		int n = rand() % zakres;
		Plansza_pole *p = &plansza->pola[n];
		if (p->jest_bomba != true && p->sprawdzone_pole != true) {
			p->jest_bomba = true;
			m++;
		}
	}
	
	// Podpisuje pobliskie pola wokól pola startowego ilością bomb z którymi te pola się stykają
	for (int i = 0; i < zakres; i++) {
		if (plansza->pola[i].jest_bomba == true) {
			continue;
		}
		int *pobliskie = spisz_pobliskie_pola(plansza, i);
		for (int j = 0; j <= 8; j++) {
			int pob_pole = pobliskie[j];
			if (pob_pole != i && plansza->pola[pob_pole].jest_bomba == true) {
				plansza->pola[i].ile_bomb++;
			}
		}
		delete pobliskie;
	}
	
	// Sprawdza puste pola których nie otacza żadna mina
	for (int i = 0; i <= 8; i++) {
		if (plansza->pola[spisz_pola[i]].ile_bomb == 0) {
			sprawdz_pobliskie_pola(plansza, spisz_pola[i]);
		}
	}
	delete spisz_pola;
	
	plansza->status = Gra;
}