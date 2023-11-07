#include "Texture.h"



// Funzione per caricare una singola texture da un file immagine
SDL_Texture* Texture::caricaTextureDaFile(SDL_Renderer* renderer, const std::string& filename) {
    SDL_Texture* texture = nullptr;
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (surface) {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
    return texture;
}

// Funzione per riempire un vettore di texture delle navi
std::vector<SDL_Texture*> Texture::riempiVettoreTextureNavi(SDL_Renderer* renderer)
{
    std::vector<SDL_Texture*> vettoreTextureNavi;

    // Nomi dei file delle immagini delle navi
    std::vector<std::string> nomiNavi = {
        "img/nave1.png",
        "img/nave1.png",
        "img/nave1.png",
        "img/nave1.png",
        "img/nave1.png",
        "img/nave1.png"
    };

    for (const std::string& nomeNave : nomiNavi) {
        SDL_Texture* textureNave = caricaTextureDaFile(renderer, nomeNave);
        if (textureNave) {
            vettoreTextureNavi.push_back(textureNave);
        }
        else {
            // Gestisci l'errore se non riesci a caricare un'immagine.
        }
    }

    return vettoreTextureNavi;
}

void Texture::disegnaTextureNave(SDL_Texture* naveTexture, Nave* nave, int x_, int y_)
{

    int larghezzaNave = nave->getLarghezza();
    int altezzaNave = nave->getAltezza();

    // Ottieni l'orientamento della nave
    bool orientamentoOrizzontale = nave->getOrientamento();

    // Calcola l'angolo di rotazione in base all'orientamento
    float angoloRotazione = 0.0; // Nessuna rotazione
    if (orientamentoOrizzontale) {
        // Ruota l'immagine di 90 gradi in senso orario se la nave è verticale
        angoloRotazione = 90.0;
    }

    // Disegna l'immagine della nave utilizzando SDL_RenderCopyEx
    SDL_Rect naveRect;
    if (orientamentoOrizzontale) {
        // Inverti la larghezza e l'altezza quando l'immagine è ruotata
        int temp = larghezzaNave;
        larghezzaNave = altezzaNave;
        altezzaNave = temp;
        // Se la nave è verticale, sposta l'immagine in modo che sia sopra il rettangolo
        naveRect.x = x_ - (nave->getAltezza() - nave->getLarghezza()) / 2;
        naveRect.y = y_ - (nave->getLarghezza() - nave->getAltezza()) / 2;
    }
    else {
        naveRect.x = x_;
        naveRect.y = y_;
    }
    naveRect.w = larghezzaNave;
    naveRect.h = altezzaNave;

    // La parte importante è l'uso di SDL_RenderCopyEx per la rotazione
    SDL_RenderCopyEx(Campo::gRenderer, naveTexture, NULL, &naveRect, angoloRotazione, NULL, SDL_FLIP_NONE);
}

