#include <ncursesw/curses.h>

#include "../status.h"
#include "napisy.h"
#include "strony.h"

int draw(status_gry *status, int x) {
	int r = 0; // return
	
	// Mapowanie klawiszy
	switch(x) {
		case 'w':
		case 'W':
			x = KEY_UP;
			break;
		case 's':
		case 'S':
			x = KEY_DOWN;
			break;
		case 'a':
		case 'A':
			x = KEY_LEFT;
			break;
		case 'd':
		case 'D':
			x = KEY_RIGHT;
			break;
		case 10:
		case ' ':
			x = KEY_ENTER;
			break;
	}
	
	// Rysowanie w zależności od wybranej strony
	switch(status->page) {
		case Mmenu: {
			r = draw_mmenu(status, x);
			break;
		}
		case Graj: {
			r = draw_gra(status, x);
			break;
		}
		case Opcje: {
			r = draw_opcje(status, x);
			break;
		}
		default:
			return 1;
	}
	
	// Wymiary okna w prawym dolnym rogu
	if (LINES < (status->plansza->height + 1) || LINES < 17 | COLS / 2 < (status->plansza->width) || COLS < 20) attron(COLOR_PAIR(3));
	mvprintw(LINES - 1, COLS - 7, "%03dx%03d", COLS/2, LINES);
	if (LINES < (status->plansza->height + 1) || LINES < 17 | COLS / 2 < (status->plansza->width) || COLS < 20) attroff(COLOR_PAIR(3));
	
	
	refresh();
	return r;
}

// Loop wywołuje się na samym początku programu, czekając na jakikolwiek input gracza 
void draw_loop(status_gry *status) {
	int x = 0;
	while ((x = getch())) {
		if (draw(status, x) != 0) {
			break;
		}
	}
}