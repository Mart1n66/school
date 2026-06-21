package oop.skuska.figure;

public abstract class AbstractFigures implements Figure {
    protected int position;

    @Override
    public void setPosition(int position) {
        this.position = position;
    }

    @Override
    public int getPosition(){
        return this.position;
    }
}
