package oop.skuska.figure;

public class BlueQueen extends AbstractFigures implements Figure{

    public BlueQueen(){
        this.position = 0;
    }

    @Override
    public void move(){
        position += 5;
    }
}
