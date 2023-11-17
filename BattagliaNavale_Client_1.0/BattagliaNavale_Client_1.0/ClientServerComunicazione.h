#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <WinSock2.h>
#include <WS2tcpip.h>>

#include <vector>
#include "Nave.h"
#include "InterazioniUtente.h"

// Aggiungi questa direttiva per collegare la libreria ws2_32.lib
#pragma comment(lib, "ws2_32.lib")


class ClientServerComunicazione
{
public:

	//INVIO e/o RICEZIONE
		static std::string receiveString(int socket);
		static bool sendString(int socket, const std::string& message);
		static SOCKET connectToServer();
		static void closeConnection(SOCKET clientSocket);
		static std::string sendAndReceiveString(SOCKET clientSocket, const std::string& message);

	//creazione stringa per server 
	static std::string stringaPosizione(std::vector<Nave> navi, int i, Nave nave, SDL_Texture* mareTexture);


public:
	static std::string nomeGiocatore;
};

