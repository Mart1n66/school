#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MMAX 1000

const char *readline() {
    static char buffer[MMAX + 1];
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    return buffer;
}

int main() {
    char op[101];
    char mem[101];
    op[0] = '\0';
    mem[0] = '\0';
    char *vstup, *token, *zbytok, *sp = op, *ep = op;
    char *start, *end;
    while (1) {
        vstup = readline();
        token = strtok(vstup, " ");
        zbytok = strtok(NULL, "\n");
        if (zbytok && strlen(zbytok) > 100) {
            printf("ERR_OVERFLOW\n");
            return 0;
        }
        if (!token && !zbytok)
            continue;
        if (strcmp(token,"in") == 0) {
            if (zbytok) {
                strcpy(op, zbytok);
            }
            sp = op;
            start = op;
            ep = op + strlen(op);
            end = op + strlen(op);
        }
        if (strcmp(token,"out") == 0 && zbytok) {
            if (strcmp(zbytok, "op") == 0) {
                printf("%s\n", op);
            }
            else if (strcmp(zbytok, "range") == 0) {
                char *temp_sp = sp;
                while (temp_sp < ep && *temp_sp != '\0') {
                    putchar(*temp_sp);
                    temp_sp++;
                }
            }
            else if (strcmp(zbytok, "mem") == 0) {
                printf("%s\n", mem);
            }
        }
        else if (strcmp(token,"move") == 0 && zbytok) {
            char *token2 = strtok(zbytok, " ");
            char *zbytok2 = strtok(NULL, "\n");
            int cislo = atoi(zbytok2);
            if (strcmp(token2,"sp") == 0) {
                if (sp+cislo > end || sp+cislo < start) {
                    printf("ERR_OUT_OF_RANGE\n");
                    return 0;
                }
                sp = sp + cislo;
            }
            if (strcmp(token2,"ep") == 0) {
                if (ep+cislo > end || ep+cislo < start) {
                    printf("ERR_OUT_OF_RANGE\n");
                    return 0;
                }
                ep = ep + cislo;
            }
        }
        else if (strcmp(token,"start") == 0 && zbytok) {
            if (strcmp(zbytok, "sp") == 0) {
                sp = start;
            }
            if (strcmp(zbytok, "ep") == 0) {
                ep = start;
            }
        }
        else if (strcmp(token,"end") == 0 && zbytok) {
            if (strcmp(zbytok, "sp") == 0) {
                sp = end;
            }
            if (strcmp(zbytok, "ep") == 0) {
                ep = end;
            }
        }
        else if (strcmp(token, "first") == 0) {
            sp = start;
            ep = start;
            for (int i = 0; i < strlen(op); i++) {
                if (isalnum(op[i])) {
                    int c = i;
                    sp = &op[i];
                    while (1) {
                        c++;
                        if (!isalnum(op[c])) {
                             ep = &op[c];
                            break;
                        }
                    }
                    break;
                }
            }
        }
        else if (strcmp(token, "last") == 0) {
           sp = end;
            ep = end;
            for (int i = strlen(op)-1; i >= 0; i--) {
                if (isalnum(op[i])) {
                    int c = i;
                    ep = &op[i]+1;
                    while (1) {
                        c--;
                        if (!isalnum(op[c])) {
                            sp = &op[c]+1;
                            break;
                        }
                    }
                    break;
                }
            }
        }
        else if (strcmp(token, "prev") == 0) {
            char *start_slova;
            char *end_slova = sp-1;
            while (isalnum(*end_slova)) {
                end_slova--;
            }
            while (!isalnum(*end_slova)) {
                end_slova--;
            }
            if (end_slova < start) {
                sp = op;
                ep = op;
                continue;
            }
            ep = end_slova + 1;
            start_slova = end_slova-1;
            while (isalnum(*start_slova)) {
                start_slova--;
            }
            sp = start_slova+1;
        }
        else if (strcmp(token, "next") == 0) {
            char *start_slova = sp+1;
            char *end_slova;
            while (isalnum(*start_slova)) {
                start_slova++;
            }
            while (!isalnum(*start_slova)) {
                start_slova++;
            }
            if (start_slova > end) {
                sp = end;
                ep = end;
                continue;
            }
            sp = start_slova;
            end_slova = start_slova;
            while (isalnum(*end_slova)) {
                end_slova++;
            }
            ep = end_slova;
        }
        else if (strcmp(token, "del") == 0) {
            if (sp > ep) {
                printf("ERR_POSITION\n");
                return 0;
            }
            if (sp == ep) {
                continue;
            }
            else;
            char *povodne_sp = sp;
            /*if (ep > op && *(ep - 1) == ' ') {
                ep--;
            }*/
            while (*ep) {
                *sp = *ep;
                sp++;
                ep++;
            }
            *sp = '\0';
            sp = povodne_sp;
            ep = povodne_sp;
        }
        else if (strcmp(token, "quit") == 0) {
            break;
        }
    }
    return 0;
}
