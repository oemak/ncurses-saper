#include <ncursesw/curses.h>

#include "../status.h"

// Logika ruchu po planszy, if'y sprawdzają czy gracz nie próbuje wyjechać poza plansze
void ruch_gora(Plansza *plansza) {
	if (plansza->pole_now >= plansza->width) {
		plansza->pole_now -= plansza->width;
	} else {
		beep(); // Próbuje wyjechać poza plansze? Beep
	}
}

void ruch_dol(Plansza *plansza) {
	if (plansza->pole_now < plansza->width * (plansza->height - 1)) {
		plansza->pole_now += plansza->width;
	} else {
		beep(); // Próbuje wyjechać poza plansze? Beep
	}
}

void ruch_prawo(Plansza *plansza) {
	if ((plansza->pole_now + 1) % plansza->width > 0) {
		plansza->pole_now++;
	} else {
		beep(); // Próbuje wyjechać poza plansze? Beep 
	}
}

void ruch_lewo(Plansza *plansza) {
	if (plansza->pole_now % plansza->width > 0) {
		plansza->pole_now--;
	} else {
		beep(); // Próbuje wyjechać poza plansze? Beep
	}
}