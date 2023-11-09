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

void SchermataIniziale::dialogoEnome()
{
    int x = 230;
    int y1 = 190;
    int y2 = 230;
    Campo::coloraFinestraDiNero(Campo::gRenderer);
    disegnaSfondo(Campo::gRenderer, "img/1.jpg", Campo::gWindow); //sfondo battaglia navale
    DisegnaContenuti::disegnaBottone(Campo::gRenderer, "img/2.bmp", Campo::SCREEN_WIDTH / 2 - 70, 400, 200, 200); //bottone start
    DisegnaContenuti::scriviScritta("BATTAGLIA NAVALE", Campo::gRenderer, 400, 30, 300);SDL_RenderPresent(Campo::gRenderer);
    while (InterazioniUtente::controlloClickBottone(680, 1080, 400, 600, 1) != 1) {}


    Campo::coloraFinestraDiBianco(Campo::gRenderer);
    DisegnaContenuti::disegnaBottone(Campo::gRenderer, "img/capitano.bmp", Campo::SCREEN_WIDTH / 2 - 300, 200, 400, 400); //capitano
    DisegnaContenuti::disegnaBottone(Campo::gRenderer, "img/dialogo.bmp", Campo::SCREEN_WIDTH / 8, 30, 400, 400); //dialogo
    DisegnaContenuti::scriviScrittaPersonalizzata("Sono il generale", Campo::gRenderer, x, y1, 115, 0,0,0); SDL_RenderPresent(Campo::gRenderer);
    DisegnaContenuti::scriviScrittaPersonalizzata("Adolfino", Campo::gRenderer, x, y2, 115, 0, 0, 0); SDL_RenderPresent(Campo::gRenderer);
    while (InterazioniUtente::controlloClickBottone(0, Campo::SCREEN_WIDTH, 0, Campo::SCREEN_HEIGHT, 1) != 1) {}


    Campo::coloraFinestraDiBianco(Campo::gRenderer);
    DisegnaContenuti::disegnaBottone(Campo::gRenderer, "img/capitano.bmp", Campo::SCREEN_WIDTH / 2 - 300, 200, 400, 400); //capitano
    DisegnaContenuti::disegnaBottone(Campo::gRenderer, "img/dialogo.bmp", Campo::SCREEN_WIDTH / 8, 30, 400, 400); //dialogo
    DisegnaContenuti::scriviScrittaPersonalizzata("Ora attacchimo", Campo::gRenderer, x, y1, 115, 0, 0, 0); SDL_RenderPresent(Campo::gRenderer);
    DisegnaContenuti::scriviScrittaPersonalizzata("una base nemica!", Campo::gRenderer, x, y2, 115, 0, 0, 0); SDL_RenderPresent(Campo::gRenderer);
    while (InterazioniUtente::controlloClickBottone(0, Campo::SCREEN_WIDTH, 0, Campo::SCREEN_HEIGHT, 1) != 1) {}

    TTF_Font* font = TTF_OpenFont("font/EaJdz.ttf", 28);
    std::string nome = InterazioniUtente::LeggiTastiera(Campo::gRenderer, font);
    //while (DisegnaContenuti::controlloClickBottone(0, Campo::SCREEN_WIDTH, 0, Campo::SCREEN_HEIGHT, 1) != 1) {}

    Campo::coloraFinestraDiBianco(Campo::gRenderer);
    DisegnaContenuti::disegnaBottone(Campo::gRenderer, "img/capitano.bmp", Campo::SCREEN_WIDTH / 2 - 300, 200, 400, 400); //capitano
    DisegnaContenuti::disegnaBottone(Campo::gRenderer, "img/dialogo.bmp", Campo::SCREEN_WIDTH / 8, 30, 400, 400); //dialogo
    DisegnaContenuti::scriviScrittaPersonalizzata("BENVENUTO ", Campo::gRenderer, x, y1, 115, 0, 0, 0); SDL_RenderPresent(Campo::gRenderer);
    DisegnaContenuti::scriviScrittaPersonalizzata(nome + " !!!", Campo::gRenderer, x, y2, 115, 0, 0, 0); SDL_RenderPresent(Campo::gRenderer);
    while (InterazioniUtente::controlloClickBottone(0, Campo::SCREEN_WIDTH, 0, Campo::SCREEN_HEIGHT, 1) != 1) {}
}

