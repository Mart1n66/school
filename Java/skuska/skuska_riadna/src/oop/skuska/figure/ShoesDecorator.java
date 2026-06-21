package oop.skuska.figure;

public class ShoesDecorator extends AbstractDecorator implements Figure{

    public ShoesDecorator(Figure figure){
        this.wrapped = figure;
    }

    @Override
    public void move(){
        int before = wrapped.getPosition();
        wrapped.move();
        int naturalStep = wrapped.getPosition() - before;
        wrapped.setPosition(before + 2*naturalStep) ;
    }

}
