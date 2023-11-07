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
//FINE LIBRERIA
//CAMPO
Campo::Campo()
{
}
//FINE CAMPO
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
void Campo::visualizzaCampo(SDL_Texture* mareTexture, const std::vector<Nave>& navi) {
    // Imposta lo sfondo
    impostaSfondo(gRenderer);

    // Disegna la griglia e il mare
    disegnaGriglia(CELL_SIZE, gRenderer, mareTexture);

    // Aggiorna il renderer
    SDL_RenderPresent(gRenderer);
}
void Campo::visualizzaVettore(std::vector<Nave>& navi, SDL_Renderer* gRenderer) {
    for (int i = 0; i < navi.size(); i++) {
        navi[i].render(gRenderer);
    }
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
void Campo::mouseNave(Nave* nave, SDL_Texture* mareTexture, std::vector<Nave> navi, SDL_Texture* naveTexture) {
    bool isNaveBeingPlaced = false;
    bool quitNave = false; // Aggiunto un quitNave separato per la gestione di ciascuna nave
    SDL_Event e;
    int controllo = 1;
    int x_ = nave->getX(), y_ = nave->getY();
    while (!quitNave) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quitNave = true;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (e.button.button == SDL_BUTTON_LEFT) {
                    if (!isNaveBeingPlaced) {
                        isNaveBeingPlaced = true;
                        int cellX = e.button.x / CELL_SIZE;
                        int cellY = e.button.y / CELL_SIZE;
                        int naveX = cellX * CELL_SIZE;
                        int naveY = cellY * CELL_SIZE;
                        nave->setPosizione(naveX, naveY);
                        x_ = naveX; 
                        y_ = naveY;
                    }
                }
            }
            if (e.type == SDL_MOUSEMOTION) {
                if (isNaveBeingPlaced) {
                    int cellX = e.button.x / CELL_SIZE;
                    int cellY = e.button.y / CELL_SIZE;
                    int naveX = cellX * CELL_SIZE;
                    int naveY = cellY * CELL_SIZE;
                    nave->setPosizione(naveX, naveY);
                    x_ = naveX;
                    y_ = naveY;
                }
            }
            if (e.type == SDL_MOUSEBUTTONUP) {
                if (controllo != 1) {
                    if (e.button.button == SDL_BUTTON_LEFT) {       
                        if (x_ < 0 || x_ > 559 || y_ < 0 || y_ > 559) {
                            //nave posizionata male
                        }
                        else {
                            isNaveBeingPlaced = false;
                            quitNave = true;
                        }
                    }
                }
                controllo++;
            }
        }

        impostaSfondo(gRenderer);
        SDL_RenderClear(gRenderer);
        disegnaGriglia(CELL_SIZE, gRenderer, mareTexture);
        DisegnaContenuti::scriviScritta("PIAZZA LA TUA NAVE");
        nave->render(gRenderer);
        SDL_RenderPresent(gRenderer);

        Texture::disegnaTextureNave(naveTexture, nave, x_, y_);

        visualizzaVettore(navi, gRenderer);
        SDL_RenderPresent(gRenderer);
    }
}

void Campo::impostaSfondo(SDL_Renderer* gRenderer) {
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
}
SDL_Texture* Campo::CaricaTextureMare(const char* path) {
    // Carica l'immagine del mare
    SDL_Surface* mareSurface = SDL_LoadBMP(path);

    if (mareSurface == NULL) {
        printf("Impossibile caricare l'immagine del mare! SDL Error: %s\n", SDL_GetError());
        return nullptr; // Restituisci nullptr per indicare che la creazione della texture ha fallito.
    }

    // Converti la superficie in formato RGBA8888
    mareSurface = SDL_ConvertSurfaceFormat(mareSurface, SDL_PIXELFORMAT_RGBA8888, 0);

    // Crea una texture dal mareSurface utilizzando il renderer
    SDL_Texture* mareTexture = SDL_CreateTextureFromSurface(Campo::gRenderer, mareSurface);

    SDL_FreeSurface(mareSurface);

    if (mareTexture == NULL) {
        printf("Impossibile creare la texture del mare! SDL Error: %s\n", SDL_GetError());
        return nullptr;
    }

    return mareTexture; // Restituisci la texture del mare creata con successo
}