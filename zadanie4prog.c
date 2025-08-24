#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h" // NEMENIT, inak vas kod neprejde testom !!!

// chybove hlasenia
#define ERR_UNIT_COUNT "ERR_UNIT_COUNT"
#define ERR_ITEM_COUNT "ERR_ITEM_COUNT"
#define ERR_WRONG_ITEM "ERR_WRONG_ITEM"
#define ERR_SLOTS "ERR_SLOTS"

const ITEM* find_item(const char *zadany_predmet) {
    for (int i = 0; i < NUMBER_OF_ITEMS; i++) {
        if (strcmp(items[i].name, zadany_predmet) == 0) {
            return &items[i];
        }
    }
    return NULL;
}

int nacitaj_armadu(UNIT *units, int *pocet) {
    scanf("%d", pocet);
    getchar();
    if (*pocet < MIN_ARMY || *pocet > MAX_ARMY) {
        printf(ERR_UNIT_COUNT);
        return 0;
    }
    for (int i = 0; i < *pocet; i++) {
        int pocet_zabranych_slotov = 0;
        char vstup[500];
        fgets(vstup, 500, stdin);
        vstup[strcspn(vstup, "\n")] = 0;
        char *slovo = strtok(vstup, " ");
        strcpy(units[i].name, slovo);
        slovo = strtok(NULL, " ");
        if (slovo == NULL) {
            printf(ERR_ITEM_COUNT);
            return 0;
        }
        const ITEM *item1 = find_item(slovo);
        if (item1 == NULL) {
            printf(ERR_WRONG_ITEM);
            return 0;
        }
        units[i].item1 = item1;
        pocet_zabranych_slotov += item1->slots;
        slovo = strtok(NULL, " ");
        if (slovo != NULL) {
            const ITEM *item2 = find_item(slovo);
            if (item2 == NULL) {
                printf(ERR_WRONG_ITEM);
                return 0;
            }
            units[i].item2 = item2;
            pocet_zabranych_slotov += item2->slots;
        }
        else
            units[i].item2 = NULL;
        slovo = strtok(NULL, " ");
        if (slovo != NULL) {
            printf(ERR_ITEM_COUNT);
            return 0;
        }
        if (pocet_zabranych_slotov >2) {
            printf(ERR_SLOTS);
            return 0;
        }
        units[i].hp = 100;
    }
    return 1;
}

void vypis_armady(UNIT *units, int *pocet, const char *nazov) {
    printf("%s\n",nazov);
    for (int i = 0; i < *pocet; i++) {
        printf("   Unit: %d\n",i);
        printf("   Name: %s\n",units[i].name);
        printf("   HP: %d\n",units[i].hp);
        printf("   Item 1: %s, %d, %d, %d, %d, %d\n",units[i].item1->name,units[i].item1->att,units[i].item1->def,units[i].item1->slots,units[i].item1->range,units[i].item1->radius);
        if (units[i].item2 != NULL) {
            printf("   Item 2: %s, %d, %d, %d, %d, %d\n",units[i].item2->name,units[i].item2->att,units[i].item2->def,units[i].item2->slots,units[i].item2->range,units[i].item2->radius);
        }
        printf("\n");
    }
}

int is_game_over(UNIT *units1, UNIT *units2) {
    if (units1[0].hp <= 0 || units2[0].hp <= 0) {
        return 1;
    }
    return 0;
}

void print_units(UNIT *units1, UNIT *units2, int *pocet1, int *pocet2) {
    printf("1: ");
    for (int i = 0; i < *pocet1; i++) {
        printf("%s,%d ", units1[i].name,units1[i].hp);
    }
    printf("\n");
    printf("2: ");
    for (int i = 0; i < *pocet2; i++) {
        printf("%s,%d ", units2[i].name,units2[i].hp);
    }
    printf("\n");
}

