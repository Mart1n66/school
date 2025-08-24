#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "functions.h" // Swish funkcia a pomocne funkcie -- NEMENIT !!!
#include "data.h" // Makra, vahy a bias hodnoty -- NEMENIT !!!

double hladanie_vahy(int neuron, int riadok, int stlpec) {
        return weights[784*neuron + 28*riadok + stlpec];
}

double sucet(double vstup[IMAGE_SIZE],double weights[NUMBER_OF_WEIGHTS], int k) {
    double suma = 0;
    for (int i = 0; i < IMAGE_SIZE; i++) {
        suma += weights[(k*IMAGE_SIZE) + i] * vstup[i];
    }
    return suma;
}
int findmax(double pole[]) {
    int max = 0;
    for (int i = 0; i < NUMBER_OF_NEURONS; i++) {
        if (pole[max] < pole[i]) {
            max = i;
        }
    }
    return max;
}

double maximum(double pole[]) {
    double max = pole[0];
    for (int i = 0; i < NUMBER_OF_NEURONS; i++) {
        if (max < pole[i]) {
            max = pole[i];
        }
    }
    return max;
}

void softmax_vypis(double z[]) {
    double vysledne_pole[10];
    double max = maximum(z);
    for (int k = 0; k < 10; k++) {
        double suma = 0;
        for (int i = 0; i < 10; i++) {
            suma += exp(z[i] - max);
        }
        vysledne_pole[k] = (exp(z[k]- max))/suma;
        printf("%.2lf ", vysledne_pole[k]);
    }
}

int softmax_index(double z[]) {
    double vysledne_pole[10];
    double max = maximum(z);
    for (int k = 0; k < 10; k++) {
        double suma = 0;
        for (int i = 0; i < 10; i++) {
            suma += exp(z[i] - max);
        }
        vysledne_pole[k] = (exp(z[k]- max))/suma;
    }
    int index;
    index = findmax(vysledne_pole);
    return index;
}

int main() {
    double vstup[IMAGE_SIZE];
    double vystup[NUMBER_OF_NEURONS];
    int a;
    scanf("%d",&a);
    if (a == 1) {
        load_image(vstup, IMAGE_SIZE);
        print_image(vstup,28,28);
        return 0;
    }
    if (a == 2) {
        int neuron, riadok , stlpec;
        scanf("%d %d %d",&neuron,&riadok,&stlpec);
        printf("%.2lf",hladanie_vahy(neuron, riadok, stlpec));
        return 0;
    }
    if (a == 3) {
        load_image(vstup, IMAGE_SIZE);
        for (int k = 0; k < NUMBER_OF_NEURONS; k++) {
            vystup[k] = sucet(vstup, weights, k) + bias[k];
            printf("%8d%8.2lf\n",k,sucet(vstup, weights, k) + bias[k]);//pri vypise na 3 miesta vypise .865 a na 2 vypise .87 (co je nespravne)
        }
        return 0;
    }
    if (a == 4) {
        double pole[10];
        for (int k = 0; k < NUMBER_OF_NEURONS; k++) {
            scanf("%lf",&pole[k]);
        }
        softmax_vypis(pole);
        return 0;
    }
    if (a == 5) {
        double pole[10];
        for (int k = 0; k < NUMBER_OF_NEURONS; k++) {
            scanf("%lf",&pole[k]);
        }
        printf("%d",findmax(pole));
        return 0;
    }
    if (a == 6) {
        load_image(vstup, IMAGE_SIZE);
        double neuron[10];
        for (int k = 0; k < NUMBER_OF_NEURONS; k++) {
            neuron[k] = swish(sucet(vstup, weights, k) + bias[k]);
        }
        printf("%d",softmax_index(neuron));
        return 0;
    }
    if (a == 7) {
        double spravny_odhad = 0.0;
        int parameter;
        scanf("%d",&parameter);
        int spravne[parameter];
        int vystupne[parameter];
        double cislo = parameter;
        for (int k = 0; k < parameter; k++) {
            scanf("%d",&spravne[k]);
        }
        for (int i = 0; i < parameter; i++) {
            load_image(vstup, IMAGE_SIZE);
            double neuron[10];
            for (int k = 0; k < NUMBER_OF_NEURONS; k++) {
                neuron[k] = swish(sucet(vstup, weights, k) + bias[k]);
            }
            vystupne[i]= softmax_index(neuron);
            if (vystupne[i] == spravne[i]) {
                spravny_odhad += 1.0;
            }
        }
        printf("%.2lf ",spravny_odhad/cislo*100);
        for (int j = 0; j < parameter; j++) {
            printf("%d-%d-%d ",j,spravne[j],vystupne[j]);
        }
        return 0;
        }
    }

