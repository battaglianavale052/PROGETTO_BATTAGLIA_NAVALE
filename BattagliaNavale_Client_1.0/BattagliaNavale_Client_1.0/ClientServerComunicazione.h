#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <WinSock2.h>
#include <WS2tcpip.h>>

// Aggiungi questa direttiva per collegare la libreria ws2_32.lib
#pragma comment(lib, "ws2_32.lib")


class ClientServerComunicazione
{
public:

	static std::string receiveString(int socket);
	static bool sendString(int socket, const std::string& message);
	static std::string Comunicazione();

};

