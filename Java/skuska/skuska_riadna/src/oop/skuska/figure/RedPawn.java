package oop.skuska.figure;

public class RedPawn extends AbstractFigures implements Figure{

    public RedPawn(){
        this.position = 0;
    }

    @Override
    public void move(){
        position += 1;
    }
}
