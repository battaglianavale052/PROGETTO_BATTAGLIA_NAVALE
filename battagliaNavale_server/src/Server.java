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
            // ciclo principale del gioco

            while (partitaFinita() == true) {

                System.out.println("gioco iniziato!");
                // gestisci il turno del giocatore corrente
                // gestisciTurno(reader1, writer1, reader2, writer2);

                // sparo
                spara(reader1, writer1, reader2, writer2);
                // passa al giocatore successivo
                // passaTurno();
            }

            // determina il vincitore alla fine della partita
            determinaVincitore();

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

        // System.out.println("inizio posizionamento navi");
        // while (giocatore1.tutteLeNaviPosizionate() == false) {

        // String messaggio1 = reader1.readLine();
        // // string messaggio2 = reader2.readLine();

        // System.out.println("ricevuto navi 1: " + messaggio1);
        // if (messaggio1.startsWith("nave")) {

        // String[] parti1 = messaggio1.split(";");

        // // attributi navi giocatore 1
        // int lunghezza1 = Integer.parseInt(parti1[1]);
        // String orientamento1 = parti1[2];
        // int riga1 = Integer.parseInt(parti1[3]);
        // int colonna1 = Integer.parseInt(parti1[4]);

        // // nave del giocatore 1
        // Nave nave1 = new Nave(lunghezza1, orientamento1, riga1, colonna1);

        // if (giocatore1.getCampoGioco().posizionaNave(nave1, riga1, colonna1,
        // orientamento1) == "1") {
        // giocatore1.aggiungiNave(nave1);
        // writer1.println("1");
        // } else if (giocatore1.getCampoGioco().posizionaNave(nave1, riga1, colonna1,
        // orientamento1) == "2") {
        // writer1.println("2");
        // }

        // }
        // }
        // while (giocatore2.tutteLeNaviPosizionate() == false) {

        // String messaggio2 = reader2.readLine();

        // System.out.println("ricevuto navi 2: " + messaggio2);

        // String[] parti2 = messaggio2.split(";");
        // // attributi navi giocatore 2
        // int lunghezza2 = Integer.parseInt(parti2[1]);
        // String orientamento2 = parti2[2];
        // int riga2 = Integer.parseInt(parti2[3]);
        // int colonna2 = Integer.parseInt(parti2[4]);

        // // nave del giocatore 2
        // Nave nave2 = new Nave(lunghezza2, orientamento2, riga2, colonna2);

        // if (giocatore2.getCampoGioco().posizionaNave(nave2, riga2, colonna2,
        // orientamento2) == "1") {
        // giocatore2.aggiungiNave(nave2);
        // writer2.println("1");
        // } else if (giocatore2.getCampoGioco().posizionaNave(nave2, riga2, colonna2,
        // orientamento2) == "2") {
        // writer1.println("2");
        // }
        // }

        // }

        // public void gestisciTurno(BufferedReader reader1, PrintWriter writer1,
        // BufferedReader reader2, PrintWriter writer2)
        // throws IOException {
        // // gestisci il turno del giocatore corrente
        // if (giocatoreCorrente == giocatore1) {
        // gestisciTurnoGiocatore(reader1, writer1, reader2, writer2, giocatore1,
        // giocatore2);
        // } else {
        // gestisciTurnoGiocatore(reader2, writer2, reader1, writer1, giocatore2,
        // giocatore1);
        // }
        // }

        // public void gestisciTurnoGiocatore(BufferedReader readerAttuale, PrintWriter
        // writerAttuale,
        // BufferedReader readerAvversario, PrintWriter writerAvversario, Giocatore
        // giocatoreAttuale,
        // Giocatore giocatoreAvversario) throws IOException {
        // // invia un messaggio al giocatore corrente per indicare il suo turno
        // writerAttuale.println("È il tuo turno, effettua uno sparo (riga;colonna):");

        // // ricevi la mossa del giocatore
        // String mossa = readerAttuale.readLine();

        // // estrai la riga e la colonna dalla mossa
        // String[] coordinate = mossa.split(";");
        // int riga = Integer.parseInt(coordinate[0]);
        // int colonna = Integer.parseInt(coordinate[1]);

        // // effettua lo sparo e ottieni l'esito
        // String esito = giocatoreAttuale.effettuaSparo(riga, colonna);

        // // invia l'esito al giocatore
        // writerAttuale.println(esito);

        // // aggiorna il campo di gioco del giocatore avversario con l'esito
        // giocatoreAvversario.getCampoGioco().aggiornaCampoAvversario(riga, colonna,
        // esito);
    }

    public void spara(BufferedReader reader1, PrintWriter writer1, BufferedReader reader2,
            PrintWriter writer2) throws IOException {

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

    public void determinaVincitore() {
        if (giocatore1.haVinto()) {
            System.out.println("Il vincitore è " + giocatore1.getNome() + "!");
        } else if (giocatore2.haVinto()) {
            System.out.println("Il vincitore è " + giocatore2.getNome() + "!");
        }
    }

}
