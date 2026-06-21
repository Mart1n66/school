package oop.zadanie3;

public class Doubler implements Function{
    private int x;

    public Doubler(){
        this.x = 0;
    }

    public Doubler(int x){
        this.x = x;
    }

    @Override
    public void setInput(int input){
        this.x = input;
    }

    @Override
    public int getOutput(){
        return 2 * this.x;
    }

    /* je to nepotrebne pisat, kedze to zdedili z rozhrania, kod bude kratsi a nebudem sa opakovat
    @Override
    public boolean isOutputPositive(){
        return (getOutput() > 0);
    }*/
}
