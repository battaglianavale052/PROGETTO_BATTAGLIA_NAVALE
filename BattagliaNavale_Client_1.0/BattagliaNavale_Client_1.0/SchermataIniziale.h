#pragma once
//LIBRERIE
	#include <SDL.h>
	#include <SDL_image.h>


class SchermataIniziale
{
public:

	static void disegnaSfondo(SDL_Renderer* renderer, const char* imagePath, SDL_Window* gWindow);
	
};

