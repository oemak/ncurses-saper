#include <ncursesw/curses.h>

#include "../status.h"

void oznacz_pole(Plansza *plansza) {
	Plansza_pole *pole = &plansza->pola[plansza->pole_now];
	
	// Zmienna pomocna, żeby sprawdzić czy nie oznaczono wcześniej wszystkich możliwych min
	// oznaczone_pole = 0/1 | x = -1/1
	int x = pole->oznaczone_pole * 2 - 1;
	
	if (pole->sprawdzone_pole == false) {
		if (plansza->ile_min_zostalo + x >= 0) {
			plansza->ile_min_zostalo += x;
			pole->oznaczone_pole = !pole->oznaczone_pole; // Oznacza/odznacza pole jeżeli zostały jeszcze miny na planszy
		} else { 
			beep(); // Próbuje oznaczyć więcej pól niż zostało min? Beep
		}
	} else {
		beep(); // Próbuje oznaczyć sprawdzone pole? Beep
	}
}