#pragma once

// Inclusione delle librerie necessarie
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <SDL_image.h>


class DisegnaContenuti {
public:

    // Funzioni per la creazione di contenuti
    static void scriviScritta(std::string str, SDL_Renderer* gRenderer, int x, int y, int grandezza);
    static void scriviScrittaPersonalizzata(std::string str, SDL_Renderer* gRenderer, int x, int y, int grandezza, int rosso, int verde, int blu);
    static void disegnaBottone(SDL_Renderer* gRenderer, std::string percorso, int x, int y, int lunghezza, int larghezza);
    static void disegnaSfondo(SDL_Renderer* renderer, const char* imagePath, SDL_Window* gWindow);
   
    static void scriviScrittaGradualmente(SDL_Renderer* renderer, const std::string& fontPath, const std::string& text, int x, int y, int delay);

};
