// Librerie
#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <vector>

// Classi
#include "Nave.h"
#include "InterazioniUtente.h"

// Aggiungi questa direttiva per collegare la libreria ws2_32.lib
#pragma comment(lib, "ws2_32.lib")

// Classi
class ClientServerComunicazione {
public:
    // Metodi per la comunicazione tra client e server

    // Ricezione di una stringa da un socket
    static std::string receiveString(int socket);

    // Invio di una stringa attraverso un socket
    static bool sendString(int socket, const std::string& message);

    // Connessione al server
    static SOCKET connectToServer();

    // Chiusura della connessione del client
    static void closeConnection(SOCKET clientSocket);

    // Invia una stringa e ricevi una risposta dal server
    static std::string sendAndReceiveString(SOCKET clientSocket, const std::string& message);

    // Metodo per ottenere una stringa di posizione da un vettore di navi
    std::string stringaPosizione(std::vector<Nave> navi, int i, Nave nave, std::string coordinate);

public:
    // Nome del giocatore
    static std::string nomeGiocatore;
};
