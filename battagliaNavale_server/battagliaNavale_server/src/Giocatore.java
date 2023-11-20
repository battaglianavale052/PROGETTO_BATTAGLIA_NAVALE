import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

public class Giocatore {
    private String nome;
    private Campo campoGioco;
    private List<Nave> navi;
    private int naviAffondate;
    private boolean pronto;
    private static final int NUMERO_NAVI = 6;

    public Giocatore(String nome, int dimensioneCampo) {
        this.nome = nome;
        this.campoGioco = new Campo(dimensioneCampo);
        this.navi = new ArrayList<>();
        this.pronto = false;
        this.naviAffondate = 0;
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

    public String effettuaSparo(int riga, int colonna, Giocatore giocatore,BufferedReader reader, PrintWriter writer) throws IOException {
        //return giocatore.campoGioco.sparo(riga, colonna);
        
        int _riga = riga;
        int _colonna = colonna;

        // while(giocatore.campoGioco.sparo(_riga, _colonna)=="10;10")
        // {
        //     //giocatore.campoGioco.sparo(_riga, _colonna)=="10;10"
        //     //comunico al client che la cella non è valida
        //     writer.println("10;10");
        //     //ricevo le nuove coordinate dal client
        //     String nuoveCoordinate = reader.readLine();
        //     String[] parti = nuoveCoordinate.split(";");
        //     _riga=Integer.parseInt(parti[0]);
        //     _colonna=Integer.parseInt(parti[1]);
            
        // }

        return giocatore.campoGioco.sparo(_riga, _colonna);
        
    }

    public void setNome(String nome)
    {
        this.nome=nome;
    }

    public boolean haVinto() {
        return campoGioco.tutteNaviAffondate(NUMERO_NAVI);
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
