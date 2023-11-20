#pragma once
// Librerie
#include <SDL.h>
#include <string>
#include <iostream>

class CampoBattaglia {
public:
    // Dimensioni e configurazioni dello schermo e della griglia
    static const int SCREEN_WIDTH = 1500;
    static const int SCREEN_HEIGHT = 600;
    static const int CELL_SIZE = 70;
    static const int GRID_OFFSET_X = 900;
    static const int GRID_OFFSET_Y = 0;
    static const int GRID_ROWS = 8;
    static const int GRID_COLS = 8;

public:
    // Metodi per disegnare il campo e gestire l'input

    // Metodo per disegnare la griglia e casella rossa
    static void disegnaGriglia(SDL_Renderer* gRenderer, SDL_Texture* mareTexture);

    // Metodo per disegnare la griglia e casella verde o un'altro colore 
    static void disegnaGrigliaVerde(SDL_Renderer* gRenderer, int row, int col, int _1, int _2, int _3);

    // Variabili per il controllo del clic del mouse su ciascuna cella
    static bool cellaCliccata[GRID_ROWS][GRID_COLS];

    // Metodo per gestire l'input del mouse
    static bool gestisciInput(SDL_Event& e);

    // Metodo per ottenere la posizione della cella cliccata
    static std::string ottieniCellaCliccata(SDL_Event& e);
};
