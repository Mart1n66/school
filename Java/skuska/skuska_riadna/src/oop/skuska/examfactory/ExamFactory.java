package oop.skuska.examfactory;

import oop.skuska.figure.CoatDecorator;
import oop.skuska.figure.Figure;
import oop.skuska.figure.ShoesDecorator;
import oop.skuska.figurefactory.BlueFigureFactory;
import oop.skuska.figurefactory.FigureFactory;
import oop.skuska.figurefactory.RedFigureFactory;

// Tovaren na vyrobu objektov pre automaticke testovanie
public class ExamFactory {

    // Vytvori a vrati tovaren na cervene figurky
    public static FigureFactory createRedFigureFactory() {
       return new RedFigureFactory();
    }

    // Vytvori a vrati tovaren na modre figurky
    public static FigureFactory createBlueFigureFactory() {
        return new BlueFigureFactory();
    }

    // Vytvori a vrati zrychlujuci plast
    public static Figure createCoat(Figure figure) {
        return new CoatDecorator(figure);
    }

    // Vytvori a vrati skakacie topanky
    public static Figure createShoes(Figure figure) {
        return new ShoesDecorator(figure);
    }
}
