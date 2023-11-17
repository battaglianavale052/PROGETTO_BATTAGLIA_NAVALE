#pragma once
//LIBRERIA
    #include <SDL.h>

//CLASSI
    #include "Nave.h"
    #include "Campo.h"
    #include "NaviVettore.h"
    
#include "InterazioniUtente.h"
class InterazioniUtente
{
public: 

    static std::string gestisciNave(Nave* nave, SDL_Texture* mareTexture, std::vector<Nave>& navi, int i);

    static std::string ottieniCoordinateNave(int x, int y);

    //CONTROLLO MOUSE UTENTE:
        //CONTROLLO POSIZIONAMENTO NAVI UTENTE
        static std::string  gestisciNave(Nave& nave, SDL_Texture* mareTexture, std::vector<Nave>& navi, int i);
        static void gestisciEventi(SDL_Event& evento, bool& staPosizionandoNave, bool& esciDaNave, int& x_, int& y_, Nave* nave);
        static void gestisciEventoMouseDown(SDL_Event& evento, bool& staPosizionandoNave, int& x_, int& y_, Nave* nave);
        static void gestisciEventoMouseMotion(SDL_Event& evento, bool& staPosizionandoNave, int& x_, int& y_, Nave* nave);
        static void gestisciEventoMouseUp(SDL_Event& evento, bool staPosizionandoNave, bool& esciDaNave, int x_, int y_, Nave* nave);
        static void rendiSuBuffer(SDL_Texture* bufferTexture, SDL_Texture* mareTexture, std::vector<Nave>& navi, int i, Nave* nave, int x_, int y_);
        static void rendiSuBuffer(SDL_Texture* bufferTexture, SDL_Texture* mareTexture, const std::vector<Nave>& navi, int i, const Nave& nave, int x_, int y_);
        static void rendiSuBuffer(SDL_Texture* bufferTexture, SDL_Texture* mareTexture, std::vector<Nave>& navi, int i, Nave* nave);
        static void disegnaNavi(std::vector<Nave> navi, int i, Nave* nave);
        static void disegnaCampoEMessaggi(SDL_Texture* mareTexture, const std::vector<Nave>& navi, int i);
        //CONTROLLO MOUSE GENERALE UTENTE
        static int controlloClickBottone(int x, int x1, int y, int y1, int var, int x_, int x1_, int y_, int y1_, int var_);
        static int controlloClickBottone(int x, int x1, int y, int y1, int var);

        static void renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y);

        //CONTROLLO TASTIERA UTENTE:
        static std::string LeggiTastiera(SDL_Renderer* renderer, TTF_Font* font);

};

