package oop.zadanie3;

public class Main {
    public static void main(String[] args){
        Doubler d1 = new Doubler();
        Function d2 = new Doubler(2);
        IO.println(d1.getOutput());        // vrati 0
        IO.println(d1.isOutputPositive()); // vrati false
        IO.println(d2.getOutput());        // vrati 4
        IO.println(d2.isOutputPositive()); // vrati true
        d1.setInput(3);
        d2.setInput(-4);
        IO.println(d1.getOutput());        // vrati  6
        IO.println(d1.isOutputPositive()); // vrati true
        IO.println(d2.getOutput());        // vrati -8
        IO.println(d2.isOutputPositive()); // vrati false

        Squarer s1 = new Squarer(4);
        Function s2 = new Squarer();
        IO.println(s1.getOutput());        // vrati 16
        IO.println(s1.isOutputPositive()); // vrati true
        IO.println(s2.getOutput());        // vrati 0
        IO.println(s2.isOutputPositive()); // vrati false
        s1.setInput(-5);
        s2.setInput(6);
        IO.println(s1.getOutput());        // vrati 25
        IO.println(s1.isOutputPositive()); // vrati true
        IO.println(s2.getOutput());        // vrati 36
        IO.println(s2.isOutputPositive()); // vrati true
    }
}
