package oop.zadanie6;

public class PerishableProduct extends Product {
    private int expirationDays;

    public PerishableProduct(String id, String name, double price, int expirationDays) {
        super(id, name, price);
        this.expirationDays = expirationDays;
    }

    public int getExpirationDays() {
        return expirationDays;
    }

    public void setExpirationDays(int expirationDays) {
        this.expirationDays = expirationDays;
    }

    @Override
    public String toString() {
        return "PerishableProduct{" + "id='" + getId() + '\'' + ", name='" + getName() + '\'' + ", price=" + getPrice() + ", expirationDays=" + expirationDays + '}';
    }
}
