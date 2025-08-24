#include<stdio.h>
#include<float.h>

int main() {
    uloha4();
    return 0;
}

void uloha4(){
    float epsilon1 = 1.0f;
    double epsilon2 = 1.0;
    printf("%.20e\n",__FLT_EPSILON__);
    printf("%.20e\n\n",__DBL_EPSILON__);
    while((1.0f + epsilon1/2) > 1.0) {
        epsilon1 = epsilon1/2.0f;
    }
    printf("%.20e\n",epsilon1);

    while(1.0 + epsilon2>1.0) {
        epsilon2 = epsilon2/2;
    }
    epsilon2 = epsilon2*2;
    printf("%.20e\n",epsilon2);
}
