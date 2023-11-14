#pragma once
#include <SDL.h>
#include <string>
#include <iostream>


class CampoBattaglia
{
public:
    static const int SCREEN_WIDTH = 1500;
    static const int SCREEN_HEIGHT = 600;
    static const int CELL_SIZE = 70;
    static const int GRID_OFFSET_X = 900;
    static const int GRID_OFFSET_Y = 0;
    static const int GRID_ROWS = 8;
    static const int GRID_COLS = 8;

public:
    static void disegnaGriglia(SDL_Renderer* gRenderer, SDL_Texture* mareTexture);
    static bool cellaCliccata[GRID_ROWS][GRID_COLS];
    static bool gestisciInput(SDL_Event& e);
    static std::string ottieniCellaCliccata(SDL_Event& e);
};