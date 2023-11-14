#include "ClientServerComunicazione.h"



// Funzione per ricevere una stringa dal server
std::string  ClientServerComunicazione::receiveString(int socket) {
    char buffer[1024]; // Buffer per la stringa ricevuta
    int bytesRead = recv(socket, buffer, sizeof(buffer), 0);
    if (bytesRead == -1) {
        perror("Errore nella ricezione della stringa");
        return "";
    }
    //buffer[bytesRead] = '\0'; // Aggiungi il terminatore null
    return std::string(buffer);
}

// Funzione per inviare una stringa al server
bool ClientServerComunicazione::sendString(int socket, const std::string& message) {
    int bytesSent = send(socket, message.c_str(), message.size(), 0);
    if (bytesSent == -1) {
        perror("Errore nell'invio della stringa");
        return false;
    }
    return true;
}

// Funzione per connettersi al server
SOCKET ClientServerComunicazione::connectToServer() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Errore inizializzazione Winsock." << std::endl;
        return INVALID_SOCKET;
    }

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Errore nella creazione del socket." << std::endl;
        WSACleanup();
        return INVALID_SOCKET;
    }

    // ... (rimane invariata)

    return clientSocket;
}

// Funzione per chiudere la connessione al server
void ClientServerComunicazione::closeConnection(SOCKET clientSocket) {
    closesocket(clientSocket);
    WSACleanup();
}

// Funzione per inviare una stringa al server e ricevere la risposta
std::string ClientServerComunicazione::sendAndReceiveString(SOCKET clientSocket, const std::string& message) {
    if (!sendString(clientSocket, message)) {
        std::cerr << "Errore nell'invio della stringa." << std::endl;
        return "Errore nell'invio della stringa.";
    }

    // Ricevi una stringa dal server
    std::string receivedString = receiveString(clientSocket);

    return receivedString;
}

// Esempio di utilizzo nel tuo programma principale
void ClientServerComunicazione::mainFunction() {
    SOCKET clientSocket = connectToServer();

    if (clientSocket != INVALID_SOCKET) {
        // Prima stringa
        std::string message1 = "Prima stringa";
        std::string response1 = sendAndReceiveString(clientSocket, message1);
        std::cout << "Ricevuto dal server: " << response1 << std::endl;

        // Seconda stringa
        std::string message2 = "Seconda stringa";
        std::string response2 = sendAndReceiveString(clientSocket, message2);
        std::cout << "Ricevuto dal server: " << response2 << std::endl;

        // Chiudi la connessione
        closeConnection(clientSocket);
    }
}

std::string ClientServerComunicazione::stringaPosizione(std::vector<Nave> navi, int i, Nave nave, SDL_Texture* mareTexture)
{
    std::string str = "";
    str = std::string("nave");
    if (navi[i].getOrientamento() == false) {
        str += (navi[i].getAltezza());
        str += "v";
    }
    else {
        str += (navi[i].getLarghezza());
        str += "o";
    }
    str += InterazioniUtente::gestisciNave(&nave, mareTexture, navi, i);
    return str;
}
