#pragma once
//LIBRERIE
	#include <SDL.h>
	#include <SDL_image.h>
#include "Campo.h"
#include "DisegnaContenuti.h"
#include "InterazioniUtente.h"

class SchermataIniziale
{
public:

	static void disegnaSfondo(SDL_Renderer* renderer, const char* imagePath, SDL_Window* gWindow);
	static void dialogoEnome();
};

