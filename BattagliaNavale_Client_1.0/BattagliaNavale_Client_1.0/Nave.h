#pragma once

// Librerie
#include <SDL.h>
#include <SDL_ttf.h>

// Altre inclusioni
#include <vector>
#include <string>

class Nave {
public:

    //COSTRUTTORI
        Nave(int larghezza, int altezza);
        Nave(const Nave& other);
        Nave();
 
    //GET E SET
        // Imposta la posizione della nave
        void setPosizione(int col, int riga);
        void setDimensione(int larghezza, int altezza);
        // Restituisce la posizione corrente della nave
        SDL_Rect getPosizione() const;
        int getLarghezza() const;
        int getAltezza() const;
        void setLarghezza(int larghezza);
        void setAltezza(int altezza);
        int getX();
        int getY();
        // Imposta l'orientamento della nave (orizzontale o verticale)
        void setOrientamento(bool orizzontale);
        // Restituisce l'orientamento corrente della nave
        bool getOrientamento() const;
        static Nave* ConvertiInPuntatore(Nave& nave) {
            return &nave;
        }

    //CREAZIONI DI NAVI:
        // Metodo per creare una nave e aggiungerla al vettore di navi
        static Nave creaNave(int larghezza, int altezza, int x, int y, std::vector<Nave>& navi);
        // Metodo per creare una nave
        static Nave creaNave(int larghezza, int altezza, int x, int y);
        static Nave creaNave(int i);

        void modificaNave(Nave& nave, std::vector<Nave>& navi, int i);

    //DISEGNARE LA NAVE:
        // Disegna la nave sul renderer
        void render(SDL_Renderer* renderer) const;


private:
    SDL_Rect posizione;  // Rettangolo che rappresenta la nave
    int larghezza;       // Larghezza della nave
    int altezza;         // Altezza della nave
    bool orientazioneOrizzontale;   // Orientamento della nave (true per orizzontale, false per verticale)
};