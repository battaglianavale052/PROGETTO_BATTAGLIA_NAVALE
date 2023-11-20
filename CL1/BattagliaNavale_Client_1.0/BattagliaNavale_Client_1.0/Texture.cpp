#include "Texture.h"



std::vector<SDL_Texture*> Texture::naveTexture;  // Inizializza il vettore statico


Texture::Texture(SDL_Renderer* gRenderer) {
    riempiVettoreTextureNavi(gRenderer);
}
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
void Texture::riempiVettoreTextureNavi(SDL_Renderer* gRenderer)
{
    std::vector<SDL_Texture*> vettoreTextureNavi;

    // Nomi dei file delle immagini delle navi
    std::vector<std::string> nomiNavi = {
        "img/nave1.png",
        "img/nave1.png",
        "img/nave1.png",
        "img/nave1.png",
        "img/navePiccola.bmp",
        "img/navePiccola.bmp"
    };

    for (const std::string& nomeNave : nomiNavi) {
        SDL_Texture* textureNave = caricaTextureDaFile(gRenderer, nomeNave);
        if (textureNave) {
            vettoreTextureNavi.push_back(textureNave);
        }
        else {
            // Gestisci l'errore se non riesci a caricare un'immagine.
        }
    }

    naveTexture = vettoreTextureNavi;
}

void Texture::disegnaTextureNave(int i,Nave* nave, int x_, int y_, SDL_Renderer* gRenderer)
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
        SDL_RenderCopyEx(gRenderer, naveTexture[i], NULL, &naveRect, angoloRotazione, NULL, SDL_FLIP_NONE);
        SDL_RenderPresent(gRenderer);
}

SDL_Texture* Texture::CaricaTextureMare(const char* path, SDL_Renderer* gRenderer) {
    // Carica l'immagine del mare
    SDL_Surface* mareSurface = SDL_LoadBMP(path);

    if (mareSurface == NULL) {
        printf("Impossibile caricare l'immagine del mare! SDL Error: %s\n", SDL_GetError());
        return nullptr; // Restituisci nullptr per indicare che la creazione della texture ha fallito.
    }

    // Converti la superficie in formato RGBA8888
    mareSurface = SDL_ConvertSurfaceFormat(mareSurface, SDL_PIXELFORMAT_RGBA8888, 0);

    // Crea una texture dal mareSurface utilizzando il renderer
    SDL_Texture* mareTexture = SDL_CreateTextureFromSurface(gRenderer, mareSurface);

    SDL_FreeSurface(mareSurface);

    if (mareTexture == NULL) {
        printf("Impossibile creare la texture del mare! SDL Error: %s\n", SDL_GetError());
        return nullptr;
    }

    return mareTexture; // Restituisci la texture del mare creata con successo
}

SDL_Texture* Texture::GetTextureVettore(int i)
{
    return naveTexture[i];
}

void Texture::disegnaVettoreTexture(int i, std::vector<Nave> navi) {
    for (int l = 0; l < i + 1; l++) {
        disegnaTextureNave(l, &navi[l], navi[l].getX(), navi[l].getY(), Campo::gRenderer); //disegna la texture della nave sulla nave  
        SDL_RenderPresent(Campo::gRenderer);
    }
}