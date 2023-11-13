public class Cella {

    private boolean aperta;
    private int riga;
    private int colonna;
    private Nave nave;
    private String esitoSparo;

    public Cella() {
        this.aperta = false;
        this.riga = -1;
        this.colonna = -1;
        this.nave = null;
        this.esitoSparo = "";
    }

    public Cella(int riga, int colonna) {

        this.aperta = false;
        this.riga = riga;
        this.colonna = colonna;
        this.nave = null;
        this.esitoSparo = "";

    }

    public boolean contieneNave() {
        if (this.nave != null) {
            return true;
        } else {

            return false;
        }
    }

    public void colpisciCella() {
        this.aperta = true;
        if (nave != null) {
            nave.subisciColpo();
        }
    }

    // metodi get
    public boolean isAperta() {
        return aperta;
    }

    public int getRiga() {
        return riga;
    }

    public int getColonna() {
        return colonna;
    }

    public Nave getNave() {
        return this.nave;
    }

    // metodi set
    public void setAperta(boolean aperta) {
        this.aperta = aperta;
    }

    public void setRiga(int riga) {
        this.riga = riga;
    }

    public void setColonna(int colonna) {
        this.colonna = colonna;
    }

    public void setNave(Nave n) {
        this.nave = n;
    }

    public void setEsitoSparo(String esito) {
        if (esito.equals("colpita") || esito.equals("affondata") || esito.equals("mancata")) {
            this.esitoSparo = esito;
        } else {
            
            this.esitoSparo="errore";
        }
    }

    public String getEsitoSparo() {
        return esitoSparo;
    }

}
