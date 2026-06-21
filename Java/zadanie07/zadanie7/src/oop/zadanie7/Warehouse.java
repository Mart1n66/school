package oop.zadanie7;

import java.util.*;
import java.util.stream.Collectors;

public class Warehouse {
    private Map<String, Product> products;

    public Warehouse() {
        this.products = new HashMap<>();
    }

    public void addProduct(Product p) throws ProductAlreadyExistsException {
        if (products.containsKey(p.getId())) {
            throw new ProductAlreadyExistsException("Product s ID '" + p.getId() + "' sa v sklade už nachádza.");
        }
        products.put(p.getId(), p);
    }

    public void removeProduct(String id) throws ProductNotFoundException {
        if(products.remove(id) == null){
            throw new ProductNotFoundException("Produkt s ID '" + id + "' sa v sklade nenachádza.");
        }
    }

    public Product getProduct(String id){
        return products.get(id);
    }

    public int getProductCount(){
        return products.size();
    }

    public List<Product> findProductsByPriceRange(double min, double max){
        return products.values().stream()
                .filter(p -> p.getPrice() >= min && p.getPrice() <= max)
                .collect(Collectors.toList());
    }

    public List<Product> getProductsSortedByPrice() {
        return products.values().stream()
                .sorted(Comparator.comparingDouble(Product::getPrice))
                .collect(Collectors.toList());
    }

    public List<Product> getProductsSortedById() {
        return products.values().stream()
                .sorted()
                .collect(Collectors.toList());
    }

    public <T> List<T> getProductsByType(Class<T> type){
        return products.values().stream()
                .filter(type::isInstance)
                .map(type::cast)
                .collect(Collectors.toList());
    }

    public Product findProductWithSmallestId(){
        if(products.isEmpty()) return null;

        Product smallest = null;
        for(Product p : products.values()){
            if(smallest == null || p.compareTo(smallest) < 0){
                smallest = p;
            }
        }
        return smallest;
    }

    public double calculateTotalValue(){
        return products.values().stream()
                .mapToDouble(Product::getPrice)
                .sum();
    }


}
