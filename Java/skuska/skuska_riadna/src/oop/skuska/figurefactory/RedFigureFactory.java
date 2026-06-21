package oop.skuska.figurefactory;

import oop.skuska.figure.Figure;
import oop.skuska.figure.RedBishop;
import oop.skuska.figure.RedPawn;
import oop.skuska.figure.RedQueen;

public class RedFigureFactory implements FigureFactory{
    public RedFigureFactory(){}

    @Override
    public Figure createPawn(){
        return new RedPawn();
    }

    @Override
    public Figure createBishop(){
        return new RedBishop();
    }

    @Override
    public Figure createQueen(){
        return new RedQueen();
    }
}
