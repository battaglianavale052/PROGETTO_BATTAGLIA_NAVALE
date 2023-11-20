#pragma once

// Librerie
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <SDL_image.h>

// Classi
#include "Nave.h"

// Classi
class DisegnaContenuti {
public:
    // Funzioni per la creazione di contenuti

    // Scrivi una scritta standard
    static void scriviScritta(std::string str, SDL_Renderer* gRenderer, int x, int y, int grandezza);

    // Scrivi una scritta con personalizzazione dei colori
    static void scriviScrittaPersonalizzata(std::string str, SDL_Renderer* gRenderer, int x, int y, int grandezza, int rosso, int verde, int blu);

    // Disegna un bottone
    static void disegnaBottone(SDL_Renderer* gRenderer, std::string percorso, int x, int y, int lunghezza, int larghezza);

    // Disegna uno sfondo
    static void disegnaSfondo(SDL_Renderer* renderer, const char* imagePath, SDL_Window* gWindow);

    // Scrivi una scritta gradualmente (non funzionante, da finire)
    static void scriviScrittaGradualmente(SDL_Renderer* renderer, const std::string& fontPath, const std::string& text, int x, int y, int delay);

    // Richiamo dei contenuti per la fase di combattimento
    void richiamoContenutiFuoco(SDL_Texture* mareTexture, std::vector<Nave> navi);

    // Richiamo dei contenuti durante il posizionamento delle navi
    void richiamoContenutiPosizionamentoNave(SDL_Texture* mareTexture, std::vector<Nave> navi, std::vector<std::string> testiNave, int i);

    // Funzione per disegnare un rettangolo nero
    static void rettangoloNero(SDL_Renderer* renderer);
};
