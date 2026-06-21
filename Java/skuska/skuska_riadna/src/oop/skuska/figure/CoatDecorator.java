package oop.skuska.figure;

public class CoatDecorator extends AbstractDecorator implements Figure{
    public CoatDecorator(Figure figure){
        this.wrapped = figure;
    }

    @Override
    public void move(){
        wrapped.move();
        wrapped.setPosition(wrapped.getPosition() + 3);
    }
}
