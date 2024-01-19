#include <ncursesw/curses.h>

#include "../status.h"
#include "../napisy.h"
#include "wysrodkowanie.h"
#include "strony.h"
#include "../gracore/input.h"
#include "../gracore/restart.h"

void draw_pasek(int g, int l, Plansza *plansza) { // góra, lewo
	attron(A_BOLD);
	mvprintw(g, l, "%03d", plansza->ile_min_zostalo);
	attroff(A_BOLD);
	int s = (int)(COLS / 2); // Wycentrowanie tekstu
	switch(plansza->status) {
		case Wygrana: {
			mvaddstr(g, s - 7, "WYGRALES!");
			break;
		}
		case Przegrana: {
			mvaddstr(g, s - 7, "PRZEGRALES :(");
			break;
		}
		case Gra:
		case Czeka: {
			mvaddstr(g, s - 7, "              ");
			break;
		}
	}
}

int draw_gra(status_gry *status, int x) {
	Plansza *plansza = status->plansza;
	int g = centery() - plansza->height / 2 - 1;
	int l = (int)(COLS / 2) - plansza->width;
	
	draw_pasek(g, l, plansza);
	
	switch(x) {
		case 27: { // ESC, wraca do main menu
			clear();
			restart_gry(status->plansza);
			status->page = Mmenu;
			status->page_selection = 0;
			return draw_mmenu(status, 0);
		}
	}
	
	gra_input(status, x); // Wdraża input do gry
	
	
	// Rysowanie planszy
	attron(A_BOLD);
	for (int i = 0; i < plansza->width * plansza->height; i++) {
		int x = l + i % plansza->width * 2;
		int y = g + 1 + i / plansza->width;
		if (plansza->pole_now == i) {
			attron(A_STANDOUT);
		}
		Plansza_pole *pole = &plansza->pola[i];
		if (pole->oznaczone_pole != true) {
			if (pole->sprawdzone_pole != true) {
				attroff(A_BOLD);
				mvaddch(y, x, '-');
				attron(A_BOLD);
			} else {
				if (pole->jest_bomba) {
					attron(COLOR_PAIR(3));
					mvaddch(y, x, 'X');
					attroff(COLOR_PAIR(3));
				} else if (pole->ile_bomb > 0) {
					int ile = pole->ile_bomb;
					attron(COLOR_PAIR(ile));
					mvaddch(y, x, '0' + ile);
					attroff(COLOR_PAIR(ile));
				} else {
					mvaddch(y, x, ' ');
				}
			}
		} else {
			attron(A_STANDOUT);
			if (plansza->status != Przegrana) {
				mvaddch(y, x, 'X');
			} else {
				if (plansza->pola[i].jest_bomba == true) {
					mvaddch(y, x, 'X');
				} else {
					attron(COLOR_PAIR(5));
					mvaddch(y, x, 'X');
					attroff(COLOR_PAIR(5));
				}
			}
			attroff(A_STANDOUT);
		}
		if (plansza->pole_now == i) {
			attroff(A_STANDOUT);
		}
	}
	attroff(A_BOLD);
	
	return 0;
}