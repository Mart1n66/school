package oop.skuska;

import oop.skuska.figure.Figure;
import oop.skuska.figurefactory.FigureFactory;
import org.junit.jupiter.api.Test;

import oop.skuska.examfactory.ExamFactory;

import static org.junit.jupiter.api.Assertions.*;


public class ExamTest {

    // Postupne posuva metodou 'move()' a testuje, ci sa nachadza na poziciach 'steps'
    // Zacina porovnanim pozicie so steps[0] a az potom prvy krat posunie
    private void testSteps(Figure figure, int... steps) {
        assertEquals(steps[0], figure.getPosition());
        for (int i = 1; i < steps.length; ++ i) {
            figure.move();
            assertEquals(steps[i], figure.getPosition());
        }
    }

    // ---- figurky - tovarne ------------------------------------------------------------------------------------------

    @Test @Points(2)
    void factoryFigure() {
        FigureFactory red = ExamFactory.createRedFigureFactory();
        FigureFactory blue = ExamFactory.createBlueFigureFactory();
        assertNotNull(red);
        assertNotNull(blue);
    }

    // ---- figurky ----------------------------------------------------------------------------------------------------

    @Test @Points(2)
    void redPawn() {
        FigureFactory red = ExamFactory.createRedFigureFactory();
        Figure pawn = red.createPawn();
        testSteps(pawn, 0, 1, 2, 3, 4);
    }

    @Test @Points(2)
    void bluePawn() {
        FigureFactory blue = ExamFactory.createBlueFigureFactory();
        Figure pawn = blue.createPawn();
        testSteps(pawn, 0, 1, 2, 3, 4);
    }

    @Test @Points(2)
    void redBishop() {
        FigureFactory red = ExamFactory.createRedFigureFactory();
        Figure bishop = red.createBishop();
        testSteps(bishop, 0, 3, 6, 9, 12);
    }

    @Test @Points(2)
    void blueBishop() {
        FigureFactory blue = ExamFactory.createBlueFigureFactory();
        Figure bishop = blue.createBishop();
        testSteps(bishop, 0, 4, 8, 12, 16);
    }

    @Test @Points(2)
    void redQueen() {
        FigureFactory red = ExamFactory.createRedFigureFactory();
        Figure queen = red.createQueen();
        testSteps(queen, 0, 6, 12, 18, 24);
    }

    @Test @Points(2)
    void blueQueen() {
        FigureFactory blue = ExamFactory.createBlueFigureFactory();
        Figure queen = blue.createQueen();
        testSteps(queen, 0, 5, 10, 15, 20);
    }

    // ---- dekoratory (po jednom) -------------------------------------------------------------------------------------

    @Test @Points(2)
    void coat() {
        FigureFactory red = ExamFactory.createRedFigureFactory();
        FigureFactory blue = ExamFactory.createBlueFigureFactory();

        Figure redPawn = red.createPawn();
        Figure redPawnCoat = ExamFactory.createCoat(redPawn);
        testSteps(redPawnCoat, 0, 4, 8, 12, 16);

        Figure redBishop = red.createBishop();
        Figure redBishopCoat = ExamFactory.createCoat(redBishop);
        testSteps(redBishopCoat, 0, 6, 12, 18, 24);

        Figure redQueen = red.createQueen();
        Figure redQueenCoat = ExamFactory.createCoat(redQueen);
        testSteps(redQueenCoat, 0, 9, 18, 27, 36, 45);

        Figure bluePawn = blue.createPawn();
        Figure bluePawnCoat = ExamFactory.createCoat(bluePawn);
        testSteps(bluePawnCoat, 0, 4, 8, 12, 16);

        Figure blueBishop = blue.createBishop();
        Figure blueBishopCoat = ExamFactory.createCoat(blueBishop);
        testSteps(blueBishopCoat, 0, 7, 14, 21, 28);

        Figure blueQueen = blue.createQueen();
        Figure blueQueenCoat = ExamFactory.createCoat(blueQueen);
        testSteps(blueQueenCoat, 0, 8, 16, 24, 32);
    }

    @Test @Points(2)
    void shoes() {
        FigureFactory red = ExamFactory.createRedFigureFactory();
        FigureFactory blue = ExamFactory.createBlueFigureFactory();

        Figure redPawn = red.createPawn();
        Figure redPawnShoes = ExamFactory.createShoes(redPawn);
        testSteps(redPawnShoes, 0, 2, 4, 6, 8);

        Figure redBishop = red.createBishop();
        Figure redBishopShoes = ExamFactory.createShoes(redBishop);
        testSteps(redBishopShoes, 0, 6, 12, 18, 24);

        Figure redQueen = red.createQueen();
        Figure redQueenShoes = ExamFactory.createShoes(redQueen);
        testSteps(redQueenShoes, 0, 12, 24, 36, 48);

        Figure bluePawn = blue.createPawn();
        Figure bluePawnShoes = ExamFactory.createShoes(bluePawn);
        testSteps(bluePawnShoes, 0, 2, 4, 6, 8);

        Figure blueBishop = blue.createBishop();
        Figure blueBishopShoes = ExamFactory.createShoes(blueBishop);
        testSteps(blueBishopShoes, 0, 8, 16, 24, 32);

        Figure blueQueen = blue.createQueen();
        Figure blueQueenShoes = ExamFactory.createShoes(blueQueen);
        testSteps(blueQueenShoes, 0, 10, 20, 30, 40, 50);
    }

