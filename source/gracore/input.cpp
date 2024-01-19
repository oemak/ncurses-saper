#include <ncursesw/curses.h>

#include "../status.h"
#include "oznacz.h"
#include "restart.h"
#include "gameresult.h"
#include "ruch.h"
#include "pobliskiepola.h"
#include "sprawdz.h"

// Mapowanie sterowania podczas gry 
void gra_input(status_gry *status, int x) {
	Plansza *plansza = status->plansza;
	switch(x) {
		case KEY_UP: {
			ruch_gora(plansza);
			break;
		}
		case KEY_DOWN: {
			ruch_dol(plansza);
			break;
		}
		case KEY_RIGHT: {
			ruch_prawo(plansza);
			break;
		}
		case KEY_LEFT: {
			ruch_lewo(plansza);
			break;
		}
		case KEY_ENTER: {
			sprawdz_pole(plansza);
			sprawdz_wygrana(plansza);
			break;
		}
		case 'f':
		case 'F': {
			oznacz_pole(plansza);
			break;
		}
		case 'r':
		case 'R': {
			restart_gry(plansza);
			break;
		}
	}
}