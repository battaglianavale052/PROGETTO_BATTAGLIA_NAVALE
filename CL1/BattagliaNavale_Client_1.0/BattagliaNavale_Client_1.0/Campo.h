#pragma once

// Librerie
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <string>
#include "SDL_image.h"
#include <iostream>
#include <sstream>

// Classi
#include "Nave.h"
#include "DisegnaContenuti.h"
#include "Texture.h"
#include "NaviVettore.h"

class Campo {
public:
    // Dimensioni dello schermo
    static const int SCREEN_WIDTH;
    static const int SCREEN_HEIGHT;
    static const int CELL_SIZE;

    // Finestra e renderizzatore SDL
    static SDL_Window* gWindow;
    static SDL_Renderer* gRenderer;

    // Libreria SDL
    static void closeSDL();
    static bool initSDL();

    // Costruttore
    Campo();

    // Metodi per disegnare il campo e le sue componenti

    // Metodo per colorare la finestra di nero
    static void coloraFinestraDiNero(SDL_Renderer* renderer);

    // Metodo per colorare la finestra di bianco
    static void coloraFinestraDiBianco(SDL_Renderer* renderer);

    // Metodo per visualizzare il campo con le navi
    static void visualizzaCampo(SDL_Texture* mareTexture, const std::vector<Nave>& navi);

    // Metodo per disegnare la griglia
    static void disegnaGriglia(int CELL_SIZE, SDL_Renderer* gRenderer, SDL_Texture* mareTexture);

    // Metodo per impostare lo sfondo
    static void impostaSfondo(SDL_Renderer* gRenderer);

    // Metodo per cambiare la texture di una cella
    void cambiaTextureCella(const std::string& posizione, SDL_Texture* mareFuocoTexture);
};
