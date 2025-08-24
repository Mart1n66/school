void uloha2_1_1() {
    int iCislo = 5;
    int iCislo2 = 6;
    int iVysledok;
    __asm__ (
    "movl %[iCislo], %%eax\n\t"
    "movl %[iCislo2], %%ecx\n\t"
    "addl %%ecx, %%eax\n\t"
    "movl %%eax, %[iVysledok]\n\t"
    : [iVysledok] "=r" (iVysledok)
    : [iCislo] "r" (iCislo), [iCislo2] "r" (iCislo2)
    : "%eax","ecx"
    );
    printf("%d %d %d\n", iCislo, iCislo2, iVysledok);
}
void uloha2_1_2() {
    int iCislo = 10     ;
    int iVysledok;
    __asm__ (
    "movl %[iCislo], %%eax\n\t"
    "shll %%eax\n\t"
    "movl %%eax, %[iVysledok]\n\t"
    : [iVysledok] "=r" (iVysledok)
    : [iCislo] "r" (iCislo)
    : "%eax","ecx"
    );
    printf("%d %d\n", iCislo,  iVysledok);
}
void uloha2_1_3() {
    int iCislo = 14;
    int iVysledok;

    __asm__ (
        "movl %[iCislo], %%eax\n\t"
        "cmpl $10, %%eax\n\t"
        "jl mensie\n\t"
        "addl $55,%%eax\n\t"
        "jmp end\n\t"
        "mensie:\n\t"
        "addl $'0',%%eax\n\t"
        "end:\n\t"
        "movl %%eax,%[iVysledok]\n\t"
        : [iVysledok] "=r" (iVysledok)
        : [iCislo] "r" (iCislo)
        : "%eax", "%ecx"
    );

    printf("%d %c\n", iCislo, iVysledok);
    return 0;
}
void uloha2_1_4(){
unsigned int eax, ebx, ecx, edx;
    char vysledok[12];
    __asm__ (
    "movl $0, %%eax\n\t"
    "CPUID\n\t"
    "movl %%ebx, %[ebx]\n\t"
    "movl %%edx, %[edx]\n\t"
    "movl %%ecx, %[ecx]\n\t"
    : [ebx] "=r" (ebx), [ecx] "=r" (ecx), [edx] "=r" (edx)
    :
    : "%eax", "%ebx", "%ecx", "%edx"
    );
    *((unsigned int*)&vysledok[0]) = ebx;
    *((unsigned int*)&vysledok[4]) = edx;
    *((unsigned int*)&vysledok[8]) = ecx;
    vysledok[12] = '\0';
    printf("%s", vysledok);
}
void uloha2_2(){
    char pole[] = "ap je super predmet";
    char *pointer = pole;
    printf("%s\n",pole);
    printf("%p\n",pointer);

    pointer++;
    *pointer = 'A';
    printf("%s\n",pole);
    printf("%p\n",pointer);

   /* pointer += 100000000;
    *pointer = 'B';
    printf("%s\n",pole);
    printf("%p\n",pointer); padne program*/

    int cisla[] = {1,2,3,4};
    for(int i=0;i<4;i++) {
        printf("%d",cisla[i]);
    }
    printf("\n");
    int *ptr = cisla;
    printf("%p\n",ptr);
    ptr++;
    *ptr = 99;
    for(int i=0;i<4;i++) {
        printf("%d ",cisla[i]);
    }
    printf("\n");
    printf("%p\n",ptr);
}
void uloha2_5_1(){
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int farba;
    for(int i=0;i<=50;i++) {
        if (i >= 0 && i <= 10) {
            farba = 10;
        }
        else if (i >= 11 && i <= 22) {
            farba = 12;
        }
        else if (i >= 23 && i <= 35) {
            farba = 9;
        }
        else
            farba = 14;
        SetConsoleTextAttribute(hConsole,farba);
        printf("%03d\n",i);
        //sleep(1);
    }
    SetConsoleTextAttribute(hConsole, 7);
}
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void uloha2_5_2(){
    int x = 1, y = 5;
    char meno[] = "martin ";
    char vyska[] = "180 cm";
    char hmotnost[] = "80 kg";
    char telefon[] = "0907 / 123 4515465435546";


    int maxLen = strlen(meno);
    if (strlen(vyska) > maxLen) maxLen = strlen(vyska);
    if (strlen(hmotnost) > maxLen) maxLen = strlen(hmotnost);
    if (strlen(telefon) > maxLen) maxLen = strlen(telefon);


    char horne_rohy[] = {201, 187, 0};
    char dolne_rohy[] = {200, 188, 0};
    char bocne = 186;
    char vodorovne = 205;

    setColor(14);
    gotoxy(x, y);
    printf("%c", horne_rohy[0]);
    for (int i = 0; i < (((maxLen + 15))- 9)/2; i++) printf("%c", vodorovne);
    setColor(10);
    printf("Zaznam 001");
    setColor(14);
    for (int i = 0; i < (((maxLen + 15))- 10)/2; i++) printf("%c", vodorovne);
    printf("%c", horne_rohy[1]);
    gotoxy(x, y + 1);
    printf("%c", bocne);
    for (int i = 0; i < maxLen + 15; i++) printf("%c", vodorovne);
    printf("%c", bocne);

    setColor(14);
    gotoxy(x, y + 2);
    printf("%c ", bocne);
    setColor(10);
    printf("Meno       ");
    setColor(14);
    printf("%c ", bocne);
    setColor(10);
    printf("%-*s ", maxLen, meno);
    setColor(14);
    printf("%c", bocne);

    gotoxy(x, y + 3);
    printf("%c ", bocne);
    setColor(10);
    printf("Vyska      ");
    setColor(14);
    printf("%c ", bocne);
    setColor(10);
    printf("%-*s ", maxLen, vyska);
    setColor(14);
    printf("%c", bocne);

    gotoxy(x, y + 4);
    printf("%c ", bocne);
    setColor(10);
    printf("Hmotnost   ");
    setColor(14);
    printf("%c ", bocne);
    setColor(10);
    printf("%-*s ", maxLen, hmotnost);
    setColor(14);
    printf("%c", bocne);

    gotoxy(x, y + 5);
    printf("%c ", bocne);
    setColor(10);
    printf("Tel.       ");
    setColor(14);
    printf("%c ", bocne);
    setColor(10);
    printf("%-*s ", maxLen, telefon);
    setColor(14);
    printf("%c", bocne);

    setColor(14);
    gotoxy(x, y + 6);
    printf("%c", dolne_rohy[0]);
    for (int i = 0; i < maxLen + 15; i++) printf("%c", vodorovne);
    printf("%c", dolne_rohy[1]);

    gotoxy(5, y + 9);
    setColor(7);
    printf("Stlacte ENTER");
    getchar();
}
void print_menu(){
char bocne = 186;
    char vodorovne = 205;
    char lh = 201, ph = 187,ld = 200, pd = 188;
    printf("%c",lh);
    for(int i = 0;i<50;i++){
        printf("%c",205);
    }
    printf("%c\n",ph);
    printf("%c",bocne);
    for(int i = 0;i<23;i++){
        printf(" ");
    }
    printf("NAVOD");
    for(int i = 0;i<22;i++){
        printf(" ");
    }
    printf("%c\n",bocne);
    printf("%c",bocne);
    for(int i = 0;i<50;i++){
        printf("%c",205);
    }
    printf("%c\n",bocne);
    printf("%c",bocne);
    printf("po zadani F2 sa vygeneruje pismeno, po zadani toho%c\n%cznaku sa vypise cas trvania, pre koniec stlac F10!%c\n",186,186,186);
    printf("%c",ld);
    for(int i = 0;i<50;i++){
        printf("%c",205);
    }
    printf("%c\n",pd);
}
void uloha2_6() {
    srand(time(NULL));
    clock_t start, koniec;
    float trvanie;
    char hadanie;
    char znak = '\0';
    unsigned char ch;
    int i = 0;
    do  {
        if(kbhit())
        { ch = getch();
        if (ch == 0x00 || ch == 0xE0){
            unsigned char ch2 = getch();
            if(ch2 == 59){
                print_menu();
                sleep(2);
                system("cls");
                znak = ' ';
            }
            if(ch2 == 60){
                znak = 'a' + rand() % 26;
                gotoxy(60,14);
                printf("%c",znak);
                start = clock();

            }
            if(ch2 == 68){
                break;
            }
        }
        if(ch == znak){
            koniec = clock();
            trvanie = (float)(koniec-start)/CLOCKS_PER_SEC;
            gotoxy(60,15);
            printf("cas trvania: %lf\n",trvanie);
            sleep(2);
            system("cls");
            znak = '\0';
        }
        }
    } while(1);
}
void uloha2_3_1(){
 FILE *fr, *fw;
 int c;

 fr = fopen("poviedka.html","r");
 fw = fopen("oprava.html","w");

    while ((c = getc(fr)) != EOF) {
        switch (c) {
            case 65: c = 66;
            case 165: c = 188; break;
            case 169: c = 138; break;
            case 171: c = 141; break;
            case 174: c = 142; break;
            case 181: c = 190; break;
            case 185: c = 154; break;
            case 187: c = 157; break;
            case 190: c = 158; break;

        }
        fputc(c, fw);
    }

 fclose(fr);
 fclose(fw);
 }
 void uloha2_3_2(){
  FILE *fr, *fw;
 int c;

 fr = fopen("koniec.html","r");
 fw = fopen("opravakonca.html","w");

    while ((c = getc(fr)) != EOF) {
        c = c^27;
        fputc(c, fw);
    }
 fclose(fr);
 fclose(fw);
 }
