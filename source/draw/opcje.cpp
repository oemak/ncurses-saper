#include <ncursesw/curses.h>

#include "../status.h"
#include "napisy.h"
#include "strony.h"
#include "wysrodkowanie.h"

// Dwufyfrowy input, kompatybilny z ncurses
int cyfry_input (int line, int collumn) {
	move(line,collumn);
	clrtoeol();
	
	char input1, input2;
	int n = 0;
	
	// Input pierwszej cyfry
	attron(A_UNDERLINE);
	mvaddch(line, collumn, ' ');
	while ((input1 = getch())) {
		if(input1 >= '0' && input1 <= '9') {
			n = 10 * (input1 - '0'); // Liczba dziesiątek
			break;
		} else if (input1 > 0) {
			beep(); // Próbuje wpisać coś innego niż cyfra w zakresie 0-9? Beep
		}
	}
	attroff(A_UNDERLINE);
	mvaddch(line, collumn, input1);
	
	// Input drugiej cyfry
	attron(A_UNDERLINE);
	mvaddch(line, collumn + 1, ' ');
	while ((input2 = getch())) {
		if (input2 >= '0' && input2 <='9') {
			n += input2 - '0'; // Liczba jedności
			break;
		} else if (input2 > 0) {
			beep(); // Próbuje wpisać coś innego niż cyfra w zakresie 0-9? Beep
		}
	}
	attroff(A_UNDERLINE);
	
	return n;	
}

int draw_opcje(status_gry *status, int c) {
	// Mapowanie sterowanie po opcjach
	switch(c) {	
		case KEY_UP: {
			if (status->page_selection > 0) {
				status->page_selection--;
			} else {
				beep();
			}
			break;
		}
		case KEY_DOWN: {
			if (status->page_selection < 3) {
				status->page_selection++;
			} else {
				beep();
			}
			break;
		}
		case 10:
		case KEY_ENTER: {
			if (status->page_selection == 3) { // Wraca do main menu jeżeli gracz kliknął "Wróć"
				clear();
				status->page = Mmenu;
				status->page_selection = 1;
				return draw_mmenu(status, 0);
			}
			break;
		}
		case 0:
			break;
		case -1:
			return 0;
		default:
			beep(); // Wcisnął nieodpowiedni przycisk? Beep
	}

	// Pozycjonowanie przycisków
	int y = centery();
	
	attron(A_BOLD | COLOR_PAIR(1));
	mvaddstr(y - 3, centerx(opcje_tytul), opcje_tytul);
	attroff(A_BOLD);
	
	int x = (int)(COLS / 2);
	mvaddstr(y - 1, x - 10, opcje_width);
	mvaddstr(y, x - 10, opcje_height);
	mvaddstr(y + 1, x - 4, opcje_ilemin);
	
	if (status->page_selection == 0) attron(A_STANDOUT);
	mvprintw(y - 1, x + 9, "%02d", status->plansza->width);
	if (status->page_selection == 0) attroff(A_STANDOUT);
	
	if (status->page_selection == 1) attron(A_STANDOUT);
	mvprintw(y, x + 9, "%02d", status->plansza->height);
	if (status->page_selection == 1) attroff(A_STANDOUT);
	
	if (status->page_selection == 2) attron(A_STANDOUT);
	mvprintw(y + 1, x + 9, "%02d", status->plansza->miny);
	if (status->page_selection == 2) attroff(A_STANDOUT);
	
	if (status->page_selection == 3) attron(A_STANDOUT);
	mvaddstr(y + 3, centerx(opcje_wroc), opcje_wroc);
	if (status->page_selection == 3) attroff(A_STANDOUT);
	
	// Zmiana ustawień w zależności od tego co wybierze i ustawi gracz
	if (c == ' ' || c == 10 || c == KEY_ENTER) {
		int input = 0;
		switch (status->page_selection) {
			case 0: {
				while ((input = cyfry_input(y - 1, x + 9))) {
					if (status->plansza->miny < input * status->plansza->height - 8) { // Sprawdza czy miny zmieszczą się na ustawionej planszy
						break;
					} else {
						beep();
					}
				}
				status->plansza->width = input;
				attron(A_STANDOUT);
				mvprintw(y - 1, x + 9, "%02d", status->plansza->width);
				attroff(A_STANDOUT);
				break;
			}
			case 1: {
				while ((input = cyfry_input(y, x + 9))) {
					if (status->plansza->miny < status->plansza->width * input - 8) { // Sprawdza czy miny zmieszczą się na ustawionej planszy
						break;
					} else {
						beep();
					}
				}
				status->plansza->height = input;
				attron(A_STANDOUT);
				mvprintw(y, x + 9, "%02d", status->plansza->height);
				attroff(A_STANDOUT);
				break;
			}
			case 2: {
				while ((input = cyfry_input(y + 1, x + 9))) {
					if (input < status->plansza->width * status->plansza->height - 8) { // Sprawdcza czy ilość min nie przekracza ilości pól
						break;
					} else {
						beep();
					}
				}
				status->plansza->miny = input;
				status->plansza->ile_min_zostalo = input;
				attron(A_STANDOUT);
				mvprintw(y + 1, x + 9, "%02d", status->plansza->miny);
				attroff(A_STANDOUT);
				break;
			}
		}
		status->plansza->pole_now = status->plansza->width / 2;
	}
	attroff(COLOR_PAIR(1));
	
	return 0;
}