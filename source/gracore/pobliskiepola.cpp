#include "../status.h"
#include "gameresult.h"

// Zwraca pola otaczające aktualnie wybrane pole
int *spisz_pobliskie_pola(Plansza *plansza, int pole) {
	int *pola = new int[9];
	int szer = plansza->width;
	int wys = plansza->height;
	
	pola[0] = pole - szer - 1;
	pola[1] = pole - szer;
	pola[2] = pole - szer + 1;
	pola[3] = pole - 1;
	pola[4] = pole; // Środek, obecnie wybrane pole
	pola[5] = pole + 1;
	pola[6] = pole + szer - 1;
	pola[7] = pole + szer;
	pola[8] = pole + szer + 1;
	
	if (pole < szer) { // pola przy górnej krawędzi planszy
		pola[0] = pole;
		pola[1] = pole;
		pola[2] = pole;
	}
	if (pole >= szer * (wys - 1)) { // pola przy dolnej krawędzi planszy
		pola[6] = pole;
		pola[7] = pole;
		pola[8] = pole;
	}
	if ((pole + 1) % szer == 0) { // pola przy prawej krawedzi planszy
		pola[2] = pole;
		pola[5] = pole;
		pola[8] = pole;
	}
	if (pole % szer == 0) { // pola przy lewej kręwedzi planszy
		pola[0] == pole;
		pola[3] == pole;
		pola[6] == pole;	
	}
	return pola;
}

void sprawdz_pobliskie_pola(Plansza *plansza, int pole) {
	int *pobliskie = spisz_pobliskie_pola(plansza, pole);
	for (int i = 0; i < 9; i++) {
		int pob_pole = pobliskie[i];
		Plansza_pole *x = &plansza->pola[pob_pole];
		if (pob_pole != pole && x->sprawdzone_pole != true && x->oznaczone_pole != true) { // Pobliskie pole nie jest oznaczone ani sprawdzone więc można sprawdzić
			x->sprawdzone_pole = true;
			if (x->jest_bomba != true && x->ile_bomb == 0) {
				sprawdz_pobliskie_pola(plansza, pob_pole); // Rekursywnie otwiera następne pola, jeżeli nie ma w pobliżu żadnych bomb
			} else if (x->jest_bomba) {
				przegrana(plansza);
				break;
			}
		}
	}
	delete pobliskie;
}