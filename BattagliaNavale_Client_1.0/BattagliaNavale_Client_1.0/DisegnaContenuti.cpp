#pragma once
#include "DisegnaContenuti.h"


void DisegnaContenuti::scriviScritta(std::string str, SDL_Renderer* gRenderer, int x, int y, int grandezza) {
    TTF_Font* font = TTF_OpenFont("font/EaJdz.ttf", grandezza);
    if (!font) return;
    // Creazione di una superficie di testo:
    SDL_Color coloreTesto = { 0, 120, 255 };
    SDL_Surface* superficieTesto = TTF_RenderText_Solid(font, str.c_str(), coloreTesto);

    if (!superficieTesto) {
        // Gestione degli errori nel caso in cui la superficie di testo non venga creata correttamente
        // Puoi aggiungere qui il codice per la gestione degli errori.
        TTF_CloseFont(font);
        return;
    }

    // Creazione di una texture dal testo:
    SDL_Texture* textureTesto = SDL_CreateTextureFromSurface(gRenderer, superficieTesto);

    if (!textureTesto) {
        // Gestione degli errori nel caso in cui la texture non venga creata correttamente
        // Puoi aggiungere qui il codice per la gestione degli errori.
        SDL_FreeSurface(superficieTesto);
        TTF_CloseFont(font);
        return;
    }

    // Renderizzazione del testo:
    SDL_Rect posizione = { x, y, superficieTesto->w / 4, superficieTesto->h / 3 };
    SDL_RenderCopy(gRenderer, textureTesto, NULL, &posizione);

    // Pulizia delle risorse:
    SDL_DestroyTexture(textureTesto);
    SDL_FreeSurface(superficieTesto);
    TTF_CloseFont(font);
}

void DisegnaContenuti::scriviScrittaPersonalizzata(std::string str, SDL_Renderer* gRenderer, int x, int y, int grandezza, int rosso, int verde, int blu) {
    TTF_Font* font = TTF_OpenFont("font/EaJdz.ttf", grandezza);
    if (!font) return;
    // Creazione di una superficie di testo:
    SDL_Color coloreTesto = { rosso, verde, blu };
    SDL_Surface* superficieTesto = TTF_RenderText_Solid(font, str.c_str(), coloreTesto);

    if (!superficieTesto) {
        // Gestione degli errori nel caso in cui la superficie di testo non venga creata correttamente
        // Puoi aggiungere qui il codice per la gestione degli errori.
        TTF_CloseFont(font);
        return;
    }

    // Creazione di una texture dal testo:
    SDL_Texture* textureTesto = SDL_CreateTextureFromSurface(gRenderer, superficieTesto);

    if (!textureTesto) {
        // Gestione degli errori nel caso in cui la texture non venga creata correttamente
        // Puoi aggiungere qui il codice per la gestione degli errori.
        SDL_FreeSurface(superficieTesto);
        TTF_CloseFont(font);
        return;
    }

    // Renderizzazione del testo:
    SDL_Rect posizione = { x, y, superficieTesto->w / 4, superficieTesto->h / 3 };
    SDL_RenderCopy(gRenderer, textureTesto, NULL, &posizione);

    // Pulizia delle risorse:
    SDL_DestroyTexture(textureTesto);
    SDL_FreeSurface(superficieTesto);
    TTF_CloseFont(font);
}
void DisegnaContenuti::disegnaBottone(SDL_Renderer* gRenderer, std::string percorso, int x, int y, int lunghezza, int larghezza) {
    // Carica l'immagine del bottone
    SDL_Surface* bottoneSurface = SDL_LoadBMP(percorso.c_str());
    if (bottoneSurface == nullptr) {
        printf("Impossibile caricare l'immagine del bottone! SDL Error: %s\n", SDL_GetError());
        return;
    }

    // Crea una texture dall'immagine del bottone
    SDL_Texture* bottoneTexture = SDL_CreateTextureFromSurface(gRenderer, bottoneSurface);
    SDL_FreeSurface(bottoneSurface); // Puoi rilasciare la superficie dopo aver creato la texture

    if (bottoneTexture == nullptr) {
        printf("Impossibile creare la texture del bottone! SDL Error: %s\n", SDL_GetError());
        return;
    }

    // Definisci la posizione del bottone
    SDL_Rect bottoneRect = { x, y, lunghezza, larghezza }; // Modifica le coordinate e le dimensioni del bottone a tuo piacimento

    // Copia l'immagine del bottone sulla finestra
    SDL_RenderCopy(gRenderer, bottoneTexture, nullptr, &bottoneRect);

    // Rendere effettive le operazioni di rendering
    SDL_RenderPresent(gRenderer);
}


// Funzione per renderizzare il testo gradualmente
void DisegnaContenuti::scriviScrittaGradualmente(SDL_Renderer* renderer, const std::string& fontPath, const std::string& text, int x, int y, int delay) {
    SDL_Color textColor = { 255, 255, 255 }; // Colore del testo (bianco)

    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), 36);

    for (size_t i = 0; i < text.length(); i++) {
        // Estrai una sottostringa con i primi i caratteri
        std::string partialText = text.substr(0, i + 1);

        // Crea una superficie con il testo parziale
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, partialText.c_str(), textColor);

        // Crea una texture dalla superficie
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        // Pulisci lo schermo
        SDL_RenderClear(renderer);

        // Disegna solo il testo
        SDL_Rect dstRect = { x, y, textSurface->w, textSurface->h };
        SDL_RenderCopy(renderer, textTexture, NULL, &dstRect);

        // Aggiorna la finestra
        SDL_RenderPresent(renderer);

        // Attendi il ritardo
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));

        // Rilascia la texture e la superficie
        SDL_DestroyTexture(textTexture);
        SDL_FreeSurface(textSurface);
    }

    // Rilascia il font
    TTF_CloseFont(font);
}

void DisegnaContenuti::disegnaSfondo(SDL_Renderer* renderer, const char* imagePath, SDL_Window* gWindow) {

    SDL_Surface* imageSurface = IMG_Load(imagePath);

    SDL_Texture* backgroundImage = SDL_CreateTextureFromSurface(renderer, imageSurface);
    // Pulisce lo schermo
    SDL_RenderClear(renderer);

    // Disegna l'immagine come sfondo
    SDL_RenderCopy(renderer, backgroundImage, NULL, NULL);

    // Aggiorna la finestra
    //SDL_RenderPresent(renderer);

    // Pulisce e rilascia le risorse
    SDL_DestroyTexture(backgroundImage);
    SDL_FreeSurface(imageSurface);
}
