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

    SDL_Texture* mareTexture = Ctx.CaricaTextureMare("img/mare.bmp", Cc.gRenderer); //crea la texture del mare come sfondo delle celle
    SDL_Texture* mareFuocoTexture = Ctx.CaricaTextureMare("img/mareFuoco1.bmp", Cc.gRenderer); //crea la texture del mare come sfondo delle celle

    //SCHERMATA INZIALE E ATTESA CONNESSIONE 2 GIOCATORI
    Csi.dialogoEnome();  //creo le schermate iniziali per l'inserimento del nome e l'inizio del gioco

    client.receiveString(clientSocket);
    std::string vartemp = client.sendAndReceiveString(clientSocket, "pronto;2"); //invio al server che il client � pronto per giocare e aspetto la ricezione che mi conferma che entrambi i giocatori si sono connessi

    //INIZIO GIOCO
    Cnv.riempiVettoreTestoNave(testiNave); //riempio il vettore di testi delle navi
    Cnv.riempiVettoreNaviTemporanee(navi); //servir� per modifiche future
    for (int i = 0; i < 6; i++) { //ciclo per ogni nave per permettere di posizionare nave sul campo
        Cdc.richiamoContenutiPosizionamentoNave(mareTexture, navi, testiNave, i); //creo sfondo e contenuti di "bellezza"

        Nave nave = Cn.creaNave(i);  navi.push_back(nave);//creo la nave in base a i e le inserisco nel vettore
        Ctx.disegnaVettoreTexture(i, navi); //disegna le texture delle navi

        bool controllo = true;
        while (controllo) { //finch� la nave non viene ruotata nella direzione desiderata
            int var = CinterazUtente.controlloClickBottone(1120, 1250, 175, 310, 1, 1120, 1250, 380, 520, 2); //bottne gira o bottone salva
            if (var == 1) { //se il giocatore gira la nave ed � verticale (getOrientamento = true = orizzontale)
                Cn.modificaNave(nave, navi, i); //cambio altezza con larghezza, orientamento  
                nave = navi[i];
                Cdc.richiamoContenutiPosizionamentoNave(mareTexture, navi, testiNave, i);//creo sfondo e contenuti di "bellezza"
                Ctx.disegnaVettoreTexture(i, navi); //disegna le texture delle navi
            }
            if (var == 2) controllo = false;//se il giocatore salva la nave, quindi ha scelto l'orientamento
        }


        std::string coordinate = CinterazUtente.gestisciNave(Nave::ConvertiInPuntatore(nave), mareTexture, navi, i); //stringa da mandare al server per controllo posizione nave
        if (client.sendAndReceiveString(clientSocket, client.stringaPosizione(navi, i, nave, coordinate)) != "1") { //nave NON � posizinata in modo corretto
            Nave nave2 = Cn.creaNave(i);
            navi[i] = nave2;
            Cdc.richiamoContenutiPosizionamentoNave(mareTexture, navi, testiNave, i); //creo sfondo e contenuti di "bellezza"
            Ctx.disegnaVettoreTexture(i, navi); //disegna le texture delle navi
            navi.pop_back();
            i--;
        }
    }

    Cdc.richiamoContenutiFuoco(mareTexture, navi); //disegna il campo e le navi, togliendo scritta e bottoni
    Ctx.disegnaVettoreTexture(5, navi); //disegna le texture delle navi
    Cdc.scriviScritta("TUORNO AVVERSARIO: in attesa dell'avversario", Campo::gRenderer, 0, 570, 90);  SDL_RenderPresent(Campo::gRenderer);//scritta attesa avversario
    client.receiveString(clientSocket);//aspetto un segnale dal server per gestire i client 

    std::string controlloFinePartita = "";
    CampoBattaglia::disegnaGriglia(Campo::gRenderer, mareTexture); SDL_RenderPresent(Campo::gRenderer);
    do { //finch� la partita non finisce...

        std::string coordinateAvversarie = "10;10";
        do {
            SDL_Event e;
            bool quit = false;
            std::string coordinateSparo = "";
            do { //finch� il giocatore non spara
                while (SDL_PollEvent(&e) != 0) {
                    quit = CampoBattaglia::gestisciInput(e); //click mouse
                    coordinateSparo = CampoBattaglia::ottieniCellaCliccata(e); //coordinate sparo
                }
            } while (!quit);
            Cdc.rettangoloNero(Campo::gRenderer);
            CampoBattaglia::disegnaGriglia(Campo::gRenderer, mareTexture);//disegna il campoBattaglia che si aggiorna ogni volta che si spara
            Cdc.scriviScritta("TUORNO AVVERSARIO: in attesa dell'avversario", Campo::gRenderer, 0, 570, 90);  SDL_RenderPresent(Campo::gRenderer);//scritta attesa avversario

            coordinateAvversarie = client.sendAndReceiveString(clientSocket, coordinateSparo); //invio coordinate e aspetto coordiante avversarie
        } while (coordinateAvversarie == "10;10");

        Cdc.rettangoloNero(Campo::gRenderer);

        char primoNumero = coordinateAvversarie[0];
        if (primoNumero == '1') { //mare colpito
            Cdc.scriviScritta("mare colpito", Campo::gRenderer, 900, 570, 90);  SDL_RenderPresent(Campo::gRenderer);//scritta attesa avversario
        }
        else if (primoNumero == '2') { //nave colpita
            Cdc.scriviScritta("nave colpita", Campo::gRenderer, 900, 570, 90);  SDL_RenderPresent(Campo::gRenderer);//scritta attesa avversario
        }
        else if (primoNumero == '3') {//nave affondata
            Cdc.scriviScritta("nave affondata", Campo::gRenderer, 900, 570, 90);  SDL_RenderPresent(Campo::gRenderer);//scritta attesa avversario
        }
        coordinateAvversarie = coordinateAvversarie.substr(2);// Rimozione del primo numero e del punto e virgola

        Cc.cambiaTextureCella(coordinateAvversarie, mareFuocoTexture);//disegno texture sparo ricevuto da avversario sul campo da gioco
        CampoBattaglia::disegnaGriglia(Campo::gRenderer, mareTexture); SDL_RenderPresent(Campo::gRenderer);//disegna il campoBattaglia che si aggiorna quando riceve un colpo

        controlloFinePartita = client.receiveString(clientSocket); //ricevo dal client se dati dell'avversario
    } while (controlloFinePartita == "2"); //riceve 1 se il gicotore a vinto, 3 se perso, 2 se continua la partita


    if (controlloFinePartita == "1") {
        Cc.coloraFinestraDiNero(Campo::gRenderer);
        Cdc.scriviScrittaPersonalizzata("HAI VINTO!!!", Campo::gRenderer, 400, 450, 150, 255, 0, 0);
        SDL_RenderPresent(Campo::gRenderer);
        while (InterazioniUtente::controlloClickBottone(0, Campo::SCREEN_WIDTH, 0, Campo::SCREEN_HEIGHT, 1) != 1) {}
    }
    else if (controlloFinePartita == "3") {
        Cc.coloraFinestraDiNero(Campo::gRenderer);
        Cdc.scriviScrittaPersonalizzata("HAI PERSO!!!", Campo::gRenderer, 400, 450, 150, 255, 0, 0);
        SDL_RenderPresent(Campo::gRenderer);
        while (InterazioniUtente::controlloClickBottone(0, Campo::SCREEN_WIDTH, 0, Campo::SCREEN_HEIGHT, 1) != 1) {}
    }
    else {
        Cc.coloraFinestraDiNero(Campo::gRenderer);
        Cdc.scriviScrittaPersonalizzata("ABBANDONO...", Campo::gRenderer, 400, 450, 150, 255, 0, 0);
        SDL_RenderPresent(Campo::gRenderer);
        while (InterazioniUtente::controlloClickBottone(0, Campo::SCREEN_WIDTH, 0, Campo::SCREEN_HEIGHT, 1) != 1) {}
    }

    Campo::closeSDL(); //chiusata libreria
    return 0;
}