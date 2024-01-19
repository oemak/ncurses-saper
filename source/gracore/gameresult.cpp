#include "../status.h"

void przegrana(Plansza *plansza) {
	plansza->status = Przegrana;
	
	// Pokaż pozostałe bomby
	for (int i = 0; i < plansza->height * plansza->width; i++) {
		if (plansza->pola[i].jest_bomba) {
			plansza->pola[i].sprawdzone_pole = true;
		}
	}
}

void sprawdz_wygrana(Plansza *plansza) {
	for (int i = 0; i < plansza->height * plansza->width; i++) {
		Plansza_pole *pole = &plansza->pola[i];
		if (pole->jest_bomba == false && pole->sprawdzone_pole == false) {
			return;
		}
	}
	plansza->status = Wygrana;
}