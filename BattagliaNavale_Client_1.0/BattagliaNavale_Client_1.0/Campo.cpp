#pragma once
#include "Campo.h"

const int Campo::SCREEN_WIDTH = 1500;
const int Campo::SCREEN_HEIGHT = 600;
const int Campo::CELL_SIZE = 70;

SDL_Window* Campo::gWindow = nullptr;
SDL_Renderer* Campo::gRenderer = nullptr;

//LIBRERIA
    bool Campo::initSDL() {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
            return false;
        }

        gWindow = SDL_CreateWindow("Battaglia Navale", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (gWindow == NULL) {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            return false;
        }

        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

        if (gRenderer == NULL) {
            printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
            return false;
        }
   
        if (TTF_Init() == -1) {
            printf("Impossibile inizializzare SDL_ttf! Errore: %s\n", TTF_GetError());
            return false;
        }

        return true;
    }
    void Campo::closeSDL() {
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);
        gWindow = NULL;
        gRenderer = NULL;
        SDL_Quit();
    }

//CAMPO
    Campo::Campo()
    {
    }


void Campo::coloraFinestraDiNero(SDL_Renderer* renderer) {
    // Imposta il colore del renderer a nero
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Crea un rettangolo che copre l'intera finestra
    SDL_Rect schermoNero = { 0, 0, 1500, 600}; // Assumi che larghezzaFinestra e altezzaFinestra siano le dimensioni della finestra

    // Riempie l'intera finestra con il colore nero
    SDL_RenderFillRect(renderer, &schermoNero);

    // Aggiorna il renderer per rendere effettive le modifiche
    SDL_RenderPresent(renderer);
}

void Campo::coloraFinestraDiBianco(SDL_Renderer* renderer) {
    // Imposta il colore del renderer a nero
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Crea un rettangolo che copre l'intera finestra
    SDL_Rect schermoNero = { 0, 0, 1500, 600 }; // Assumi che larghezzaFinestra e altezzaFinestra siano le dimensioni della finestra

    // Riempie l'intera finestra con il colore nero
    SDL_RenderFillRect(renderer, &schermoNero);

    // Aggiorna il renderer per rendere effettive le modifiche
    SDL_RenderPresent(renderer);
}

void Campo::visualizzaCampo(SDL_Texture* mareTexture, const std::vector<Nave>& navi) {
    // Imposta lo sfondo
    impostaSfondo(gRenderer);

    // Disegna la griglia e il mare
    disegnaGriglia(CELL_SIZE, gRenderer, mareTexture);

    // Aggiorna il renderer
    SDL_RenderPresent(gRenderer);
}

void Campo::disegnaGriglia(int CELL_SIZE, SDL_Renderer* gRenderer, SDL_Texture* mareTexture){
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            SDL_Rect cellRect = {
                col * CELL_SIZE,
                row * CELL_SIZE,
                CELL_SIZE,
                CELL_SIZE
            };
            SDL_RenderCopy(gRenderer, mareTexture, NULL, &cellRect);
            //SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
            SDL_RenderDrawRect(gRenderer, &cellRect);
        }
    }
}

void Campo::impostaSfondo(SDL_Renderer* gRenderer) {
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
}
