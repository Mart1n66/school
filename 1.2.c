#include<stdio.h>

int posun(int kroky, unsigned int cislo) {
    int pocet_bitov, povodne_cislo = cislo;
    while (povodne_cislo > 0) {
        povodne_cislo = povodne_cislo / 2;
        pocet_bitov++;
    }
    kroky = kroky % pocet_bitov;
    return cislo >> kroky | (cislo << (pocet_bitov - kroky) & (1 << pocet_bitov) - 1);
}
int vypis_v_bin(unsigned int cislo) {
    int bin_cislo[32];
    int i = 0;
    while (cislo > 0) {
        bin_cislo[i] = cislo % 2;
        cislo = cislo / 2;
        i++;
    }
    for (int j = i-1; j >= 0; j--) {
        printf("%d",bin_cislo[j]);
    }
}

int main() {
    unsigned int a = 5;
    int kroky = 27;
    printf("%d\n",a);
    //kroky = kroky%4;
    a = posun(kroky,a);
    printf("%d\n",a);
    vypis_v_bin(a);
    return 0;
}
