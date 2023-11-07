#pragma once

// Inclusione delle librerie necessarie
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <string>

class DisegnaContenuti {
public:

    // Funzioni per la creazione di contenuti
    static void scriviScritta(std::string str, SDL_Renderer* gRenderer);
    static void disegnaBottone(SDL_Renderer* gRenderer, std::string percorso, int x, int y, int lunghezza, int larghezza);
    // Funzione per gestire il click del bottone
    static int controlloClickBottone(int x, int x1, int y, int y1, int var, int x_, int x1_, int y_, int y1_, int var_);
};