    // ---- dekoratory (kombinacie) ------------------------------------------------------------------------------------

    @Test @Points(2)
    void coatShoes() {
        FigureFactory red = ExamFactory.createRedFigureFactory();
        FigureFactory blue = ExamFactory.createBlueFigureFactory();

        Figure redPawn = red.createPawn();
        Figure redPawnCoat = ExamFactory.createCoat(redPawn);
        Figure redPawnCoatShoes = ExamFactory.createShoes(redPawnCoat);
        testSteps(redPawnCoatShoes, 0, 8, 16, 24, 32);

        Figure redBishop = red.createBishop();
        Figure redBishopCoat = ExamFactory.createCoat(redBishop);
        Figure redBishopCoatShoes = ExamFactory.createShoes(redBishopCoat);
        testSteps(redBishopCoatShoes, 0, 12, 24, 36, 48);

        Figure redQueen = red.createQueen();
        Figure redQueenCoat = ExamFactory.createCoat(redQueen);
        Figure redQueenShoes = ExamFactory.createShoes(redQueenCoat);
        testSteps(redQueenShoes, 0, 18, 36, 54, 72);

        Figure bluePawn = blue.createPawn();
        Figure bluePawnCoat = ExamFactory.createCoat(bluePawn);
        Figure bluePawnShoes = ExamFactory.createShoes(bluePawnCoat);
        testSteps(bluePawnShoes, 0, 8, 16, 24, 32);

        Figure blueBishop = blue.createBishop();
        Figure blueBishopCoat = ExamFactory.createCoat(blueBishop);
        Figure blueBishopCoatShoes = ExamFactory.createShoes(blueBishopCoat);
        testSteps(blueBishopCoatShoes, 0, 14, 28, 42, 56);

        Figure blueQueen = blue.createQueen();
        Figure blueQueenCoat = ExamFactory.createCoat(blueQueen);
        Figure blueQueenCoatShoes = ExamFactory.createShoes(blueQueenCoat);
        testSteps(blueQueenCoatShoes, 0, 16, 32, 48, 64);
    }

    @Test @Points(2)
    void shoesCoat() {
        FigureFactory red = ExamFactory.createRedFigureFactory();
        FigureFactory blue = ExamFactory.createBlueFigureFactory();

        Figure redPawn = red.createPawn();
        Figure redPawnShoes = ExamFactory.createShoes(redPawn);
        Figure redPawnShoesCoat = ExamFactory.createCoat(redPawnShoes);
        testSteps(redPawnShoesCoat, 0, 5, 10, 15, 20);

        Figure redBishop = red.createBishop();
        Figure redBishopShoes = ExamFactory.createShoes(redBishop);
        Figure redBishopShoesCoat = ExamFactory.createCoat(redBishopShoes);
        testSteps(redBishopShoesCoat, 0, 9, 18, 27, 36);

        Figure redQueen = red.createQueen();
        Figure redQueenShoes = ExamFactory.createShoes(redQueen);
        Figure redQueenShoesCoat = ExamFactory.createCoat(redQueenShoes);
        testSteps(redQueenShoesCoat, 0, 15, 30, 45, 60);

        Figure bluePawn = blue.createPawn();
        Figure bluePawnShoes = ExamFactory.createShoes(bluePawn);
        Figure bluePawnShoesCoat = ExamFactory.createCoat(bluePawnShoes);
        testSteps(bluePawnShoesCoat, 0, 5, 10, 15, 20);

        Figure blueBishop = blue.createBishop();
        Figure blueBishopShoes = ExamFactory.createShoes(blueBishop);
        Figure blueBishopShoesCoat = ExamFactory.createCoat(blueBishopShoes);
        testSteps(blueBishopShoesCoat, 0, 11, 22, 33, 44);

        Figure blueQueen = blue.createQueen();
        Figure blueQueenShoes = ExamFactory.createShoes(blueQueen);
        Figure blueQueenShoesCoat = ExamFactory.createCoat(blueQueenShoes);
        testSteps(blueQueenShoesCoat, 0, 13, 26, 39, 52);
    }

