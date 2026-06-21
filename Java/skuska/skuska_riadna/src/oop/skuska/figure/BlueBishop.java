package oop.skuska.figure;

public class BlueBishop extends AbstractFigures implements Figure {

    public BlueBishop(){
        this.position = 0;
    }

    @Override
    public void move(){
        position += 4;
    }
}
