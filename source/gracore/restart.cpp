#include "../status.h"

void restart_gry(Plansza *plansza) {
	plansza->status = Czeka;
	plansza->ile_min_zostalo = plansza->miny;
	
	// Usuwa istniejącą plansze i tworzy nową
	if (plansza->pola != nullptr) {
		delete plansza->pola;
	}
	plansza->pola = new Plansza_pole[plansza->height * plansza->width];
	for (int i = 0; i < plansza->height * plansza->width; i++) {
		Plansza_pole *pole = &plansza->pola[i];
		pole->ile_bomb = 0;
		pole->jest_bomba = false;
		pole->sprawdzone_pole = false;
		pole->oznaczone_pole = false;
	} 
}