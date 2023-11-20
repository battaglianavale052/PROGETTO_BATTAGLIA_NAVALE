#pragma once

// Librerie
#include <SDL.h>
#include <SDL_image.h>

// Classi
#include "Campo.h"
#include "DisegnaContenuti.h"
#include "InterazioniUtente.h"
#include "ClientServerComunicazione.h"

class SchermataIniziale {
public:
    // Metodo per visualizzare il dialogo iniziale e ottenere il nome del giocatore
    static void dialogoEnome();
};
