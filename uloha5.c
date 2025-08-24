#include<stdio.h>
#include<math.h>


float sinus(float uhol, float epsilon) {
    float ity_clen = uhol;
    float vysledok = uhol;
    int i = 1;
    while (fabs(ity_clen) >= epsilon) {
        ity_clen = ity_clen * -uhol * uhol / ((2*i) * (2*i+1));
        vysledok += ity_clen;
        i++;
    }
    return vysledok;
}

int main() {
    float uhol;
    char deg_alebo_rad;
    float epsilon = 0.00000000001;
    scanf("%f",&uhol);
    scanf(" %c",&deg_alebo_rad);
    if (deg_alebo_rad == 's') {
        uhol = uhol * M_PI/180.0;
    }
    printf("uhol v rad %f\n",uhol);
    while(uhol > M_PI){
            uhol -= 2*M_PI;
    }
    while(uhol < M_PI){
        uhol += 2*M_PI;
    }
    printf("%.10f\n",sinus(uhol,epsilon));
    return 0;
}

