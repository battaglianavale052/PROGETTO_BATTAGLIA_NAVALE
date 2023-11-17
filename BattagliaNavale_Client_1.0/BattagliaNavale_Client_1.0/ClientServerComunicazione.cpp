#include "ClientServerComunicazione.h"



// Funzione per ricevere una stringa dal server
std::string ClientServerComunicazione::receiveString(int socket) {
    char buffer[1024]; // Buffer per la stringa ricevuta
    int bytesRead = recv(socket, buffer, sizeof(buffer), 0);
    if (bytesRead == -1) {
        perror("Errore nella ricezione della stringa");
        return "";
    }
    buffer[bytesRead] = '\0'; // Aggiungi il terminatore null

    // Rimuovi il carattere di ritorno a capo (\r\n) dalla fine della stringa
    for (int i = bytesRead - 1; i >= 0; --i) {
        if (buffer[i] == '\r' || buffer[i] == '\n') {
            buffer[i] = '\0';
        }
        else {
            break;
        }
    }

    return std::string(buffer);
}

//// Funzione per inviare una stringa al server
//bool ClientServerComunicazione::sendString(int socket, const std::string& message) {
//    int bytesSent = send(socket, message.c_str(), message.size(), 0);
//    if (bytesSent == -1) {
//        perror("Errore nell'invio della stringa");
//        return false;
//    }
//    return true;
//}

bool ClientServerComunicazione::sendString(int socket, const std::string& message) {
    // Aggiungi un carattere di nuova riga alla fine del messaggio
    std::string messageWithNewline = message + "\n";

    // Invia la stringa al server
    int bytesSent = send(socket, messageWithNewline.c_str(), messageWithNewline.size(), 0);
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
    const std::string SERVER_ADDRESS = "127.0.0.1"; // Indirizzo del server (localhost)
    const int SERVER_PORT = 666;
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_ADDRESS.c_str(), &(serverAddr.sin_addr));

    if (connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Errore nella connessione al server." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return INVALID_SOCKET;
    }
    if (clientSocket == INVALID_SOCKET) {
        printf("errore socket");
        return -666;
    }
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

std::string ClientServerComunicazione::stringaPosizione(std::vector<Nave> navi, int i, Nave nave, std::string coordinate)
{
    std::stringstream ss;
    ss << "nave";

    if (navi[i].getOrientamento()) {
        float lunghezzaNave = static_cast<float>(nave.getLarghezza()) / 70.0f;
        ss << ";" << lunghezzaNave;
        ss << ";" << "o";
        ss << ";" << coordinate;
    }
    else {
        float lunghezzaNave = static_cast<float>(nave.getAltezza()) / 70.0f;
        ss << ";" << lunghezzaNave;
        ss << ";" << "v";
        ss << ";" << coordinate;
    }

    return ss.str();
}
