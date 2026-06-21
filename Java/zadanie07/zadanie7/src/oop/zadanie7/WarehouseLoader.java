package oop.zadanie7;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.io.IOException;
import java.time.LocalDate;
import java.time.format.DateTimeParseException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class WarehouseLoader {

    public List<Product> loadProducts(String filename) throws InvalidProductFormatException {
        List<Product> products = new ArrayList<>();

        // Použitie try-with-resources pre automatické zatvorenie zdroja
        try (BufferedReader reader = new BufferedReader(new FileReader(filename))) {
            String line;
            while ((line = reader.readLine()) != null) {
                // Preskočenie prípadných prázdnych riadkov
                if (line.trim().isEmpty()) {
                    continue;
                }

                String[] parts = line.split(",");
                if (parts.length != 5) {
                    throw new InvalidProductFormatException("Nesprávny počet stĺpcov v riadku: " + line);
                }

                String type = parts[0].trim();
                String id = parts[1].trim();
                String name = parts[2].trim();
                double price;

                try {
                    price = Double.parseDouble(parts[3].trim());
                } catch (NumberFormatException e) {
                    throw new InvalidProductFormatException("Neplatný formát ceny v riadku: " + line);
                }

                if ("E".equals(type)) {
                    try {
                        int warrantyMonths = Integer.parseInt(parts[4].trim());
                        products.add(new ElectronicProduct(id, name, price, warrantyMonths));
                    } catch (NumberFormatException e) {
                        throw new InvalidProductFormatException("Neplatný formát záruky (nie je číslo) v riadku: " + line);
                    }
                } else if ("P".equals(type)) {
                    try {
                        LocalDate expirationDate = LocalDate.parse(parts[4].trim());
                        products.add(new PerishableProduct(id, name, price, expirationDate));
                    } catch (DateTimeParseException e) {
                        throw new InvalidProductFormatException("Neplatný formát dátumu v riadku: " + line);
                    }
                } else {
                    throw new InvalidProductFormatException("Neznámy typ produktu (očakáva sa E alebo P): " + type);
                }
            }
        } catch (IOException e) {
            throw new InvalidProductFormatException("Chyba pri čítaní: " + e.getMessage());
        }

        // Zadanie vyžaduje zoradenie načítaných produktov podľa ID
        Collections.sort(products);
        return products;
    }

    public void saveProducts(List<Product> products, String filename) {
        // Použitie try-with-resources pre PrintWriter
        try (PrintWriter writer = new PrintWriter(new FileWriter(filename))) {
            for (Product p : products) {
                if (p instanceof ElectronicProduct) {
                    ElectronicProduct ep = (ElectronicProduct) p;
                    writer.println("E," + ep.getId() + "," + ep.getName() + "," + ep.getPrice() + "," + ep.getWarrantyMonths());
                } else if (p instanceof PerishableProduct) {
                    PerishableProduct pp = (PerishableProduct) p;
                    writer.println("P," + pp.getId() + "," + pp.getName() + "," + pp.getPrice() + "," + pp.getExpirationDate());
                }
            }
        } catch (IOException e) {
            System.err.println("Chyba pri zápise do súboru: " + e.getMessage());
        }
    }
}