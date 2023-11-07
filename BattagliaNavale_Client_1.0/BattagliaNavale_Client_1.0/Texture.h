#pragma once
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Nave.h"
#include "Campo.h"
class Texture
{
public: 
	static std::vector<SDL_Texture*> riempiVettoreTextureNavi(SDL_Renderer* renderer);
	static SDL_Texture* caricaTextureDaFile(SDL_Renderer* renderer, const std::string& filename);
	static void disegnaTextureNave(SDL_Texture* naveTexture, Nave* nave, int x_, int y_);
};

