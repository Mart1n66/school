package oop.skuska.figurefactory;

import oop.skuska.figure.*;

public class BlueFigureFactory implements FigureFactory{
    public BlueFigureFactory(){}

    @Override
    public Figure createPawn(){
        return new BluePawn();
    }

    @Override
    public Figure createBishop(){
        return new BlueBishop();
    }

    @Override
    public Figure createQueen(){
        return new BlueQueen();
    }
}
