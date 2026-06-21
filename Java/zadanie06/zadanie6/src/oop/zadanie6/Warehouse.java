package oop.zadanie6;

import java.util.HashSet;
import java.util.Set;

public class Warehouse {
    private Set<Product> products;

    public Warehouse(){
        this.products = new HashSet<>();
    }

    public void addProduct(Product p) throws ProductAlreadyExistsException{
        if(products.contains(p)){
            throw new ProductAlreadyExistsException("Product s ID '" + p.getId() + "' sa v sklade už nachádza.");
        }
        products.add(p);
    }

    public void removeProduct(String id) throws ProductNotFoundException{
        Product toRemove = null;
        for(Product p : products){
            if(p.getId().equals(id)){
                toRemove = p;
                break;
            }
        }

        if(toRemove != null){
            products.remove(toRemove);
        } else {
            throw new ProductNotFoundException("Product s ID '" + id + "' sa v sklade nenachádza.");
        }
    }

    public int getProductCount(){
        return products.size();
    }
}
