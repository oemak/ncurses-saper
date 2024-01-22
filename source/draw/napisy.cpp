
// char * zamiast std::string dlatego, że ncurses narzuca użycie char * jako argument w niektórych funkcjach
 
const char *mmenu_splash[8] = {
        " $$$$$$\\   $$$$$$\\  $$$$$$$\\  $$$$$$$$\\ $$$$$$$\\  ",
        "$$  __$$\\ $$  __$$\\ $$  __$$\\ $$  _____|$$  __$$\\ ",
        "$$ /  \\__|$$ /  $$ |$$ |  $$ |$$ |      $$ |  $$ |",
        "\\$$$$$$\\  $$$$$$$$ |$$$$$$$  |$$$$$\\    $$$$$$$  |",
        " \\____$$\\ $$  __$$ |$$  ____/ $$  __|   $$  __$$< ",
        "$$\\   $$ |$$ |  $$ |$$ |      $$ |      $$ |  $$ |",
        "\\$$$$$$  |$$ |  $$ |$$ |      $$$$$$$$\\ $$ |  $$ |",
        " \\______/ \\__|  \\__|\\__|   \\________|\\__|  \\__|"
};

const char *mmenu_splash_text = "SAPER";
const char *mmenu_buttons[3] = {"GRAJ", "OPCJE", "WYJSCIE"};

const char *opcje_tytul = "OPCJE";
const char *opcje_width = "Szerokosc planszy:";
const char *opcje_height = " Wysokosc planszy:";
const char *opcje_ilemin = "  Ilosc min:";
const char *opcje_wroc = "Cofnij";