    @Test @Points(2)
    void coatCoat() {
        FigureFactory red = ExamFactory.createRedFigureFactory();
        FigureFactory blue = ExamFactory.createBlueFigureFactory();

        Figure redBishop = red.createBishop();
        Figure redBishopCoat = ExamFactory.createCoat(redBishop);
        Figure redBishopCoatCoat = ExamFactory.createCoat(redBishopCoat);
        testSteps(redBishopCoatCoat, 0, 9, 18, 27, 36);

        Figure blueQueen = blue.createQueen();
        Figure blueQueenCoat = ExamFactory.createCoat(blueQueen);
        Figure blueQueenCoatCoat = ExamFactory.createCoat(blueQueenCoat);
        testSteps(blueQueenCoatCoat, 0, 11, 22, 33, 44);
    }

    @Test @Points(2)
    void shoesShoes() {
        FigureFactory red = ExamFactory.createRedFigureFactory();
        FigureFactory blue = ExamFactory.createBlueFigureFactory();

        Figure redBishop = red.createBishop();
        Figure redBishopShoes = ExamFactory.createShoes(redBishop);
        Figure redBishopShoesShoes = ExamFactory.createShoes(redBishopShoes);
        testSteps(redBishopShoesShoes, 0, 12, 24, 36, 48);

        Figure blueBishop = blue.createBishop();
        Figure blueBishopShoes = ExamFactory.createShoes(blueBishop);
        Figure blueBishopShoesShoes = ExamFactory.createShoes(blueBishopShoes);
        testSteps(blueBishopShoesShoes, 0, 16, 32, 48, 64);
    }

    @Test @Points(2)
    void coatCoatShoes() {
        FigureFactory red = ExamFactory.createRedFigureFactory();

        Figure redBishop = red.createBishop();
        Figure redBishopCoat = ExamFactory.createCoat(redBishop);
        Figure redBishopCoatCoat = ExamFactory.createCoat(redBishopCoat);
        Figure redBishopCoatCoatShoes = ExamFactory.createShoes(redBishopCoatCoat);
        testSteps(redBishopCoatCoatShoes, 0, 18, 36, 54, 72);
    }

    @Test @Points(2)
    void shoesCoatShoes() {
        FigureFactory blue = ExamFactory.createBlueFigureFactory();

        Figure blueBishop = blue.createBishop();
        Figure blueishopShoes = ExamFactory.createShoes(blueBishop);
        Figure blueBishopShoesCoat = ExamFactory.createCoat(blueishopShoes);
        Figure blueBishopShoesCoatShoes = ExamFactory.createShoes(blueBishopShoesCoat);
        testSteps(blueBishopShoesCoatShoes, 0, 22, 44);
    }

    // ---- dekorator (aplikovany neskor) ------------------------------------------------------------------------------

    @Test @Points(2)
    void coatLater() {
        FigureFactory red = ExamFactory.createRedFigureFactory();

        Figure redBishop = red.createBishop();
        redBishop.move();
        assertEquals(3, redBishop.getPosition());

        Figure redBishopCoat = ExamFactory.createCoat(redBishop);
        assertEquals(3, redBishopCoat.getPosition());
        redBishopCoat.move();
        assertEquals(9, redBishopCoat.getPosition());
    }

    @Test @Points(2)
    void coatLaterB() {
        FigureFactory red = ExamFactory.createRedFigureFactory();

        Figure redBishop = red.createBishop();
        redBishop.move();
        redBishop.move();
        assertEquals(6, redBishop.getPosition());

        Figure redBishopCoat = ExamFactory.createCoat(redBishop);
        assertEquals(6, redBishopCoat.getPosition());
        redBishopCoat.move();
        assertEquals(12, redBishopCoat.getPosition());
    }

    @Test @Points(2)
    void shoesLater() {
        FigureFactory blue = ExamFactory.createBlueFigureFactory();

        Figure blueQueen = blue.createQueen();
        blueQueen.move();
        assertEquals(5, blueQueen.getPosition());

        Figure blueQueenShoes = ExamFactory.createShoes(blueQueen);
        assertEquals(5, blueQueenShoes.getPosition());
        blueQueenShoes.move();
        assertEquals(15, blueQueenShoes.getPosition());
    }

    @Test @Points(2)
    void shoesLaterB() {
        FigureFactory blue = ExamFactory.createBlueFigureFactory();

        Figure blueQueen = blue.createQueen();
        blueQueen.move();
        blueQueen.move();
        assertEquals(10, blueQueen.getPosition());

        Figure blueQueenShoes = ExamFactory.createShoes(blueQueen);
        assertEquals(10, blueQueenShoes.getPosition());
        blueQueenShoes.move();
        assertEquals(20, blueQueenShoes.getPosition());
    }
}
