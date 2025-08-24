#include<stdio.h>

void uloha1(int a, char b) {
    int bin_a[100];
    int bin_b[100];
    int i = 0,j,pocet;
    printf("Dec %d\n",a);
    printf("Hex %x\n",a);
    while (a > 0) {
        bin_a[i] = a % 2;
        a = a / 2;
        i++;
        pocet = i-1;
    }
    printf("Bin ");
    for (j = pocet; j >= 0; j--) {
        printf("%d",bin_a[j]);
    }
    printf("\n\n");
    printf("Dec %d\n",b);
    printf("Hex %x\n",b);
    i = 0;
    while (b > 0) {
        bin_b[i] = b % 2;
        b = b / 2;
        i++;
        pocet = i-1;
    }
    printf("Bin ");
    for (j = pocet; j >= 0; j--) {
        printf("%d",bin_b[j]);
    }
}

int main() {
    int a = 33777;
    char b = 'X';
    uloha1(a,b);
    return 0;
}
