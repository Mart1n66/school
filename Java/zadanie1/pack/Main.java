package pack;

public class Main {
    public static void main(String args[]){
        TownCrier crier = new TownCrier();

        IO.println(crier.getNumberOfLastMessageAnnounced()); // vrati 0

        crier.setMessage("Vtaky lietaju nizko, burka je blizko");
        IO.println(crier.announce()); // vrati "Vtaky lietaju nizko, burka je blizko"
        IO.println(crier.announce()); // vrati "Vtaky lietaju nizko, burka je blizko"
        IO.println(crier.getNumberOfLastMessageAnnounced()); // vrati 2

        crier.setMessage("V skole sa zacina vykurovacia sezona. Kazdy ziak musi doniest poleno dreva denne");
        IO.println(crier.announce()); // vrati "V skole sa zacina ...
        IO.println(crier.getNumberOfLastMessageAnnounced()); // vrati 1
    }
}
