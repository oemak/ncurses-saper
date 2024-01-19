#include <iostream>
#include <ncursesw/curses.h>

#include "kolory.h"
#include "draw/draw.h"
#include "status.h"
#include "gracore/restart.h"

using namespace std;

int main(void) {
	initscr();
	
	// Przypisanie domyślnych opcji	
	status_gry *status = new status_gry;
	status->page = Mmenu;
	status->page_selection = 0;
	Plansza *plansza = new Plansza;
	status->plansza = plansza;
	plansza->status = Czeka;
	plansza->width = 40;
	plansza->height = 20;
	plansza->miny = 99;
	plansza->ile_min_zostalo = 99;
	plansza->pole_now = plansza->width / 2;
	plansza->pola = nullptr;
	restart_gry(plansza);
	
	timeout(60); // Czeka na getch() 
	noecho(); // Input nie wyświetla się na ekranie
	cbreak(); // Input nie czeka na enter
	keypad(stdscr, TRUE); // Użycie specjalnych klaiwszy
	init_colorpairs(); // Inicjalizacja kolorów
	curs_set(0); // Niewidzialny kursor

	// Oczekiwanie na input użytkownika
	draw(status, 0);   
	draw_loop(status); 
    
    endwin();
	
	// Zwalnianie pamięci
	delete(plansza->pola);
	delete(plansza);
	delete(status);
	return 0;
}