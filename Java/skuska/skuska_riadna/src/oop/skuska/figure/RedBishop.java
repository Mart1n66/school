package oop.skuska.figure;

public class RedBishop extends AbstractFigures implements Figure{
    //private int position;

    public RedBishop(){
        this.position = 0;
    }

    @Override
    public void move(){
        position += 3;
    }
}
