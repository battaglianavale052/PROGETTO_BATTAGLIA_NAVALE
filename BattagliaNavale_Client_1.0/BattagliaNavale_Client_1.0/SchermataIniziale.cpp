#include "SchermataIniziale.h"


void SchermataIniziale::disegnaSfondo(SDL_Renderer* renderer, const char* imagePath, SDL_Window* gWindow) {

    SDL_Surface* imageSurface = IMG_Load(imagePath);

    SDL_Texture* backgroundImage = SDL_CreateTextureFromSurface(renderer, imageSurface);
    // Pulisce lo schermo
    SDL_RenderClear(renderer);

    // Disegna l'immagine come sfondo
    SDL_RenderCopy(renderer, backgroundImage, NULL, NULL);

    // Aggiorna la finestra
    SDL_RenderPresent(renderer);

    // Pulisce e rilascia le risorse
    SDL_DestroyTexture(backgroundImage);
    SDL_FreeSurface(imageSurface);
}

