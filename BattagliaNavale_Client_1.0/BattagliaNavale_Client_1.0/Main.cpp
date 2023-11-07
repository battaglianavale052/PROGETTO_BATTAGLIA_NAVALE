//LIBRERIE
    #include <SDL.h>
    #include <cstdio>

//CLASSI
    #include "Campo.h"
    #include "DisegnaContenuti.h"
    #include "Texture.h"
    #include "NaviVettore.h"
    #include "InterazioniUtente.h"
    #include "SchermataIniziale.h"


int main(int argc, char* args[]) {
    if (!Campo::initSDL()) {
        printf("Failed to initialize SDL!");
        return -1;
    }
    
    std::vector<Nave> navi; // Vettore per contenere le navi
    std::vector<std::string> testiNave; //contiene il testo delle navi
    DisegnaContenuti Cdc; Campo Cc;Nave Cn;Texture Ctx(Cc.gRenderer);NaviVettore Cnv;InterazioniUtente Cinu; SchermataIniziale Csi;//oggetti di varie classi che verranno usate
    
    //SCHERMATA INZIALE
    Csi.disegnaSfondo(Campo::gRenderer, "img/sfondoInizio.jpg", Campo::gWindow);


    //INIZIO GIOCO
    Cnv.riempiVettoreTestoNave(testiNave); //riempio il vettore di testi delle navi
    Cnv.riempiVettoreNaviTemporanee(navi); //servirà per modifiche future
    SDL_Texture* mareTexture = Ctx.CaricaTextureMare("img/mare.bmp", Cc.gRenderer); //crea la texture del mare come sfondo delle celle
    for (int i = 0; i < 6; i++) { //ciclo per ogni nave per permettere di posizionare nave sul campo

        //CREA CAMPO, BOTTONI e SCRITTA
        Cc.coloraFinestraDiNero(Cc.gRenderer);
        Cc.visualizzaCampo(mareTexture, navi);
        Cdc.disegnaBottone(Cc.gRenderer, "img/ruota.bmp", 1100, 150, 200, 200);
        Cdc.disegnaBottone(Cc.gRenderer, "img/salva.bmp", 1100, 350, 200, 200);
        Cdc.scriviScritta(testiNave[i], Cc.gRenderer);

        Nave nave = Cn.creaNave(i); //creo la nave in base a i
        navi.push_back(nave);
        //Cnv.visualizzaVettore(navi, Cc.gRenderer);
        for (int l = 0; l < i + 1; l++) {
            Texture::disegnaTextureNave(l, &navi[l], navi[l].getX(), navi[l].getY(), Cc.gRenderer); //disegna la texture della nave sulla nave  
            SDL_RenderPresent(Cc.gRenderer);
        }

        bool controllo = true;
        while (controllo) { //finchè la nave non viene ruotata nella direzione desiderata
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
                else if (navi[i].getOrientamento() == true) {
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
                Cdc.scriviScritta(testiNave[i], Cc.gRenderer);
                //Cnv.visualizzaVettore(navi, Cc.gRenderer);
                for (int l = 0; l < i + 1; l++) {
                    Texture::disegnaTextureNave(l ,&navi[l], navi[l].getX(), navi[l].getY(), Cc.gRenderer); //disegna la texture della nave sulla nave  
                    SDL_RenderPresent(Cc.gRenderer);
                }
            }
            //SE IL GIOCATORE SALVA
            if (var == 2) {
                controllo = false;
            }
        }
        controllo = true;
        Cinu.gestisciNave(&nave, mareTexture, navi, i);
        navi[i] = nave;
    }






    
    
    
    Campo::closeSDL();
    return 0;
}


