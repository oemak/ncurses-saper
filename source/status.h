#ifndef STATUS_H
#define STATUS_H

enum DrawPage {
	Mmenu,
	Graj,
	Opcje	
};

enum GameStatus {
	Czeka,
	Gra,
	Wygrana,
	Przegrana
};

struct Plansza_pole {
	bool oznaczone_pole;
	bool sprawdzone_pole;
	bool jest_bomba;
	int ile_bomb;
};

struct Plansza {
	int width;
	int height;
	int pole_now; // x = pole_now % width | y = pole_now / width
	int miny;
	int ile_min_zostalo;
	GameStatus status;
	Plansza_pole *pola; // Tablica trzymająca wartość każdego pola | zakres tablicy: width * height
};

struct status_gry {
	DrawPage page;
	int page_selection;
	Plansza *plansza;
};

#endif
