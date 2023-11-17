#pragma once
#include <vector>
#include <string>
#include "Nave.h"
#include <SDL.h>
class NaviVettore
{
public:

    //GESTIONE VETTORE DI NAVI
    static void riempiVettoreTestoNave(std::vector<std::string>& vett);

    static void riempiVettoreNaviTemporanee(std::vector<Nave> navi);

    static void visualizzaVettore(std::vector<Nave>& navi, SDL_Renderer* gRenderer);
};

