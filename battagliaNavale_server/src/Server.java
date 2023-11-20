import java.io.*;
import java.net.*;
import java.util.HashMap;
import java.util.Map;

public class Server {
    private Giocatore giocatore1;
    private Giocatore giocatore2;
    private Giocatore giocatoreCorrente;

    public Server() {
        giocatore1 = new Giocatore("Giocatore1", 8);
        giocatore2 = new Giocatore("Giocatore2", 8);
        giocatoreCorrente = giocatore1;
    }

    public void start() {
        try (ServerSocket serverSocket = new ServerSocket(666)) {

            // Socket clientSocket1 = serverSocket.accept();
            // BufferedReader reader1 = new BufferedReader(new
            // InputStreamReader(clientSocket1.getInputStream()));
            // PrintWriter writer1 = new PrintWriter(clientSocket1.getOutputStream(), true);

            // // Leggi la stringa inviata dal client
            // String messaggio1 = reader1.readLine();

            // System.out.println("Messaggio ricevuto: " + messaggio1);

            // writer1.println("ciao");

            // System.out.println("inviato ciao");

            System.out.println("Server in ascolto sulla porta 666");

            // aspetto prima connessione cl1
            Socket clientSocket1 = serverSocket.accept();
            System.out.println("Connessione da: " + clientSocket1.getInetAddress());
            Socket clientSocket2 = serverSocket.accept();
            System.out.println("Connessione da: " + clientSocket2.getInetAddress());
            // ricevi pronto1 e pronto2

            BufferedReader reader1 = new BufferedReader(new InputStreamReader(clientSocket1.getInputStream()));
            PrintWriter writer1 = new PrintWriter(clientSocket1.getOutputStream(), true);

            BufferedReader reader2 = new BufferedReader(new InputStreamReader(clientSocket2.getInputStream()));
            PrintWriter writer2 = new PrintWriter(clientSocket2.getOutputStream(), true);

            writer1.println("1");

            // aspetto che entrambi i giocatori siano pronti
            attesaProntoGiocatori(reader1, writer1, reader2, writer2);

            // aspetto che entrambi i giocatori posizionino le navi
            attesaPosizionamentoNavi(reader1, writer1, reader2, writer2);

            System.out.println("gioco iniziato!");

            // faccio partire il client 1
            writer1.println("1");
            // spara(reader1, writer1, reader2, writer2);
            String risposta1 = spara(reader1, writer1, writer2, giocatore1);

            // faccio partire il client 2
            writer2.println("1");
            String risposta2 = spara(reader2, writer2, writer1, giocatore2);

            //inverto gli esiti dei colpi
            String[] partiEsito1 = risposta1.split(";");
            String esito1 = partiEsito1[0];

            String[] partiEsito2 = risposta2.split(";");
            String esito2 = partiEsito2[0];

            risposta1 = risposta1.substring(1);
            risposta1 = esito2 + risposta1;

            risposta2 = risposta2.substring(1);
            risposta2 = esito1 + risposta2;

            // invio ai client lo sparo nemico
            writer1.println(risposta2);
            writer2.println(risposta1);

            // determina se un giocatore ha vinto e lo comunica ai client
            determinaVincitore(reader1, writer1, reader2, writer2);

            // ciclo principale del gioco
            while (partitaFinita() == false) {

                // gestisci il turno del giocatore corrente
                // gestisciTurno(reader1, writer1, reader2, writer2);

                // sparo
                spara(reader1, writer1, reader2, writer2);

                // determina se un giocatore ha vinto e lo comunica ai client
                determinaVincitore(reader1, writer1, reader2, writer2);

            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void attesaProntoGiocatori(BufferedReader reader1, PrintWriter writer1, BufferedReader reader2,
            PrintWriter writer2) throws IOException {

        while (giocatore1.prontoPerSparare() == false || giocatore2.prontoPerSparare() == false) {

            System.out.println("inizio attesa giocatori");

            String messaggio1 = reader1.readLine();
            System.out.println("ricevuto 1: " + messaggio1);

            writer2.println("1");
            String messaggio2 = reader2.readLine();
            System.out.println("ricevuto 2: " + messaggio2);

            if (messaggio1.startsWith("pronto") && messaggio2.startsWith("pronto")) {

                String[] parti1 = messaggio1.split(";");
                String[] parti2 = messaggio2.split(";");

                giocatore1.setNome(parti1[1]);
                giocatore2.setNome(parti2[1]);

                // entrambi i giocatori sono pronti
                writer1.println("1");
                writer2.println("1");

                giocatore1.prontoSparare();
                giocatore2.prontoSparare();
            }
        }
    }

    public void attesaPosizionamentoNavi(BufferedReader reader1, PrintWriter writer1, BufferedReader reader2,
            PrintWriter writer2) throws IOException {

        GestioneThread ThreadGiocatore1 = new GestioneThread(giocatore1, reader1,
                writer1);
        GestioneThread ThreadGiocatore2 = new GestioneThread(giocatore2, reader2,
                writer2);

        ThreadGiocatore1.start();
        ThreadGiocatore2.start();

        try {
            ThreadGiocatore1.join();
        } catch (InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        try {
            ThreadGiocatore2.join();
        } catch (InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

    }

    public void spara(BufferedReader reader1, PrintWriter writer1, BufferedReader reader2,
            PrintWriter writer2) throws IOException {

        // spara il giocatore 1
        // comunico al client che è il suo turno di sparare
        // writer1.println("1");
        System.out.println("ricezione colpo 1...");

        // String messaggio1 = reader1.readLine(); // coordinate di sparo cl1
        // String[] parti = messaggio1.split(";");
        // System.out.println("ricevuto 1: " + messaggio1);
        // int rigaColpo = Integer.parseInt(parti[0]);
        // int colonnaColpo = Integer.parseInt(parti[1]);
        String risposta1 = "";
        do {

            String messaggio1 = reader1.readLine(); // coordinate di sparo cl1
            String[] parti = messaggio1.split(";");
            System.out.println("ricevuto 1: " + messaggio1);
            int rigaColpo = Integer.parseInt(parti[0]);
            int colonnaColpo = Integer.parseInt(parti[1]);
            risposta1 = giocatore1.effettuaSparo(rigaColpo, colonnaColpo, giocatore2, reader1, writer1);
            if (risposta1 == "10;10") {
                writer1.println(risposta1);
            }

        } while (risposta1 == "10;10");

        // spara il giocatore 2
        // comunico al client che è il suo turno di sparare

        // System.out.println("ricezione colpo 2...");
        // String messaggio2 = reader2.readLine();
        // String[] parti2 = messaggio2.split(";");
        // System.out.println("ricevuto 2: " + messaggio2);
        // int rigaColpo2 = Integer.parseInt(parti2[0]);
        // int colonnaColpo2 = Integer.parseInt(parti2[1]);

        String risposta2 = "";
        do {

            System.out.println("ricezione colpo 2...");
            String messaggio2 = reader2.readLine();
            String[] parti2 = messaggio2.split(";");
            System.out.println("ricevuto 2: " + messaggio2);
            int rigaColpo2 = Integer.parseInt(parti2[0]);
            int colonnaColpo2 = Integer.parseInt(parti2[1]);

            risposta2 = giocatore2.effettuaSparo(rigaColpo2, colonnaColpo2, giocatore1, reader2, writer2);
            if (risposta2 == "10;10") {
                writer2.println(risposta2);
            }

        } while (risposta2 == "10;10");

        //inverto gli esiti dei colpi
        String[] partiEsito1 = risposta1.split(";");
        String esito1 = partiEsito1[0];

        String[] partiEsito2 = risposta2.split(";");
        String esito2 = partiEsito2[0];

        risposta1 = risposta1.substring(1);
        risposta1 = esito2 + risposta1;

        risposta2 = risposta2.substring(1);
        risposta2 = esito1 + risposta2;

        writer1.println(risposta2);
        writer2.println(risposta1);

    }

    public String spara(BufferedReader readerAttaccante, PrintWriter writerAttaccante, PrintWriter writerDifensore,
            Giocatore giocatore) throws IOException {

        // spara il giocatore 1
        // comunico al client che è il suo turno di sparare

        System.out.println("ricezione colpo " + giocatore.getNome());
        String messaggio = readerAttaccante.readLine(); // coordinate di sparo cl1
        String[] parti = messaggio.split(";");
        System.out.println("ricevuto " + giocatore.getNome() + ": " + messaggio);
        int rigaColpo = Integer.parseInt(parti[0]);
        int colonnaColpo = Integer.parseInt(parti[1]);
        if (giocatore == giocatore1) {
            String risposta = giocatore.effettuaSparo(rigaColpo, colonnaColpo, giocatore2, readerAttaccante,
                    writerAttaccante);
            return risposta;
        } else {
            String risposta = giocatore.effettuaSparo(rigaColpo, colonnaColpo, giocatore1, readerAttaccante,
                    writerAttaccante);
            return risposta;
        }

    }

    public void passaTurno() {
        if (giocatoreCorrente == giocatore1) {
            giocatoreCorrente = giocatore2;
        } else {
            giocatoreCorrente = giocatore1;
        }
    }

    public boolean partitaFinita() {

        if (giocatore1.haVinto() || giocatore2.haVinto()) {
            return true;
        } else {
            return false;
        }
    }

    public void determinaVincitore(BufferedReader reader1, PrintWriter writer1, BufferedReader reader2,
            PrintWriter writer2) throws IOException {
        if (giocatore2.haVinto()) {
            // il giocatore 1 ha vinto
            System.out.println("Il vincitore è " + giocatore1.getNome() + "!");
            writer1.println("1");
            writer2.println("3");

        } else if (giocatore1.haVinto()) {
            // il giocstore 2 ha vinto
            System.out.println("Il vincitore è " + giocatore2.getNome() + "!");
            writer1.println("3");
            writer2.println("1");
        } else {
            // nessun giocatore ha ancora vinto
            writer1.println("2");
            writer2.println("2");
        }
    }

    public void determinaVincitore() {
        if (giocatore1.haVinto()) {
            System.out.println("Il vincitore è " + giocatore1.getNome() + "!");
        } else if (giocatore2.haVinto()) {
            System.out.println("Il vincitore è " + giocatore2.getNome() + "!");
        }
    }

}
