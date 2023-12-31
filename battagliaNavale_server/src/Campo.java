public class Campo {

    private Cella[][] celle;
    int naviAffondate;

    public Campo(int dimensione) {
        celle = new Cella[dimensione][dimensione];
        for (int riga = 0; riga < dimensione; riga++) {
            for (int colonna = 0; colonna < dimensione; colonna++) {
                celle[riga][colonna] = new Cella();
            }
        }
    }

    public Cella getCella(int riga, int colonna) {
        return celle[riga][colonna];
    }

    public String posizionaNave(Nave nave, int riga, int colonna, String orientamento) {
        // verifica se la posizione iniziale è valida ovvero non è fuori dal campo
        if (riga - 1 < 0 || colonna - 1 < 0 || riga - 1 >= celle.length || colonna - 1 >= celle.length) {
            return "2"; // La posizione non è valida
        }

        // verifica se la nave è attaccata a un'altra nave
        if (contieneNaveAdiacente(riga, colonna, orientamento, nave.getLunghezza())) {
            return "2"; // la nave è adiacente a un'altra nave
        }

        // orientamento orizzontale
        if (orientamento.equals("o")) {
            // verifica se la nave può essere posizionata orizzontalmente
            if (colonna - 1 + nave.getLunghezza() > celle.length) {
                return "2"; // La nave non può essere posizionata qui
            }

            // verifica se la posizione è occupata da un'altra nave
            for (int i = 0; i < nave.getLunghezza(); i++) {
                if (celle[(riga - 1)][(colonna - 1) + i].contieneNave()) {
                    System.out.println("Riga: " + riga + ", Colonna: " + (colonna + i));
                    return "2"; // Posizione occupata da un'altra nave
                }
            }

            // posiziona la nave orizzontalmente
            for (int i = 0; i < nave.getLunghezza(); i++) {
                celle[riga - 1][(colonna - 1) + i].setNave(nave);
            }
        }
        // orientamento verticale
        else if (orientamento.equals("v")) {
            // verifica se la nave può essere posizionata verticalmente
            if (riga - 1 + nave.getLunghezza() > celle.length) {
                return "2"; // la nave non può essere posizionata qui
            }

            // verifica se la posizione è occupata da un'altra nave
            for (int i = 0; i < nave.getLunghezza(); i++) {
                if (celle[(riga - 1) + i][(colonna - 1)].contieneNave()) {
                    System.out.println("Riga: " + (riga + i) + ", Colonna: " + colonna);
                    return "2"; // posizione occupata da un'altra nave
                }
            }

            // posiziona la nave verticalmente
            for (int i = 0; i < nave.getLunghezza(); i++) {
                celle[(riga - 1) + i][(colonna - 1)].setNave(nave);
            }
        }
        // orientamento non valido
        else {
            return "2"; // orientamento non riconosciuto
        }

        return "1"; // la nave è stata posizionata con successo
    }

    // metodo per verificare la presenza di una nave adiacente
    public boolean contieneNaveAdiacente(int riga, int colonna, String orientamento, int lunghezzaNave) {
        if (orientamento.equals("o")) {
            // orientamento orizzontale
            for (int i = -1; i <= 1; i++) {
                for (int j = 0; j < lunghezzaNave; j++) {
                    int newRow = (riga - 1) + i;
                    int newCol = (colonna - 1) + j;
                    if (newRow >= 0 && newRow < celle.length && newCol >= 0 && newCol < celle.length) {
                        if (celle[newRow][newCol].contieneNave()) {
                            return true; // cè una nave adiacente
                        }
                    }
                }
            }
        } else if (orientamento.equals("v")) {
            // orientamento verticale
            for (int i = -1; i <= 1; i++) {
                for (int j = 0; j < lunghezzaNave; j++) {
                    int newRow = (riga - 1) + j;
                    int newCol = (colonna - 1) + i;
                    if (newRow >= 0 && newRow < celle.length && newCol >= 0 && newCol < celle.length) {
                        if (celle[newRow][newCol].contieneNave()) {
                            return true; // cè una nave adiacente
                        }
                    }
                }
            }
        }
        return false; // nessuna nave adiacente
    }

    // metodo per gestire gli spari
    public String sparo(int riga, int colonna) {

        Cella cella = celle[riga][colonna];
        //controllo per non far sparare in una cella che è già stata colpita
        if(cella.isAperta())
        {
            System.out.println("cella già colpita!");
            return "10;10";
            
        }
        if (cella.contieneNave()) {

            // cella.colpisciCella();
            celle[riga][colonna].colpisciCella();

            Nave naveColpita = cella.getNave();

            if (naveColpita.isAffondata()) {
                // la nave è stata affondata
                
                naviAffondate++;
                return "3;"+riga+";"+colonna;
            } else {
                // la nave è stata colpita ma non affondata
                
                return "2;"+riga+";"+colonna;

            }

        } else {

            // acqua
            return "1;"+riga+";"+colonna;
        }

    }

    public boolean tutteNaviAffondate(int numNavi) {

        if (naviAffondate == numNavi) {
            return true;
        } else {
            return false;

        }
    }

    // aggiorna il campo dell'avversario con l'esito dello sparo
    public void aggiornaCampoAvversario(int riga, int colonna, String esito) {

        celle[riga - 1][colonna - 1].setEsitoSparo(esito);
    }

}
