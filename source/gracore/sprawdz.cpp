#include <ncursesw/curses.h>

#include "../status.h"
#include "inicjalizacja.h"
#include "gameresult.h"
#include "pobliskiepola.h"

void sprawdz_pole(Plansza *plansza) {
	if (plansza->status == Czeka) { // Zaczyna gre na polu, które wybierze gracz
		//plansza->status = Gra;
		zainicjalizuj_gre(plansza);
	} else if (plansza->status == Gra) {
		Plansza_pole *pole = &plansza->pola[plansza->pole_now];
		if (pole->oznaczone_pole != true) { // Nie jest oznaczone
			if (pole->sprawdzone_pole != true) { // Nie jest sprawdzone
				pole->sprawdzone_pole = true;
				if (pole->jest_bomba == true) {
					przegrana(plansza);
				} else if (pole->ile_bomb == 0) { // Sprawdza pobliskie pola jeżeli nie ma żadnej bomby wokół
					sprawdz_pobliskie_pola(plansza, plansza->pole_now);
				}
			} else {
				// Liczy ile pobliskich pól jest oznaczone
				int *pobliskie = spisz_pobliskie_pola(plansza, plansza->pole_now);
				int ile_oznaczonych = 0;
				for (int i = 0; i <= 8; i++) {
					int pob_pole = pobliskie[i];
					if (pob_pole != plansza->pole_now && plansza->pola[pob_pole].oznaczone_pole == true) {
						ile_oznaczonych++;
					}
				}
				delete pobliskie;
				
				// Jeżeli wszystkie pobliskie miny są oznaczone to sprawdza reszte pól
				if (ile_oznaczonych == pole->ile_bomb) {
					sprawdz_pobliskie_pola(plansza, plansza->pole_now);
				}
			}
		}
	} else { // Beep jeżeli próbuje sprawdzić oznaczone pole
		beep();
	}
}