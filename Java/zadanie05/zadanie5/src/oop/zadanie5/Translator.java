package oop.zadanie5;

import java.util.HashMap;
import java.util.Map;

public class Translator {
    private Map<String, String> dictionary;

    public Translator(){
        this.dictionary = new HashMap<>();
    }

    public void set(String word, String translation){
        this.dictionary.put(word, translation);
    }

    public String translate(String word){
        return this.dictionary.get(word);
    }

    public boolean canTranslate(String word){
        return this.dictionary.containsKey(word);
    }

    public int getSize(){
        return  this.dictionary.size();
    }
}
