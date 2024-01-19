#include <ncursesw/curses.h>
#include <iostream>
#include <string>

#include "wysrodkowanie.h"
#include "strony.h"
#include "../napisy.h"
#include "../status.h"

int draw_mmenu(status_gry *status, int x) {
	// Mapowanie sterowania po main menu
	switch (x) {
		case KEY_DOWN: {
			if (status->page_selection != 4) {
				status->page_selection++;
			} else {
				beep();
			}
			break;
		}
		case KEY_UP: {
			if (status->page_selection != 0) {
				status->page_selection--;
			} else {
				beep();
			}
			break;
		}
		case KEY_ENTER: {
			clear();
			switch (status->page_selection) {
				case 0: {
					status->page = Graj;
					status->page_selection = 0;
					return draw_gra(status, 0);
				}
				case 1: {
					status->page = Opcje;
					status->page_selection = 0;
					return draw_opcje(status, 0);
				}
				case 2: { // Wyjście z programu
					return 1;
				}
			}
			break;
		}
		case 27: // ESC - wyjście z programu
			return 1;	
		case 0:
			break;
		case -1:
			return 0;
		default:
			beep(); // Wcisnął nieodpowiedni przycisk? Beep
	}
	
	// Pozycjonowanie przycisków i splash artu
	int mv = 0;
	
	attron(A_BOLD | COLOR_PAIR(5));
	if (COLS > 50 && LINES > 18) {
		for (int i = 0; i < 8; i++) {
			const char *splash = mmenu_splash[i];
			mvprintw(centery() - 7 + i, centerx(splash), splash);
			mv = 5;
		}
	} else { // Jeżeli okno jest za małe na wyświetlenie splash artu, wyświetla sam tekst
		mvprintw(centery() - 7, centerx(mmenu_splash_text), mmenu_splash_text);
		mv = 2;
	}
	
	for (int i = 0; i < 3; i++) {
		if (status->page_selection == i) attron(A_STANDOUT);
		mvprintw(centery() + i + mv, centerx(mmenu_buttons[i]), mmenu_buttons[i]);
		if (status->page_selection == i) attroff(A_STANDOUT);
	}
	attroff(A_BOLD | COLOR_PAIR(5));
	
	return 0;
}
