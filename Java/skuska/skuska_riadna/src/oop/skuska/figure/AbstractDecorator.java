package oop.skuska.figure;

public abstract class AbstractDecorator implements Figure{
    protected Figure wrapped;

    @Override
    public int getPosition(){
        return wrapped.getPosition();
    }

    @Override
    public void setPosition(int position) {
        wrapped.setPosition(position);
    }
}
