#pragma once

// Librerie
#include <SDL.h>

// Classi
#include "Nave.h"
#include "Campo.h"
#include "NaviVettore.h"
#include "InterazioniUtente.h"

class InterazioniUtente {
public:
    // Metodi per la gestione delle interazioni dell'utente

    // Gestione delle informazioni di una nave
    static std::string gestisciNave(Nave* nave, SDL_Texture* mareTexture, std::vector<Nave>& navi, int i);

    // Ottieni le coordinate di una nave in base alle coordinate del mouse
    static std::string ottieniCoordinateNave(int x, int y);

    // Controllo degli eventi del mouse per il posizionamento delle navi
    static void gestisciEventi(SDL_Event& evento, bool& staPosizionandoNave, bool& esciDaNave, int& x_, int& y_, Nave* nave);
    static void gestisciEventoMouseDown(SDL_Event& evento, bool& staPosizionandoNave, int& x_, int& y_, Nave* nave);
    static void gestisciEventoMouseMotion(SDL_Event& evento, bool& staPosizionandoNave, int& x_, int& y_, Nave* nave);
    static void gestisciEventoMouseUp(SDL_Event& evento, bool staPosizionandoNave, bool& esciDaNave, int x_, int y_, Nave* nave);
    static void rendiSuBuffer(SDL_Texture* bufferTexture, SDL_Texture* mareTexture, std::vector<Nave>& navi, int i, Nave* nave, int x_, int y_);
    static void disegnaNavi(std::vector<Nave> navi, int i, Nave* nave);
    static void disegnaCampoEMessaggi(SDL_Texture* mareTexture, const std::vector<Nave>& navi, int i);

    // Controllo generale del mouse per il click su un bottone
    static int controlloClickBottone(int x, int x1, int y, int y1, int var, int x_, int x1_, int y_, int y1_, int var_);
    static int controlloClickBottone(int x, int x1, int y, int y1, int var);

    // Rendering del testo su schermo
    static void renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y);

    // Lettura degli input da tastiera
    static std::string LeggiTastiera(SDL_Renderer* renderer, TTF_Font* font);
};

