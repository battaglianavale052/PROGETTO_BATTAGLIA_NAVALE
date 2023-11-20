public class Nave {

    private int lunghezza;
    private boolean affondata;
    private int colpiRicevuti;
    private int riga;
    private int colonna;
    private String orientamento;

    public Nave(int lunghezza) {
        this.lunghezza = lunghezza;
        this.affondata = false;
        this.colpiRicevuti = 0;
        this.riga = -1;
        this.colonna = -1;
        this.orientamento = "o"; // inizialmente la nave è orientata orizzontalmente.
    }

    public Nave(int lunghezza,String orientamento,int riga,int colonna) {
        this.lunghezza = lunghezza;
        this.affondata = false;
        this.colpiRicevuti = 0;
        this.riga = riga;
        this.colonna = colonna;
        this.orientamento = orientamento;
    }

    public boolean isAffondata() {
        return affondata;
    }
    
    public void setAffondata(boolean affondata) {
        this.affondata = affondata;
    }

    public int getLunghezza() {
        return lunghezza;
    }

    public int getColpiRicevuti() {
        return colpiRicevuti;
    }

    public void subisciColpo() {
        colpiRicevuti++;
        if (colpiRicevuti >= lunghezza) {
            affondata = true;
        }
    }

    public int getRiga() {
        return riga;
    }

    public int getColonna() {
        return colonna;
    }

    public String getOrientamento() {
        return orientamento;
    }

    public void setOrientamento(String orientamento) {
        this.orientamento = orientamento;
    }

    public void posiziona(int riga, int colonna, String orientamento) {
        this.riga = riga;
        this.colonna = colonna;
        this.orientamento = orientamento;
    }
}
