package oop.skuska.figure;

public class RedQueen extends AbstractFigures implements Figure{

     public RedQueen(){
         this.position = 0;
     }

    @Override
    public void move(){
        position += 6;
    }
}
