# Repository del progetto Battaglia Navale di Tagliabue e Mottadelli

### Struttura directory

- CL1/BattagliaNavale_ : contiene il client in C++
- CL2/BattagliaNavale_ : contiene il client in C++
- Server : contiene il server in Java
- documentazione : contiene i diagrammi UML ed una presentazione powerpoint del progetto


### Come avviarlo
- Scaricare le cartelle "CL1", "CL2" e "battagliaNavale_server" sul proprio pc
- Aprire con VSC la cartella "battagliaNavale_server" ed avviare il server java (scaricare le opportune estensioni per eseguire file .java)
- Aprire con VSC o VS le cartelle "CL1" e "CL2" ed avviare i client c++ (scaricare le opportune estensioni per eseguire file .cpp e .h)

> [!IMPORTANT]
> Avviare prima il server e poi i client
> Prima di avviare il server, assicurarsi che entrambi i client siano connessi all'indirizzo ip del pc con il server.
> Per farlo, basta modificare l'indirizzo ip presente nella classe "ClientServerComunicazione.cpp" nel client 
> Le cartelle "CL1" e "CL2" contengono già le librerie SDL (per la grafica)
