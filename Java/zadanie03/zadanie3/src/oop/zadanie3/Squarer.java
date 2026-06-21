package oop.zadanie3;

public class Squarer implements Function{
    private int x;

    public Squarer(){
        this.x = 0;
    }

    public Squarer(int x){
        this.x = x;
    }

    @Override
    public void setInput(int input){
        this.x = input;
    }

    @Override
    public int getOutput(){
        return (this.x * this.x);
    }

    /* je to nepotrebne pisat, kedze to zdedili z rozhrania, kod bude kratsi a nebudem sa opakovat
    @Override
    public boolean isOutputPositive(){
        return (getOutput() > 0);
    }*/
}
