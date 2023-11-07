#pragma once
//LIBRERIA
    #include <SDL.h>

//CLASSI
    #include "Nave.h"
    #include "Campo.h"
    #include "NaviVettore.h"

class InterazioniUtente
{
public: 

    //CONTROLLO MOUSE UTENTE:
        static void gestisciNave(Nave* nave, SDL_Texture* mareTexture, std::vector<Nave> navi, int i);
        static void gestisciEventi(SDL_Event& evento, bool& staPosizionandoNave, bool& esciDaNave, int& x_, int& y_, Nave* nave);
        static void gestisciEventoMouseDown(SDL_Event& evento, bool& staPosizionandoNave, int& x_, int& y_, Nave* nave);
        static void gestisciEventoMouseMotion(SDL_Event& evento, bool& staPosizionandoNave, int& x_, int& y_, Nave* nave);
        static void gestisciEventoMouseUp(SDL_Event& evento, bool staPosizionandoNave, bool& esciDaNave, int x_, int y_, Nave* nave);
        static void rendiSuBuffer(SDL_Texture* bufferTexture, SDL_Texture* mareTexture, const std::vector<Nave>& navi, int i, Nave* nave);
        static void disegnaNavi(std::vector<Nave> navi, int i, Nave* nave);
        static void disegnaCampoEMessaggi(SDL_Texture* mareTexture, const std::vector<Nave>& navi, int i);

};

