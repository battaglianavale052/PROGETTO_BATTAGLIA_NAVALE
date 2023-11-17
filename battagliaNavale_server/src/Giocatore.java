import java.util.ArrayList;
import java.util.List;

public class Giocatore {
    private String nome;
    private Campo campoGioco;
    private List<Nave> navi;
    private boolean pronto;
    private static final int NUMERO_NAVI = 6;

    public Giocatore(String nome, int dimensioneCampo) {
        this.nome = nome;
        this.campoGioco = new Campo(dimensioneCampo);
        this.navi = new ArrayList<>();
        this.pronto = false;
    }

    public String getNome() {
        return nome;
    }

    public Campo getCampoGioco() {
        return campoGioco;
    }

    public List<Nave> getNavi() {
        return navi;
    }

    public void aggiungiNave(Nave nave) {
        navi.add(nave);
    }

    public void rimuoviNave(Nave nave) {
        navi.remove(nave);
    }


    //imposta il giocatore pronto per sparare
    public void prontoSparare() {
        pronto = true;
    }

    //verifica se il giocatore è pronto
    public boolean prontoPerSparare() {
        return pronto;
    }

    public String effettuaSparo(int riga, int colonna) {
        return campoGioco.sparo(riga, colonna);
    }

    public void setNome(String nome)
    {
        this.nome=nome;
    }

    public boolean haVinto() {
        return campoGioco.tutteNaviAffondate();
    }

    public boolean tutteLeNaviPosizionate() {
        if(navi.size()==NUMERO_NAVI)
        {
            return true;
        }
        else{
            return false;
        }
    }
}
