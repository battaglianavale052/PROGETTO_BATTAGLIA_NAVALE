#include "InterazioniUtente.h"

void InterazioniUtente::gestisciNave(Nave* nave, SDL_Texture* mareTexture, std::vector<Nave> navi, int i) {
    SDL_RenderClear(Campo::gRenderer);
    bool staPosizionandoNave = false;
    bool esciDaNave = false;
    SDL_Event evento;
    int controllo = 1;
    int x_ = nave->getX(), y_ = nave->getY();
    SDL_Texture* bufferTexture = SDL_CreateTexture(Campo::gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Campo::SCREEN_WIDTH, Campo::SCREEN_HEIGHT);

    while (!esciDaNave) {
        // Gestisci gli eventi dell'utente
        gestisciEventi(evento, staPosizionandoNave, esciDaNave, x_, y_, nave);
        // Esegui il rendering sulla texture del buffer
        rendiSuBuffer(bufferTexture, mareTexture, navi, i, nave);
    }

    // Rilascia la texture del buffer
    SDL_DestroyTexture(bufferTexture);
}

void InterazioniUtente::gestisciEventi(SDL_Event& evento, bool& staPosizionandoNave, bool& esciDaNave, int& x_, int& y_, Nave* nave) {
    while (SDL_PollEvent(&evento) != 0) {
        // Se l'utente chiude la finestra, esci dall'interazione con la nave
        if (evento.type == SDL_QUIT) {
            esciDaNave = true;
        }
        if (evento.type == SDL_MOUSEBUTTONDOWN) {
            // Gestisci l'evento di clic del mouse
            gestisciEventoMouseDown(evento, staPosizionandoNave, x_, y_, nave);
        }
        if (evento.type == SDL_MOUSEMOTION) {
            // Gestisci l'evento di movimento del mouse
            gestisciEventoMouseMotion(evento, staPosizionandoNave, x_, y_, nave);
        }
        if (evento.type == SDL_MOUSEBUTTONUP) {
            // Gestisci l'evento di rilascio del pulsante del mouse
            gestisciEventoMouseUp(evento, staPosizionandoNave, esciDaNave, x_, y_, nave);
        }
    }
}

void InterazioniUtente::gestisciEventoMouseDown(SDL_Event& evento, bool& staPosizionandoNave, int& x_, int& y_, Nave* nave) {
    if (evento.button.button == SDL_BUTTON_LEFT) {
        if (!staPosizionandoNave) {
            // L'utente ha iniziato a posizionare la nave
            staPosizionandoNave = true;
            // Calcola la posizione in base alla cella in cui è stato fatto clic
            int cellX = evento.button.x / Campo::CELL_SIZE;
            int cellY = evento.button.y / Campo::CELL_SIZE;
            int naveX = cellX * Campo::CELL_SIZE;
            int naveY = cellY * Campo::CELL_SIZE;
            // Imposta la posizione della nave
            nave->setPosizione(naveX, naveY);
            x_ = naveX;
            y_ = naveY;
        }
    }
}

void InterazioniUtente::gestisciEventoMouseMotion(SDL_Event& evento, bool& staPosizionandoNave, int& x_, int& y_, Nave* nave) {
    if (staPosizionandoNave) {
        // Se l'utente sta posizionando la nave, aggiorna la posizione sulla base del movimento del mouse
        int cellX = evento.button.x / Campo::CELL_SIZE;
        int cellY = evento.button.y / Campo::CELL_SIZE;
        int naveX = cellX * Campo::CELL_SIZE;
        int naveY = cellY * Campo::CELL_SIZE;
        nave->setPosizione(naveX, naveY);
        x_ = naveX;
        y_ = naveY;
    }
}

void InterazioniUtente::gestisciEventoMouseUp(SDL_Event& evento, bool staPosizionandoNave, bool& esciDaNave, int x_, int y_, Nave* nave) {
    static int controllo = 1;
    if (controllo != 1) {
        if (evento.button.button == SDL_BUTTON_LEFT) {
            if (x_ < 0 || x_ > 559 || y_ < 0 || y_ > 559) {
                // La nave è stata posizionata male
            }
            else {
                // La nave è stata posizionata correttamente
                staPosizionandoNave = false;
                esciDaNave = true;
            }
        }
    }
    controllo++;
}

void InterazioniUtente::rendiSuBuffer(SDL_Texture* bufferTexture, SDL_Texture* mareTexture, const std::vector<Nave>& navi, int i, Nave* nave) {
    // Imposta la texture del buffer come destinazione per il rendering
    SDL_SetRenderTarget(Campo::gRenderer, bufferTexture);
    SDL_RenderClear(Campo::gRenderer);

    // Esegui il rendering del campo e dei messaggi
    disegnaCampoEMessaggi(mareTexture, navi, i);
    // Esegui il rendering delle navi
    disegnaNavi(navi, i, nave);

    // Ripristina il renderer come destinazione per il rendering
    SDL_SetRenderTarget(Campo::gRenderer, NULL);

    // Copia la texture del buffer nel renderer principale
    SDL_RenderCopy(Campo::gRenderer, bufferTexture, NULL, NULL);
    SDL_RenderPresent(Campo::gRenderer);
}

void InterazioniUtente::disegnaNavi(std::vector<Nave> navi, int i, Nave* nave) {
    Texture::disegnaTextureNave(i, nave, nave->getX(), nave->getY(), Campo::gRenderer); // Disegna la texture della nave sulla nave

    for (int l = 0; l < i; l++) {
        Texture::disegnaTextureNave(l, &navi[l], navi[l].getX(), navi[l].getY(), Campo::gRenderer); // Disegna la texture della nave sulla nave
    }
}

void InterazioniUtente::disegnaCampoEMessaggi(SDL_Texture* mareTexture, const std::vector<Nave>& navi, int i) {
    SDL_RenderClear(Campo::gRenderer);
    Campo::impostaSfondo(Campo::gRenderer);
    Campo::disegnaGriglia(Campo::CELL_SIZE, Campo::gRenderer, mareTexture);
    DisegnaContenuti::scriviScritta("PIAZZA LA TUA NAVE", Campo::gRenderer, 600, 10, 200);
    SDL_RenderPresent(Campo::gRenderer);
}