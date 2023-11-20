#pragma once

#include <vector>
#include <string>
#include "Nave.h"
#include <SDL.h>

class NaviVettore {
public:
    // GESTIONE VETTORE DI NAVI

    // Riempi il vettore con i testi delle navi
    static void riempiVettoreTestoNave(std::vector<std::string>& vett);

    // Riempi un vettore temporaneo con le navi
    static void riempiVettoreNaviTemporanee(std::vector<Nave> navi);

    // Visualizza il vettore di navi sul renderer
    static void visualizzaVettore(std::vector<Nave>& navi, SDL_Renderer* gRenderer);
};
