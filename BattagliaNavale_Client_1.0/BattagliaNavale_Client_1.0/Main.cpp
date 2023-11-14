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
    if (!Campo::initSDL()) {
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
   // Csi.dialogoEnome();  //creo le schermate iniziali per l'inserimento del nome e l'inizio del gioco
   // client.sendAndReceiveString(clientSocket,"pronto;1"); //invio al server che il client è pronto per giocare e aspetto la ricezione che mi conferma che entrambi i giocatori si sono connessi

 
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
        
        std::string coordinte = CinterazUtente.gestisciNave(Nave::ConvertiInPuntatore(nave), mareTexture, navi, i);
        //creo la stringa per il posizionamento della nave e invio al server
        //se la nave va bene mantengo la posizione se la nave non va bene la faccio ripiazzare
        /*
        if (client.sendAndReceiveString(clientSocket, client.stringaPosizione(navi, i, nave, mareTexture)) != "1") { //nave NON posizinata in modo corretto
            Cdc.richiamoContenutiPosizionamentoNave(mareTexture, navi, testiNave, i); //creo sfondo e contenuti di "bellezza"
            Ctx.disegnaVettoreTexture(i, navi); //disegna le texture delle navi
            i--;
        }
        coordinte += "";
        Cdc.richiamoContenutiPosizionamentoNave(mareTexture, navi, testiNave, i); //creo sfondo e contenuti di "bellezza"
        Ctx.disegnaVettoreTexture(i, navi); //disegna le texture delle navi
        */
    }

    Cdc.richiamoContenutiFuoco(mareTexture, navi); //disegna il campo e le navi, togliendo scritta e bottoni
    Ctx.disegnaVettoreTexture(5, navi); //disegna le texture delle navi
    //CICLO DA FARE FINO ALLA FINE DEL GIOCO

    //server per fare coso rosso
    CampoBattaglia::disegnaGriglia(Campo::gRenderer, mareTexture);
    SDL_RenderPresent(Campo::gRenderer);
    SDL_Event e;
    bool quit = false;
    std::string coordinateSparo = "";
    do {
        while (SDL_PollEvent(&e) != 0) {
            // Gestisci gli eventi di input
            quit = CampoBattaglia::gestisciInput(e);
            coordinateSparo = CampoBattaglia::ottieniCellaCliccata(e);
        }
    } while (!quit);
    CampoBattaglia::disegnaGriglia(Campo::gRenderer, mareTexture);
    SDL_RenderPresent(Campo::gRenderer);


    std::string coordinateAvversarie = client.sendAndReceiveString(clientSocket, coordinateSparo); //invio coordinate e aspetto coordiante avversarie
    //al posto di 1;1 inserisco coordinateAvversarie
    Cc.cambiaTextureCella("1;1", mareFuocoTexture); //
    SDL_RenderPresent(Campo::gRenderer);
   
    







    
    
    
    Campo::closeSDL();
    return 0;
}

/*
controllo schermata:
-client invia: "pronto;String nomeGiocatore"

-server invia ai client "1" quando entrambi i giocatori sono connessi

posizionamento navi:
-client invia: "nave;lunghezza_nave;orientamento_nave;riga_nave;colonna_nave" riga e colonna da 0 a 7

-server invia 1 se la nave è stata pozionata in modo corretto dentro al campo, senza sovrapposzioni e
senza stare troppo vicino alle altre navi, 2 se la nave non è stata posizonata in modo corretto dentro il
campo

controllo coordinate sparo:
-client invia:due interi una riga e una colonna da 0 a 7. separate da ;. sparo;1;1

-server invia al client 1 se lo sparo è stato fatto in una casella gia fatta, quindi lo sparo è da rifare
invia invece 2 se lo sparo va bene

controllo vinto:
-client invia: non vuole ninte

-server invia al client 1 se il giocatore a vinto, 2 se il giocatore nessun giocatore non ha ancora vinto,
3 se il giocatore ha perso*/

