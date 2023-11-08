#include "ClientServerComunicazione.h"

// Funzione per ricevere una stringa dal server
std::string  ClientServerComunicazione::receiveString(int socket) {
    char buffer[1024]; // Buffer per la stringa ricevuta
    int bytesRead = recv(socket, buffer, sizeof(buffer), 0);
    if (bytesRead == -1) {
        perror("Errore nella ricezione della stringa");
        return "";
    }
    buffer[bytesRead] = '\0'; // Aggiungi il terminatore null
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

std::string ClientServerComunicazione::Comunicazione() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Errore inizializzazione Winsock." << std::endl;
        return "Errore inizializzazione Winsock.";
    }

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Errore nella creazione del socket." << std::endl;
        WSACleanup();
        return "Errore nella creazione del socket.";
    }

    // Indirizzo IP e porta del server
    const char* serverIP = "127.0.0.1"; // Sostituisci con l'IP del tuo server
    const int serverPort = 666; // Sostituisci con la porta del tuo server

    // Configura l'indirizzo del server
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    inet_pton(AF_INET, serverIP, &serverAddr.sin_addr);

    // Connetti al server
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Errore nella connessione al server." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return "Errore nella connessione al server.";
    }

    // Invia una stringa al server
    std::string messageToSend = "Ciao, server!";
    if (!sendString(clientSocket, messageToSend)) {
        std::cerr << "Errore nell'invio della stringa." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return "Errore nell'invio della stringa.";
    }

    // Ricevi una stringa dal server
    std::string receivedString = receiveString(clientSocket);
    std::cout << "Ricevuto dal server: " << receivedString << std::endl;

    // Chiudi il socket utilizzando closesocket invece di close
    closesocket(clientSocket);
    WSACleanup();

    return receivedString;
}
