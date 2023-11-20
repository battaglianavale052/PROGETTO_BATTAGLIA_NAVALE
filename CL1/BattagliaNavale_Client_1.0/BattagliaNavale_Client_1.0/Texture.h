#pragma once

#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Nave.h"
#include "Campo.h"

class Texture {
public:
    // Costruttore
    Texture(SDL_Renderer* gRenderer);

    // Riempie il vettore naveTexture di texture
    static void riempiVettoreTextureNavi(SDL_Renderer* gRenderer);

    // Carica una texture da file
    static SDL_Texture* caricaTextureDaFile(SDL_Renderer* renderer, const std::string& filename);

    // Disegna la texture di una nave
    static void disegnaTextureNave(int i, Nave* nave, int x_, int y_, SDL_Renderer* gRenderer);

    // Carica la texture del mare
    static SDL_Texture* CaricaTextureMare(const char* path, SDL_Renderer* gRenderer);

    // Restituisce la texture del vettore alla posizione i
    static SDL_Texture* GetTextureVettore(int i);

    // Disegna il vettore di texture delle navi
    void disegnaVettoreTexture(int i, std::vector<Nave> navi);

private:
    static std::vector<SDL_Texture*> naveTexture;
};
