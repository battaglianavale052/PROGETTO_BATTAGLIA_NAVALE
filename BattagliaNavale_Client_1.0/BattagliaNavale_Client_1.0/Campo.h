#pragma once

//LIBRERIE
    #include <SDL.h>
    #include <SDL_ttf.h>
    #include <vector>
    #include <string>
    #include "SDL_image.h"
//CLASSI
    #include "Nave.h"
    #include "DisegnaContenuti.h"
    #include "Texture.h"
    #include "NaviVettore.h"

class Campo {
public:
    static const int SCREEN_WIDTH;
    static const int SCREEN_HEIGHT;
    static const int CELL_SIZE;
    static SDL_Window* gWindow;
    static SDL_Renderer* gRenderer;

    //LIBRERIA
        static void closeSDL();
        static bool initSDL();

    //COSTRUTTORE
        Campo();


    //DISEGNARE IL CAMPO E LE SUE COMPONENTI
        // Metodo per colorare la finestra di nero
        static void coloraFinestraDiNero(SDL_Renderer* renderer);
        // Metodo per visualizzare il campo
        static void visualizzaCampo(SDL_Texture* mareTexture, const std::vector<Nave>& navi);
        // Metodo per disegnare la griglia
        static void disegnaGriglia(int CELL_SIZE, SDL_Renderer* gRenderer, SDL_Texture* mareTexture);
        // Metodo per impostare lo sfondo
        static void impostaSfondo(SDL_Renderer* gRenderer);

};
