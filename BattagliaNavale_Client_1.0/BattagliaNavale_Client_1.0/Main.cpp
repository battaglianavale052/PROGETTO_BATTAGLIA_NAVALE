#include <SDL.h>
#include "Campo.h"
#include "DisegnaContenuti.h"
#include "CreaNave.h"
#include "Texture.h"
#include <cstdio>

int main(int argc, char* args[]) {
    if (!Campo::initSDL()) {
        printf("Failed to initialize SDL!");
        return -1;
    }
    
    std::vector<Nave> navi; // Vettore per contenere le navi
    std::vector<std::string> testiNave; //contiene il testo delle navi
    DisegnaContenuti Cdc;
    Campo Cc;
    Nave Cn;
    CreaNave Ccn;
    Texture Ctx;
    std::vector<SDL_Texture*> textureNavi = Ctx.riempiVettoreTextureNavi(Cc.gRenderer);
    
    Cn.riempiVettoreTestoNave(testiNave); //riempio il vettore di testi delle navi
    Cn.riempiVettoreNaviTemporanee(navi); //servirà per modifiche future
    SDL_Texture* mareTexture = Campo::CaricaTextureMare("img/mare.bmp"); //crea la texture del mare come sfondo delle celle

    for (int i = 0; i < 6; i++) { //ciclo per ogni nave per permettere di posizionare nave sul campo

        //CREA CAMPO, BOTTONI e SCRITTA
        Cc.coloraFinestraDiNero(Cc.gRenderer);
        Cc.visualizzaCampo(mareTexture, navi);
        Cdc.disegnaBottone(Cc.gRenderer, "img/ruota.bmp", 1100, 150, 200, 200);
        Cdc.disegnaBottone(Cc.gRenderer, "img/salva.bmp", 1100, 350, 200, 200);
        Cdc.scriviScritta(testiNave[i]);

        Nave nave = Ccn.creaNave(i); //creo la nave in base a i
        navi.push_back(nave);
        Cc.visualizzaVettore(navi, Cc.gRenderer);
        Texture::disegnaTextureNave(textureNavi[i], &navi[i], navi[i].getX(), navi[i].getY());  SDL_RenderPresent(Cc.gRenderer);

        bool controllo = true;
        while (controllo) {
            int var = Cdc.controlloClickBottone(1120, 1250, 175, 310, 1, 1120, 1250, 380, 520, 2); //bottne gira o bottone salva
            //SE IL GIOCATORE GIRA LA NAVE
            if (var == 1) {
                if (navi[i].getOrientamento() == false) {
                    navi[i].setOrientamento(true); //true se è orizzontale
                    int tempAltz = navi[i].getAltezza(); //se no l'altezza diventa la larghezza quando usata da setLarghezza
                    navi[i].setAltezza(navi[i].getLarghezza()); //imposto altezza la larghezza cosi che de verticale diventa orizzonatale
                    navi[i].setLarghezza(tempAltz);//imposto larghezza la altezza cosi che de orizzonatale diventa verticale
                    nave = navi[i];
                }
                else if (navi[0].getOrientamento() == true) {
                    navi[i].setOrientamento(false);//false se non è orizzontale
                    int tempAltz = navi[i].getAltezza();//se no l'altezza diventa la larghezza quando usata da setLarghezza
                    navi[i].setAltezza(navi[i].getLarghezza());//imposto altezza la larghezza cosi che de verticale diventa orizzonatale
                    navi[i].setLarghezza(tempAltz);//imposto larghezza la altezza cosi che de orizzonatale diventa verticale
                    nave = navi[i];
                }
                //RIDISEGNO TUTTI SE QUALCOSA è STATO MODIFICATO
                Cc.coloraFinestraDiNero(Cc.gRenderer);
                Cc.visualizzaCampo(mareTexture, navi);
                Cdc.disegnaBottone(Cc.gRenderer, "img/ruota.bmp", 1100, 150, 200, 200);
                Cdc.disegnaBottone(Cc.gRenderer, "img/salva.bmp", 1100, 350, 200, 200);
                Cdc.scriviScritta(testiNave[i]);
                Cc.visualizzaVettore(navi, Cc.gRenderer);
                Texture::disegnaTextureNave(textureNavi[i], &navi[i], navi[i].getX(), navi[i].getY());  SDL_RenderPresent(Cc.gRenderer);

            }
            //SE IL GIOCATORE SALVA
            if (var == 2) {
                controllo = false;
            }
        }
        controllo = true;
        Cc.mouseNave(&nave, mareTexture, navi, textureNavi[i]);
        navi[i] = nave;
    }
    
    
    
    Campo::closeSDL();
    return 0;
}


