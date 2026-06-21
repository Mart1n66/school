package oop.skuska.figure;

public class BluePawn extends AbstractFigures implements Figure{

    public BluePawn(){
        this.position = 0;
    }

    @Override
    public void move(){
        position += 1;
    }
}
