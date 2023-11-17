#pragma once

// Inclusione delle librerie necessarie
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <SDL_image.h>

#include "Nave.h"


class DisegnaContenuti {
public:

    // Funzioni per la creazione di contenuti
        static void scriviScritta(std::string str, SDL_Renderer* gRenderer, int x, int y, int grandezza);
        static void scriviScrittaPersonalizzata(std::string str, SDL_Renderer* gRenderer, int x, int y, int grandezza, int rosso, int verde, int blu);
        static void disegnaBottone(SDL_Renderer* gRenderer, std::string percorso, int x, int y, int lunghezza, int larghezza);
        static void disegnaSfondo(SDL_Renderer* renderer, const char* imagePath, SDL_Window* gWindow);
   
    //non funzionante da finire
        static void scriviScrittaGradualmente(SDL_Renderer* renderer, const std::string& fontPath, const std::string& text, int x, int y, int delay);

    //funziona che richiamano funzioni 
        void richiamoContenutiFuoco(SDL_Texture* mareTexture, std::vector<Nave> navi); //viene richiamata prima di iniziare il combattiemnto vero e proprio
        void richiamoContenutiPosizionamentoNave(SDL_Texture* mareTexture, std::vector<Nave> navi, std::vector<std::string> testiNave, int i); //viene richiamata durante il posizionamento delle navi

};
