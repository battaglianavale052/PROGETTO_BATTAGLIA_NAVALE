#pragma once
#include "Nave.h"
#include <SDL_mouse.h>
#include <SDL_ttf.h>

Nave::Nave(int larghezza, int altezza) : larghezza(larghezza), altezza(altezza), orientazioneOrizzontale(true) {
    // Inizializza la posizione della nave
    posizione.x = 0;
    posizione.y = 0;
    posizione.w = larghezza;
    posizione.h = altezza;
}

Nave::Nave(const Nave& other) {
    larghezza = other.larghezza;
    altezza = other.altezza;
    posizione = other.posizione;
    orientazioneOrizzontale = other.orientazioneOrizzontale;
}

Nave::Nave() {
}

int Nave::getX() {
    return posizione.x;
}


int Nave::getY() {
    return posizione.y;
}

// imposta la posizione della nave
void Nave::setPosizione(int col, int riga) {
    posizione.x = col;
    posizione.y = riga;
}

// imposta la posizione della nave
void Nave::setDimensione(int larghezza, int altezza) {
    posizione.w = larghezza;
    posizione.h = altezza;
}

// Restituisce la posizione corrente della nave
SDL_Rect Nave::getPosizione() const {
    return posizione;
}

int Nave::getLarghezza() const {
    return larghezza;
}

int Nave::getAltezza() const {
    return altezza;
}

void Nave::setLarghezza(int larghezza) {
    this->larghezza = larghezza;
    posizione.w = larghezza;
}

void Nave::setAltezza(int altezza) {
    this->altezza = altezza;
    posizione.h = altezza;
}

// Disegna la nave sul renderer
void Nave::render(SDL_Renderer* renderer) const {
    // Disegna la nave come un rettangolo rosso (puoi personalizzare il colore)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &posizione);
}
// Imposta l'orientamento della nave (orizzontale o verticale)
void Nave::setOrientamento(bool orizzontale) {
    orientazioneOrizzontale = orizzontale;
}
// Restituisce l'orientamento corrente della nave
bool Nave::getOrientamento() const {
    return orientazioneOrizzontale;
}
Nave Nave::creaNave(int larghezza, int altezza, int x, int y, std::vector<Nave>& navi) {
    // Crea e posiziona la prima nave
    Nave nave(larghezza, altezza);
    //mouseNave(&nave1, mareTexture, navi);
    nave.setPosizione(x, y);
    //navi.push_back(nave);
    return nave;
}
Nave Nave::creaNave(int larghezza, int altezza, int x, int y) {
    // Crea e posiziona la prima nave
    Nave nave(larghezza, altezza);
    //mouseNave(&nave1, mareTexture, navi);
    nave.setPosizione(x, y);
    //navi.push_back(nave);
    return nave;
}

Nave Nave::creaNave(int i)
{

    if (i == 0) { // se è portaerei
        Nave nave(0, 0); // Corazzata iniziale in verticale
        nave = Nave::creaNave(70, 490, 600, 100);
        nave.setOrientamento(false);
        return nave;
    }
    if (i == 1) { // se è corazzata
        Nave nave(0, 0); // Corazzata iniziale in verticale
        nave = Nave::creaNave(70, 280, 600, 100);
        nave.setOrientamento(false);
        return nave;
    }
    if (i == 2) { // se è sottomarino
        Nave nave(0, 0); // Corazzata iniziale in verticale
        nave = Nave::creaNave(70, 210, 600, 100);
        nave.setOrientamento(false);
        return nave;
    }
    if (i == 3) { // se è corvetta
        Nave nave(0, 0); // Corazzata iniziale in verticale
        nave = Nave::creaNave(70, 140, 600, 100);
        nave.setOrientamento(false);
        return nave;
    }
    if (i == 4 || i == 5) { // se è lancia
        Nave nave(0, 0); // Corazzata iniziale in verticale
        nave = Nave::creaNave(70, 70, 600, 100);
        nave.setOrientamento(false);
        return nave;
    }
    Nave nave;
    return nave;
}

void Nave::modificaNave(Nave& nave, std::vector<Nave>& navi, int i) {
    navi[i].setOrientamento(!nave.getOrientamento()); // Inverte l'orientamento
    int temp = navi[i].getAltezza(); //se no l'altezza diventa la larghezza quando usata da setLarghezza
    navi[i].setAltezza(navi[i].getLarghezza()); //imposto altezza la larghezza cosi che de verticale diventa orizzonatale
    navi[i].setLarghezza(temp);//imposto larghezza la altezza cosi che de orizzonatale diventa verticale
}