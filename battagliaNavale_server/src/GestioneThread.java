import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;

public class GestioneThread extends Thread {

    private Giocatore giocatore;
    private BufferedReader br;
    private PrintWriter pw;

    public GestioneThread(Giocatore g, BufferedReader _br, PrintWriter _pw) {
        this.giocatore = g;
        this.br = _br;
        this.pw = _pw;
    }

    public void run() {

        while (!this.giocatore.tutteLeNaviPosizionate()) {

            String messaggio1="";
            try {
                messaggio1 = this.br.readLine();
            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
            
            //se il messaggio è vuoto ritorna 2 (errore)
            if(messaggio1.isEmpty())
            {
                this.pw.println("3");
                return;
            }

            if (messaggio1.startsWith("nave")) {

                String[] parti1 = messaggio1.split(";");

                // attributi navi giocatore 1
                int lunghezza1 = Integer.parseInt(parti1[1]);
                String orientamento1 = parti1[2];
                int riga1 = Integer.parseInt(parti1[3]);
                int colonna1 = Integer.parseInt(parti1[4]);

                // nave del giocatore 1
                Nave nave1 = new Nave(lunghezza1, orientamento1, riga1, colonna1);

                if (this.giocatore.getCampoGioco().posizionaNave(nave1, riga1, colonna1, orientamento1) == "1") {
                    this.giocatore.aggiungiNave(nave1);
                    this.pw.println("1");
                } else if (this.giocatore.getCampoGioco().posizionaNave(nave1, riga1, colonna1, orientamento1) == "2") {
                    this.pw.println("2");
                }

            }
        }
    }

}
