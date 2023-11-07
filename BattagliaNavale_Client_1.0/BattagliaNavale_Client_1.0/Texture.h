#pragma once
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Nave.h"
class Texture
{
public: 

	Texture(SDL_Renderer* gRenderer);
	static void riempiVettoreTextureNavi(SDL_Renderer* gRenderer); //riempie il vettore naveTexture di texture
	static SDL_Texture* caricaTextureDaFile(SDL_Renderer* renderer, const std::string& filename);
	static void disegnaTextureNave(int i, Nave* nave, int x_, int y_,SDL_Renderer* gRenderer);
	//carica texture mare
	static SDL_Texture* CaricaTextureMare(const char* path, SDL_Renderer* gRenderer);

	static SDL_Texture* GetTextureVettore(int i);


private: 
	static  std::vector<SDL_Texture*> naveTexture;
};

