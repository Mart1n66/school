#include<stdio.h>

int pocitanie(int a) {
    int pocet = 0;
    while (a>0) {
        if((a&1) == 1){
        pocet++;
        }
        a >>= 1;
    }
    return pocet;
}

int main() {
    int cislo = 17, vysledok;
    vysledok = pocitanie(cislo);
    printf("%d jednotky",vysledok);
    return 0;
}