void atack_army(UNIT *units1, UNIT *units2, int *pocet1, int *pocet2) {
    int total_def[MAX_ARMY];
    for (int i = 0; i < *pocet2; i++) {
        total_def[i] = units2[i].item1->def;
        if (units2[i].item2 != NULL) {
            total_def[i] += units2[i].item2->def;
        }
    }
    for (int i = 0; i < *pocet1; i++) {
        if (i <= units1[i].item1->range) {
            for (int j = 0; j <= units1[i].item1->radius && j < *pocet2; j++) {
                int dmg = units1[i].item1->att - total_def[j];
                units2[j].hp -= dmg > 1 ? dmg : 1;

            }
        }
        if (units1[i].item2 != NULL) {
            if (i <= units1[i].item2->range) {
                for (int j = 0; j <= units1[i].item2->radius && j < *pocet2; j++) {
                    units2[j].hp -= (units1[i].item2->att - total_def[j]) > 1 ? units1[i].item2->att - total_def[j] : 1;

                }
            }
        }
    }
}

void print_damage(UNIT *units1, UNIT *units2, int *pocet1, int *pocet2) {
    int total_def[MAX_ARMY];
    for (int i = 0; i < *pocet2; i++) {
        total_def[i] = units2[i].item1->def;
        if (units2[i].item2 != NULL) {
            total_def[i] += units2[i].item2->def;
        }
    }
    for (int i = 0; i < *pocet1; i++) {
        if (i <= units1[i].item1->range) {
            for (int j = 0; j <= units1[i].item1->radius && j < *pocet2; j++) {
                printf("%d, %s, %s:   [%s,%d]\n",i+1, units1[i].name,units1[i].item1->name,units2[j].name, units1[i].item1->att - total_def[j] > 1 ? units1[i].item1->att - total_def[j] : 1);
            }
        }
        if (units1[i].item2 != NULL && i <= units1[i].item2->range) {
            for (int j = 0; j <= units1[i].item2->radius && j < *pocet2; j++) {
                printf("%d, %s, %s:   [%s,%d]\n",i+1, units1[i].name,units1[i].item2->name,units2[j].name, units1[i].item2->att - total_def[j] > 1 ? units1[i].item2->att - total_def[j] : 1);
            }
        }
    }
}

 int update_army(UNIT *units, int *pocet){
    int novy_index = 0;
    for (int i = 0; i < *pocet; i++) {
        if (units[i].hp > 0) {
            units[novy_index++] = units[i];
        }
    }
    *pocet = novy_index;
    return *pocet;
}

void vitaz(UNIT *units1, UNIT *units2) {
     if (units1[0].hp > 0 && units2[0].hp <= 0) {
        printf("WINNER 1");
    }
    if (units1[0].hp <= 0 && units2[0].hp > 0) {
        printf("WINNER 2");
    }
    if (units1[0].hp <= 0 && units2[0].hp <= 0) {
        printf("NO WINNER");
    }
}

int main(const int argc, char *argv[]){
    int pocet_kol = -1;
    if (argc == 2) {
        pocet_kol = atoi(argv[1]);
    }
    UNIT army_1[MAX_ARMY], army_2[MAX_ARMY];
    int pocet1 = 0, pocet2 = 0;
    if (nacitaj_armadu(army_1, &pocet1) == 0)
        return 0;
    if (nacitaj_armadu(army_2, &pocet2) == 0)
        return 0;
    vypis_armady(army_1, &pocet1,"Army 1");
    vypis_armady(army_2, &pocet2,"Army 2");
    int kolo = 1;
    while (!is_game_over(army_1,army_2) && (pocet_kol == -1 || kolo <= pocet_kol)) {
        printf("Round: %d\n",kolo);
        kolo++;
        print_units(army_1, army_2, &pocet1, &pocet2);
        atack_army(army_1, army_2, &pocet1, &pocet2);
        atack_army(army_2, army_1, &pocet2, &pocet1);
        print_damage(army_1, army_2, &pocet1, &pocet2);
        print_damage(army_2, army_1, &pocet2, &pocet1);
        pocet1 = update_army(army_1, &pocet1);
        pocet2 = update_army(army_2, &pocet2);
        print_units(army_1, army_2, &pocet1, &pocet2);
        printf("\n");
    }
    vitaz(army_1,army_2);
    return 0;
}
}
