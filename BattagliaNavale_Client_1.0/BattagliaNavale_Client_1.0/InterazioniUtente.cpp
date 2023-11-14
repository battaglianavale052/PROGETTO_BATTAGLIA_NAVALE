#include "InterazioniUtente.h"



std::string InterazioniUtente::gestisciNave(Nave* nave, SDL_Texture* mareTexture, std::vector<Nave>& navi, int i) {
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
        rendiSuBuffer(bufferTexture, mareTexture, navi, i, nave, x_, y_);
    }

    // Rilascia la texture del buffer
    SDL_DestroyTexture(bufferTexture);
    return ottieniCoordinateNave(x_,y_);
}

// Funzione per ottenere la stringa "riga, colonna" dalla posizione x e y
std::string InterazioniUtente::ottieniCoordinateNave(int x, int y) {
    // Calcola la riga e la colonna in base alla dimensione della cella
    int riga = y / Campo::CELL_SIZE + 1;
    int colonna = x / Campo::CELL_SIZE + 1;

    // Converti le coordinate in una stringa nel formato desiderato
    return std::to_string(riga) + ";" + std::to_string(colonna);
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

void InterazioniUtente::rendiSuBuffer(SDL_Texture* bufferTexture, SDL_Texture* mareTexture,  std::vector<Nave>& navi, int i, Nave* nave, int x_, int y_) {
    // Imposta la texture del buffer come destinazione per il rendering
    SDL_SetRenderTarget(Campo::gRenderer, bufferTexture);
    SDL_RenderClear(Campo::gRenderer);

    // Esegui il rendering del campo e dei messaggi
    disegnaCampoEMessaggi(mareTexture, navi, i);
    // Esegui il rendering delle navi
    disegnaNavi(navi, i, nave);

    // Aggiorna la posizione della nave nel vettore navi
    navi[i].setPosizione(x_, y_);

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
//-------------------------------------

void InterazioniUtente::renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y) {
    SDL_Color textColor = { 0, 0, 0 };
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);

    if (textSurface == nullptr) {
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    int textWidth = textSurface->w;
    int textHeight = textSurface->h;

    SDL_Rect renderQuad = { x, y, textWidth, textHeight };
    SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

std::string InterazioniUtente::LeggiTastiera(SDL_Renderer* renderer, TTF_Font* font) {
    std::string inputText = "";
    bool quit = false;

    SDL_Event e;
    SDL_StartTextInput();

    DisegnaContenuti::disegnaSfondo(Campo::gRenderer, "img/capitano.bmp", Campo::gWindow);
    DisegnaContenuti::disegnaBottone(renderer, "img/dialogo.bmp", Campo::SCREEN_WIDTH / 8, 30, 400, 400); //dialogo
    DisegnaContenuti::scriviScrittaPersonalizzata("INVIO per proseguire || BACK per cancellare lettere/numeri", Campo::gRenderer, 0, 0, 70, 0, 0, 0);
    DisegnaContenuti::scriviScrittaPersonalizzata("Inserire il tuo", Campo::gRenderer, 230, 190, 115, 0, 0, 0);
    DisegnaContenuti::scriviScrittaPersonalizzata("nome capitano:", Campo::gRenderer, 230, 215, 115, 0, 0, 0);


    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_BACKSPACE && !inputText.empty()) {
                    inputText.pop_back();
                    DisegnaContenuti::disegnaSfondo(Campo::gRenderer, "img/capitano.bmp", Campo::gWindow); 
                    DisegnaContenuti::disegnaBottone(renderer, "img/dialogo.bmp", Campo::SCREEN_WIDTH / 8, 30, 400, 400); //dialogo
                    DisegnaContenuti::scriviScrittaPersonalizzata("INVIO per proseguire || BACK per cancellare lettere/numeri", Campo::gRenderer, 0, 0, 70, 0, 0, 0);
                    DisegnaContenuti::scriviScrittaPersonalizzata("Inserire il tuo", Campo::gRenderer, 230, 190, 115, 0, 0, 0);
                    DisegnaContenuti::scriviScrittaPersonalizzata("nome capitano:", Campo::gRenderer, 230, 215, 115, 0, 0, 0);
                }
                else if (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_KP_ENTER) {
                    quit = true;
                }
            }
            else if (e.type == SDL_TEXTINPUT) {
                inputText += e.text.text;
                DisegnaContenuti::disegnaSfondo(Campo::gRenderer, "img/capitano.bmp", Campo::gWindow); ;
                DisegnaContenuti::disegnaBottone(renderer, "img/dialogo.bmp", Campo::SCREEN_WIDTH / 8, 30, 400, 400); //dialogo
                DisegnaContenuti::scriviScrittaPersonalizzata("INVIO per proseguire || BACK per cancellare lettere/numeri", Campo::gRenderer, 0, 0, 70, 0, 0, 0);
                DisegnaContenuti::scriviScrittaPersonalizzata("Inserire il tuo", Campo::gRenderer, 230, 190, 115, 0, 0, 0);
                DisegnaContenuti::scriviScrittaPersonalizzata("nome capitano:", Campo::gRenderer, 230, 215, 115, 0, 0, 0);
            }
        }

       
        // Disegna il testo inserito dall'utente
        renderText(renderer, font, inputText, 10, 40);

        SDL_RenderPresent(renderer);
    }

    SDL_StopTextInput();

    return inputText;
}

int InterazioniUtente::controlloClickBottone(int x, int x1, int y, int y1, int var, int x_, int x1_, int y_, int y1_, int var_) {
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

int InterazioniUtente::controlloClickBottone(int x, int x1, int y, int y1, int var) {
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
