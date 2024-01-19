#include <ncursesw/curses.h>
#include <iostream>
#include <cstring> // ncurses narzuca użycie char * jako argument w niektórych funkcjach, dlatego <cstring> zamiast <string>

// Dokładne wyśrodkowanie tekstu w zależności od ilości znaków
int centerx(const char *i) {
	int len = strlen(i);
	int x = (int)(COLS / 2) - int(len / 2);
	if (x > 0) {
		return x;
	} else {
		return 0;
	}
}

int centery() {
	int y = (LINES / 2);
	return y;
}