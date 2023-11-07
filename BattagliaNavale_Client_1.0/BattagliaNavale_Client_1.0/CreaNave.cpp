#include "CreaNave.h"

Nave CreaNave::creaNave(int i)
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
