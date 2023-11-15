//LIBRERIE
    #include <SDL.h>
    #include <cstdio>
    #include <iostream>
    #include <sstream>
    #include <vector>
    #include <string>

//CLASSI
    #include "Campo.h"
    #include "DisegnaContenuti.h"
    #include "Texture.h"
    #include "NaviVettore.h"
    #include "InterazioniUtente.h"
    #include "SchermataIniziale.h"
    #include "ClientServerComunicazione.h"
    #include "CampoBattaglia.h"

int main(int argc, char* args[]) {
    if (!Campo::initSDL()) { //libreria 
        printf("Failed to initialize SDL!");
        return -1;
    }
    
    std::vector<Nave> navi; // Vettore per contenere le navi
    std::vector<std::string> testiNave; //contiene il testo delle navi
    DisegnaContenuti Cdc; Campo Cc;Nave Cn;Texture Ctx(Cc.gRenderer);NaviVettore Cnv; CampoBattaglia CcampoBattagl;
    InterazioniUtente CinterazUtente; SchermataIniziale Csi; ClientServerComunicazione client;//oggetti di varie classi che verranno usate
    SOCKET clientSocket = client.connectToServer(); //creo una connessione col server
    if (clientSocket != INVALID_SOCKET) {
        printf("errore socket");
        return -666;
    }
    SDL_Texture* mareTexture = Ctx.CaricaTextureMare("img/mare.bmp", Cc.gRenderer); //crea la texture del mare come sfondo delle celle
    SDL_Texture* mareFuocoTexture = Ctx.CaricaTextureMare("img/mareFuoco1.bmp", Cc.gRenderer); //crea la texture del mare come sfondo delle celle

    //SCHERMATA INZIALE E ATTESA CONNESSIONE 2 GIOCATORI
    Csi.dialogoEnome();  //creo le schermate iniziali per l'inserimento del nome e l'inizio del gioco
    client.sendAndReceiveString(clientSocket,"pronto;2"); //invio al server che il client è pronto per giocare e aspetto la ricezione che mi conferma che entrambi i giocatori si sono connessi

 
    //INIZIO GIOCO
    Cnv.riempiVettoreTestoNave(testiNave); //riempio il vettore di testi delle navi
    Cnv.riempiVettoreNaviTemporanee(navi); //servirà per modifiche future
    for (int i = 0; i < 6; i++) { //ciclo per ogni nave per permettere di posizionare nave sul campo
        Cdc.richiamoContenutiPosizionamentoNave(mareTexture, navi, testiNave, i); //creo sfondo e contenuti di "bellezza"
       
        Nave nave = Cn.creaNave(i);  navi.push_back(nave);//creo la nave in base a i e le inserisco nel vettore
        Ctx.disegnaVettoreTexture(i, navi); //disegna le texture delle navi
     
        bool controllo = true;
        while (controllo) { //finchè la nave non viene ruotata nella direzione desiderata
            int var = CinterazUtente.controlloClickBottone(1120, 1250, 175, 310, 1, 1120, 1250, 380, 520, 2); //bottne gira o bottone salva
            if (var == 1) { //se il giocatore gira la nave ed è verticale (getOrientamento = true = orizzontale)
                if (navi[i].getOrientamento() == false) {
                   Cn.modificaNave(nave, navi, i);  //cambio altezza con larghezza, orientamento  
                   nave = navi[i]; 
                }
                else if (navi[i].getOrientamento() == true) { //se il giocatore gira la nave ed è verticale (getOrientamento = false = verticale)
                    Cn.modificaNave(nave, navi, i); //cambio altezza con larghezza, orientamento  
                    nave = navi[i];
                }
                Cdc.richiamoContenutiPosizionamentoNave(mareTexture, navi, testiNave, i);//creo sfondo e contenuti di "bellezza"
                Ctx.disegnaVettoreTexture(i, navi); //disegna le texture delle navi
            }
            if (var == 2) controllo = false;//se il giocatore salva la nave, quindi ha scelto l'orientamento
        }
        
        std::string coordinte = CinterazUtente.gestisciNave(Nave::ConvertiInPuntatore(nave), mareTexture, navi, i); //stringa da mandare al server per controllo posizione nave
        if (client.sendAndReceiveString(clientSocket, client.stringaPosizione(navi, i, nave, mareTexture)) != "1") { //nave NON è posizinata in modo corretto
            Cdc.richiamoContenutiPosizionamentoNave(mareTexture, navi, testiNave, i); //creo sfondo e contenuti di "bellezza"
            Ctx.disegnaVettoreTexture(i, navi); //disegna le texture delle navi
            i--; //siccome bisogna riposizionare la stessa nave
        }
        else { //posizione corretta
            Cdc.richiamoContenutiPosizionamentoNave(mareTexture, navi, testiNave, i); //creo sfondo e contenuti di "bellezza"
            Ctx.disegnaVettoreTexture(i, navi); //disegna le texture delle navi
        }
    }

    Cdc.richiamoContenutiFuoco(mareTexture, navi); //disegna il campo e le navi, togliendo scritta e bottoni
    Ctx.disegnaVettoreTexture(5, navi); //disegna le texture delle navi

    std::string controlloFinePartita = "";
    CampoBattaglia::disegnaGriglia(Campo::gRenderer, mareTexture); SDL_RenderPresent(Campo::gRenderer);
    do { //finchè la partita non finisce...

        SDL_Event e;
        bool quit = false;
        std::string coordinateSparo = "";
        do { //finchè il giocatore non spara
            while (SDL_PollEvent(&e) != 0) {
                quit = CampoBattaglia::gestisciInput(e); //click mouse
                coordinateSparo = CampoBattaglia::ottieniCellaCliccata(e); //coordinate sparo
            }
        } while (!quit);
        CampoBattaglia::disegnaGriglia(Campo::gRenderer, mareTexture);//disegna il campoBattaglia che si aggiorna ogni volta che si spara

        Cdc.scriviScritta("TUORNO AVVERSARIO: in attesa dell'avversario", Campo::gRenderer, 0, 570, 90);  SDL_RenderPresent(Campo::gRenderer);//scritta attesa avversario
        std::string coordinateAvversarie = client.sendAndReceiveString(clientSocket, coordinateSparo); //invio coordinate e aspetto coordiante avversarie
        Cc.cambiaTextureCella(coordinateAvversarie, mareFuocoTexture);//disegno texture sparo ricevuto da avversario sul campo da gioco
        CampoBattaglia::disegnaGriglia(Campo::gRenderer, mareTexture); SDL_RenderPresent(Campo::gRenderer);//disegna il campoBattaglia che si aggiorna quando riceve un colpo

        controlloFinePartita = client.receiveString(clientSocket); //ricevo dal client se dati dell'avversario
    } while (controlloFinePartita == "2"); //riceve 1 se il gicotore a vinto, 3 se perso, 2 se continua la partita


    if (controlloFinePartita == "1") {
        Cc.coloraFinestraDiNero(Campo::gRenderer);
        Cdc.scriviScrittaPersonalizzata("HAI VINTO!!!", Campo::gRenderer, 400, 450, 150, 255, 0, 0);
        int vinto = 0;
    }
    else {
        Cc.coloraFinestraDiNero(Campo::gRenderer);
        Cdc.scriviScrittaPersonalizzata("HAI PERSO!!!", Campo::gRenderer, 400, 450, 150, 255, 0, 0);
        int perso = 0;
    }
   
    Campo::closeSDL(); //chiusata libreria
    return 0;
}