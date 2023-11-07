#pragma once

#include "Nave.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "DisegnaContenuti.h"
#include <vector>
#include <string>
#include "SDL_image.h"
#include "Texture.h"

class Campo {
public:
    static const int SCREEN_WIDTH;
    static const int SCREEN_HEIGHT;
    static const int CELL_SIZE;
    static SDL_Window* gWindow;
    static SDL_Renderer* gRenderer;

    // Libreria
    static void closeSDL();
    static bool initSDL();
    // Fine libreria

    // Costruttore
    Campo();

    // Metodo per gestire il mouse sulla nave
    static void mouseNave(Nave* nave, SDL_Texture* mareTexture, std::vector<Nave> navi, SDL_Texture* naveTexture);



    // Metodo per colorare la finestra di nero
    static void coloraFinestraDiNero(SDL_Renderer* renderer);

    // Metodo per visualizzare il campo
    static void visualizzaCampo(SDL_Texture* mareTexture, const std::vector<Nave>& navi);

    // Metodo per visualizzare il vettore di navi
    static void visualizzaVettore(std::vector<Nave>& navi, SDL_Renderer* gRenderer);

    // Metodo per disegnare la griglia
    static void disegnaGriglia(int CELL_SIZE, SDL_Renderer* gRenderer, SDL_Texture* mareTexture);

    // Metodo per impostare lo sfondo
    static void impostaSfondo(SDL_Renderer* gRenderer);

    //carica texture mare
    static SDL_Texture* CaricaTextureMare(const char* path);
};
