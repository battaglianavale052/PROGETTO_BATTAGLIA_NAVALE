#pragma once
#include "DisegnaContenuti.h"

void DisegnaContenuti::scriviScritta(std::string str, SDL_Renderer* gRenderer, int x, int y, int grandezza) {
    TTF_Font* font = TTF_OpenFont("font/EaJdz.ttf", grandezza);
    if (!font) return;
    // Creazione di una superficie di testo:
    SDL_Color coloreTesto = { 45, 129, 200 };
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
int DisegnaContenuti::controlloClickBottone(int x, int x1, int y, int y1, int var, int x_, int x1_, int y_, int y1_, int var_) {
    SDL_Event e;
    int mouseX, mouseY; // Dichiarare queste variabili per memorizzare le coordinate del clic

    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            if (e.button.button == SDL_BUTTON_LEFT) {
                mouseX = e.button.x; // Coordinate X del clic
                mouseY = e.button.y; // Coordinate Y del clic
                // Ora puoi utilizzare mouseX e mouseY per determinare dove ha cliccato l'utente.

                if (mouseX >= x && mouseX <= x1) {
                    if (mouseY >= y && mouseY <= y1) {
                        return var;
                    }
                }

                if (mouseX >= x_ && mouseX <= x1_) {
                    if (mouseY >= y_ && mouseY <= y1_) {
                        return var_;
                    }
                }
            }
        }
    }
    return 0;
}

int DisegnaContenuti::controlloClickBottone(int x, int x1, int y, int y1, int var) {
    SDL_Event e;
    int mouseX, mouseY; // Dichiarare queste variabili per memorizzare le coordinate del clic

    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            if (e.button.button == SDL_BUTTON_LEFT) {
                mouseX = e.button.x; // Coordinate X del clic
                mouseY = e.button.y; // Coordinate Y del clic
                // Ora puoi utilizzare mouseX e mouseY per determinare dove ha cliccato l'utente.

                if (mouseX >= x && mouseX <= x1) {
                    if (mouseY >= y && mouseY <= y1) {
                        return var;
                    }
                }
            }
        }
    }
    return 0;
}