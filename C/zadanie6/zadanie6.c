#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>

#define MAP_SIZE 10
#define VYSKA 10
#define SIRKA 10
#define NUMBER_OF_ITEMS 16
#define MAX_NAME 100
#define MIN_ARMY 1
#define MAX_ARMY 5

typedef struct item {
    char name[MAX_NAME + 1];
    int att;
    int def;
    int slots;
    int range;
} ITEM;

typedef struct unit {
    char name[MAX_NAME + 1];
    const ITEM *item1;
    const ITEM *item2;
    int hp;
} UNIT;

const ITEM items[NUMBER_OF_ITEMS] = {
    {.name = "wand",      .att = 12, .def = 4, .slots = 1, .range = 4},
    {.name = "fireball",  .att = 11, .def = 0, .slots = 1, .range = 3},
    {.name = "sword",     .att = 9,  .def = 2, .slots = 1, .range = 1},
    {.name = "spear",     .att = 6,  .def = 1, .slots = 1, .range = 2},
    {.name = "dagger",    .att = 4,  .def = 0, .slots = 1, .range = 1},
    {.name = "rock",      .att = 3,  .def = 0, .slots = 1, .range = 2},
    {.name = "armor",     .att = 2,  .def = 7, .slots = 1, .range = 1},
    {.name = "shield",    .att = 2,  .def = 6, .slots = 1, .range = 1},
    {.name = "gloves",    .att = 1,  .def = 4, .slots = 1, .range = 1},
    {.name = "helmet",    .att = 1,  .def = 5, .slots = 1, .range = 1},
    {.name = "aura",      .att = 0,  .def = 8, .slots = 1, .range = 1},

    {.name = "cannon",    .att = 12, .def = 0, .slots = 2, .range = 4},
    {.name = "axe",       .att = 10, .def = 2, .slots = 2, .range = 1},
    {.name = "hammer",    .att = 8,  .def = 2, .slots = 2, .range = 1},
    {.name = "crossbow",  .att = 5,  .def = 1, .slots = 2, .range = 3},
    {.name = "slingshot", .att = 2,  .def = 0, .slots = 2, .range = 2}
};

typedef enum {
    REZIM_MENU,
    REZIM_HRA,
    REZIM_IN_GAME_MENU
} Rezim;

typedef struct {
    UNIT *unit;
    int owner;
} CELL;

CELL battlefield[MAP_SIZE][MAP_SIZE];

const ITEM* select_item_menu_with_display(const char* prompt, int used_slots) {
    int highlight = 0;
    int c;
    int start_y = 2;
    int start_x = 4;
    int width = 70;
    while (1) {
        clear();
        for (int i = 0; i <= NUMBER_OF_ITEMS + 1; i++) {
            mvprintw(start_y + i, start_x - 2, "|");
            mvprintw(start_y + i, start_x + width, "|");
        }
        for (int i = -1; i <= width; i++) {
            mvprintw(start_y - 1, start_x + i, "-");
            mvprintw(start_y + NUMBER_OF_ITEMS + 1, start_x + i, "-");
        }
        attron(A_BOLD | COLOR_PAIR(2));
        mvprintw(0, 2, "%s (slots vyuzite: %d/2)", prompt, used_slots);
        attroff(A_BOLD | COLOR_PAIR(2));
        for (int i = 0; i < NUMBER_OF_ITEMS; i++) {
            bool available = used_slots + items[i].slots <= 2;

            if (!available)
                attron(COLOR_PAIR(1));
            if (i == highlight)
                attron(A_REVERSE);
            mvprintw(start_y + i, start_x, "%-14s  att:%2d  def:%2d  slots:%d  range:%d  %s",
                     items[i].name, items[i].att, items[i].def, items[i].slots,
                     items[i].range,
                     available ? "" : "[X]");
            if (i == highlight)
                attroff(A_REVERSE);
            if (!available)
                attroff(COLOR_PAIR(1));
        }

        c = getch();
        switch (c) {
            case KEY_UP:
                highlight = (highlight - 1 + NUMBER_OF_ITEMS) % NUMBER_OF_ITEMS;
            break;
            case KEY_DOWN:
                highlight = (highlight + 1) % NUMBER_OF_ITEMS;
            break;
            case '\n':
                if (used_slots + items[highlight].slots <= 2)
                    return &items[highlight];
            break;
        }
    }
}

int ma_jednotky(CELL battlefield[MAP_SIZE][MAP_SIZE], int hrac) {
    for (int y = 0; y < MAP_SIZE; y++) {
        for (int x = 0; x < MAP_SIZE; x++) {
            if (battlefield[y][x].unit != NULL && battlefield[y][x].owner == hrac) {
                return 1;
            }
        }
    }
    return 0;
}

int celkovy_att(const UNIT* u) {
    int att = 0;
    if (u->item1) att += u->item1->att;
    if (u->item2) att += u->item2->att;
    return att;
}

int celkovy_def(const UNIT* u) {
    int def = 0;
    if (u->item1) def += u->item1->def;
    if (u->item2) def += u->item2->def;
    return def;
}

void interaktivne_nacitanie_armady(UNIT *units, int *pocet, const char *nazov_hraca) {
    echo();
    curs_set(1);

    while (*pocet < MAX_ARMY) {
        clear();
        mvprintw(0, 0, "%s - Zadaj meno jednotky (%d/%d) alebo \"koniec\" pre ukoncenie nacitania armady:", nazov_hraca, *pocet + 1, MAX_ARMY);
        char meno[100];
        getstr(meno);
        if (strcmp(meno, "koniec") == 0)
            break;
        strcpy(units[*pocet].name, meno);
        const ITEM* item1 = select_item_menu_with_display("Vyber PRVY item pre jednotku", 0);
        units[*pocet].item1 = item1;
        int sloty = item1->slots;
        units[*pocet].item2 = NULL;
        clear();
        mvprintw(0, 0, "Chces vybrat DRUHY item? (a/n)");
        int ch = getch();
        if ((ch == 'a' || ch == 'A') && sloty < 2) {
            const ITEM* item2 = select_item_menu_with_display("Vyber DRUHY item pre jednotku", sloty);
            units[*pocet].item2 = item2;
        }

        units[*pocet].hp = 100;
        (*pocet)++;

        clear();
        mvprintw(0, 0, "Chces pridat dalsiu jednotku? (a/n): ");
        ch = getch();
        if (ch != 'a' && ch != 'A')
            break;
    }
    noecho();
    curs_set(0);
}

void zobraz_napovedu() {
    clear();
    mvprintw(1, 2, "NAPOVEDA - Mechaniky hry:");
    mvprintw(3, 4, "- Vyber jednotku pomocou W/A/S/D a potvrd ENTER.");
    mvprintw(4, 4, "- Jednotky maju utocnu silu a obranu podla svojich itemov.");
    mvprintw(5, 4, "- Range urcuje maximalnu vzdialenost utoku (Manhattan).");
    mvprintw(6, 4, "- Kazdy utok znizuje HP ciela o (att - def), min 1.");
    mvprintw(7, 4, "- Armada moze mat 1 az 5 jednotiek, kazda ma max 2 sloty.");
    mvprintw(LINES-2, 2, "Stlac akukolvek klavesu pre navrat...");
    getch();
    refresh();
}

int manhattan(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

void utoc_na_poziciu(CELL battlefield[MAP_SIZE][MAP_SIZE], int ux, int uy, int tx, int ty) {
    if (!battlefield[uy][ux].unit) return;
    UNIT* attacker = battlefield[uy][ux].unit;
    int attacker_owner = battlefield[uy][ux].owner;
    if (!battlefield[ty][tx].unit) return;
    if (battlefield[ty][tx].owner == attacker_owner) return;

    int dist = abs(ux - tx) + abs(uy - ty);
    int range1 = attacker->item1 ? attacker->item1->range : 0;
    int range2 = attacker->item2 ? attacker->item2->range : 0;
    int max_range = range1 > range2 ? range1 : range2;
    if (dist > max_range) {
        mvprintw(MAP_SIZE + 5, 0, "Ciel je mimo dosahu! (vzdialenost %d, dosah %d)", dist, max_range);
        return;
    }

    UNIT* target = battlefield[ty][tx].unit;
    int att = (attacker->item1 ? attacker->item1->att : 0) +
              (attacker->item2 ? attacker->item2->att : 0);
    int def = (target->item1 ? target->item1->def : 0) +
              (target->item2 ? target->item2->def : 0);
    int dmg = att - def;
    if (dmg < 0) dmg = 0;
    target->hp -= dmg;

    mvprintw(MAP_SIZE + 5, 0, "%s utoci na %s (%d,%d) za %d DMG!",
             attacker->name, target->name, tx, ty, dmg);
    refresh(); napms(800);

    if (target->hp <= 0) {
        mvprintw(MAP_SIZE + 6, 0, "%s bol zabity!", target->name);
        battlefield[ty][tx].unit = NULL;
        battlefield[ty][tx].owner = 0;
        napms(800);
    }
}

int zobraz_menu_sipky() {
    const char *moznosti[] = {"Nova hra", "Nacitaj hru", "Uloz hru", "Napoveda", "Koniec"};
    int pocet = sizeof(moznosti)/sizeof(moznosti[0]);
    int vyber = 0, ch;
    keypad(stdscr, TRUE);
    while (1) {
        clear(); mvprintw(2, 5, "=== Hlavne menu ===");
        for (int i = 0; i < pocet; i++) {
            if (i == vyber) attron(A_REVERSE);
            mvprintw(4 + i, 7, "%s", moznosti[i]);
            if (i == vyber) attroff(A_REVERSE);
        }
        ch = getch();
        if (ch == KEY_UP)    vyber = (vyber - 1 + pocet) % pocet;
        else if (ch == KEY_DOWN)  vyber = (vyber + 1) % pocet;
        else if (ch == '\n')     return vyber + 1;
    }
}

int nacitaj_hru(UNIT *army1, int *pocet1, UNIT *army2, int *pocet2, CELL battlefield[MAP_SIZE][MAP_SIZE]) {
    FILE *f = fopen("save.dat", "rb");
    if (!f) {
        mvprintw(0, 0, "Ziadna ulozena hra neexistuje.");
        getch();
        return 0;
    }

    fread(pocet1, sizeof(int), 1, f);
    fread(army1, sizeof(UNIT), *pocet1, f);
    fread(pocet2, sizeof(int), 1, f);
    fread(army2, sizeof(UNIT), *pocet2, f);

    fread(battlefield, sizeof(CELL), MAP_SIZE * MAP_SIZE, f);

    fclose(f);
    mvprintw(0, 0, "Hra bola nacitana.");
    napms(1000);
    return 1;
}



void zobraz_mapu(CELL battlefield[MAP_SIZE][MAP_SIZE], int kurzor_x, int kurzor_y, int hrac) {
    clear();
    mvprintw(0, 2, "Bojove pole:");

    int right_panel_x = MAP_SIZE * 4 + 5;
    int unit_index = 0;

    for (int y = 0; y < MAP_SIZE; y++) {
        for (int x = 0; x < MAP_SIZE; x++) {
            if (y == kurzor_y && x == kurzor_x)
                attron(A_REVERSE);
            if (battlefield[y][x].unit != NULL) {
                UNIT *u = battlefield[y][x].unit;

                if (battlefield[y][x].owner == 1)
                    attron(COLOR_PAIR(2));
                else if (battlefield[y][x].owner == 2)
                    attron(COLOR_PAIR(1));
                char shortname[4];
                snprintf(shortname, sizeof(shortname), "%.2s", u->name);
                mvprintw(y + 2, x * 4, "[%s]", shortname);

                attroff(COLOR_PAIR(1));
                attroff(COLOR_PAIR(2));

                if (y == kurzor_y && x == kurzor_x)
                    attroff(A_REVERSE);
                int y_offset = unit_index * 9;
                mvprintw(y_offset + 1, right_panel_x +60, "Jednotka: %s", u->name);
                mvprintw(y_offset + 2, right_panel_x +60, "HP: %d", u->hp);
                mvprintw(y_offset + 3, right_panel_x +60, "Item1: %s", u->item1->name);
                mvprintw(y_offset + 4, right_panel_x +60, "  att:%d def:%d rng:%d",
                         u->item1->att, u->item1->def, u->item1->range);
                if (u->item2) {
                    mvprintw(y_offset + 5, right_panel_x +60, "Item2: %s", u->item2->name);
                    mvprintw(y_offset + 6, right_panel_x +60, "  att:%d def:%d rng:%d",
                             u->item2->att, u->item2->def, u->item2->range);
                } else {
                    mvprintw(y_offset + 5, right_panel_x +60, "Item2: None");
                }
                mvprintw(y_offset + 7, right_panel_x +60, "Vlastnik: Hrac %d", battlefield[y][x].owner);

                unit_index++;
            } else {
                mvprintw(y + 2, x * 4, "[  ]");
                if (y == kurzor_y && x == kurzor_x)
                    attroff(A_REVERSE);
            }
        }
    }
    char farba[100];
    if (hrac == 1)
        strcpy(farba, "MODRY");
    else
        strcpy(farba, "CERVENY");
    mvprintw(MAP_SIZE + 3, 0, "%s vyber unit pomocou ENTER a potom opatovne vyber nove policko",farba);
    refresh();
}

bool najdi_poziciu_jednotky(UNIT *unit, int *x_out, int *y_out) {
    for (int y = 0; y < MAP_SIZE; y++) {
        for (int x = 0; x < MAP_SIZE; x++) {
            if (battlefield[y][x].unit == unit) {
                *x_out = x;
                *y_out = y;
                return true;
            }
        }
    }
    return false;
}

void pohni_jednotkou(CELL battlefield[10][10], int x, int y, int new_x, int new_y) {
    UNIT* unit = battlefield[y][x].unit;
    int hrac = battlefield[y][x].owner;
    battlefield[new_y][new_x].unit = unit;
    battlefield[new_y][new_x].owner = battlefield[y][x].owner;
    battlefield[y][x].unit = NULL;
    battlefield[y][x].owner = 0;
    // ÚTOK
    int range1 = unit->item1 ? unit->item1->range : 0;
    int range2 = unit->item2 ? unit->item2->range : 0;
    int max_range = (range1 > range2) ? range1 : range2;

    for (int dy = -max_range; dy <= max_range; dy++) {
        for (int dx = -max_range; dx <= max_range; dx++) {
            int tx = new_x + dx;
            int ty = new_y + dy;
            if (tx < 0 || tx >= MAP_SIZE || ty < 0 || ty >= MAP_SIZE)
                continue;
            if (manhattan(new_x, new_y, tx, ty) > max_range)
                continue;

            if (battlefield[ty][tx].unit != NULL && battlefield[ty][tx].owner != hrac) {
                UNIT* enemy = battlefield[ty][tx].unit;

                int att = celkovy_att(unit);
                int def = celkovy_def(enemy);
                int dmg = att - def;
                if (dmg <= 0) dmg = 1;

                enemy->hp -= dmg;

                mvprintw(MAP_SIZE + 5, 0, "Jednotka %s utoci na %s za %d DMG!", unit->name, enemy->name, dmg);
                refresh();
                napms(1000);

                if (enemy->hp <= 0) {
                    battlefield[ty][tx].unit = NULL;
                    battlefield[ty][tx].owner = 0;
                    mvprintw(MAP_SIZE + 6, 0, "Nepriatel %s bol zabity!", enemy->name);
                    refresh();
                    napms(2000);
                }

                return;
            }
        }
    }
}

void uloz_hru(UNIT *army1, int pocet1, UNIT *army2, int pocet2, CELL battlefield[MAP_SIZE][MAP_SIZE]) {
    FILE *f = fopen("save.dat", "wb");
    if (!f) {
        mvprintw(0, 0, "Chyba pri otvarani suboru na zapis.");
        getch();
        return;
    }

    fwrite(&pocet1, sizeof(int), 1, f);
    fwrite(army1, sizeof(UNIT), pocet1, f);
    fwrite(&pocet2, sizeof(int), 1, f);
    fwrite(army2, sizeof(UNIT), pocet2, f);

    fwrite(battlefield, sizeof(CELL), MAP_SIZE * MAP_SIZE, f);

    fclose(f);
    mvprintw(0, 0, "Hra bola ulozena.");
    getch();
}


int hrac_na_tahu(CELL battlefield[MAP_SIZE][MAP_SIZE], int hrac) {
    int kurzor_x = 0, kurzor_y = 0;
    int oznacene_x = -1, oznacene_y = -1;

    while (1) {
        zobraz_mapu(battlefield, kurzor_x, kurzor_y, hrac);

        int input = getch();
        if (input == 27) {

            return 1;
        }
        if (input == 'w' && kurzor_y > 0) kurzor_y--;
        else if (input == 's' && kurzor_y < 9) kurzor_y++;
        else if (input == 'a' && kurzor_x > 0) kurzor_x--;
        else if (input == 'd' && kurzor_x < 9) kurzor_x++;

        else if (input == '\n') {
            if (oznacene_x == -1 &&
                battlefield[kurzor_y][kurzor_x].unit != NULL &&
                battlefield[kurzor_y][kurzor_x].owner == hrac) {

                oznacene_x = kurzor_x;
                oznacene_y = kurzor_y;

                } else if (oznacene_x != -1) {
                    int dx = abs(kurzor_x - oznacene_x);
                    int dy = abs(kurzor_y - oznacene_y);

                    if (dx + dy == 1 && battlefield[kurzor_y][kurzor_x].unit == NULL) {
                        pohni_jednotkou(battlefield, oznacene_x, oznacene_y, kurzor_x, kurzor_y);
                        oznacene_x = -1;
                        oznacene_y = -1;
                        break;
                    }
                    if (battlefield[kurzor_y][kurzor_x].unit != NULL &&
                             battlefield[kurzor_y][kurzor_x].owner != hrac) {
                        utoc_na_poziciu(battlefield, oznacene_x, oznacene_y, kurzor_x, kurzor_y);
                        napms(1000);
                        oznacene_x = -1;
                        oznacene_y = -1;
                        break;
                             }
                    {
                        mvprintw(MAP_SIZE + 4, 0, "Neplatny ciel: mozes sa pohnut iba o 1.");
                        refresh();
                        napms(1000);
                    }
                }
        } else if (input == 'q') {
            oznacene_x = -1;
            oznacene_y = -1;
        } else if (input == 'x') {
            break;
        }
    }
    return 0;
}

void vypis_armady_ncurses(UNIT *units, int *pocet, const char *nazov) {
    clear();
    mvprintw(0, 0, "%s", nazov);
    for (int i = 0; i < *pocet; i++) {
        int base_y = i * 6 + 1;
        mvprintw(base_y + 0, 0, "   Unit: %d", i);
        mvprintw(base_y + 1, 0, "   Name: %s", units[i].name);
        mvprintw(base_y + 2, 0, "   HP: %d", units[i].hp);
        mvprintw(base_y + 3, 0, "   Item 1: %s", units[i].item1->name);
        mvprintw(base_y + 4, 0, "   Item 2: %s", units[i].item2 != NULL ? units[i].item2->name : "None");
    }
    refresh();
}

void umiestni_jednotky_na_mapu(UNIT *units, int pocet, int hrac) {
    int start_row = (hrac == 1) ? 0 : 8;
    int end_row = (hrac == 1) ? 1 : 9;

    for (int i = 0; i < pocet; i++) {
        int x = 0, y = start_row;

        while (1) {
            zobraz_mapu(battlefield,x,y,hrac);
            mvprintw(MAP_SIZE + 2, 0, "Umiestni jednotku %s do prvych dvoch riadkov svojej strany", units[i].name);
            move(y + 2, x * 4 + 1);
            curs_set(1);
            refresh();
            int ch = getch();
            if (ch == KEY_UP && y > start_row) y--;
            if (ch == KEY_DOWN && y < end_row) y++;
            if (ch == KEY_LEFT && x > 0) x--;
            if (ch == KEY_RIGHT && x < MAP_SIZE - 1) x++;
            if (ch == '\n') {
                if (battlefield[y][x].unit == NULL) {
                    battlefield[y][x].unit = &units[i];
                    battlefield[y][x].owner = hrac;
                    break;
                }
            }
        }
    }
    curs_set(0);
}

void resetuj_hru(CELL battlefield[MAP_SIZE][MAP_SIZE], UNIT *army1, int *pocet1, UNIT *army2, int *pocet2) {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            battlefield[i][j].unit = NULL;
            battlefield[i][j].owner = 0;
        }
    }
    *pocet1 = 0;
    *pocet2 = 0;
    for (int i = 0; i < MAX_ARMY; i++) {
        army1[i].hp = 0;
        army2[i].hp = 0;
    }
}

int zobraz_in_game_menu() {
    const char *moznosti[] = {"Uloz hru", "Nacitaj hru", "Spat do menu", "Ukonci hru", "Napoveda", "Pokracuj"};
    int pocet = sizeof(moznosti)/sizeof(moznosti[0]);
    int vyber = 0, ch;
    keypad(stdscr, TRUE);
    while (1) {
        clear(); mvprintw(2, 5, "=== In-game menu ===");
        for (int i = 0; i < pocet; i++) {
            if (i == vyber) attron(A_REVERSE);
            mvprintw(4 + i, 7, "%s", moznosti[i]);
            if (i == vyber) attroff(A_REVERSE);
        }
        ch = getch();
        if (ch == KEY_UP)    vyber = (vyber - 1 + pocet) % pocet;
        else if (ch == KEY_DOWN)  vyber = (vyber + 1) % pocet;
        else if (ch == '\n')     return vyber + 1;
        else if (ch == 27)        return pocet; // ESC
    }
}

int main() {
    UNIT army_1[MAX_ARMY], army_2[MAX_ARMY];
    int pocet1 = 0, pocet2 = 0;
    Rezim current_mode = REZIM_MENU;

    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);

    for (int y = 0; y < MAP_SIZE; y++) {
        for (int x = 0; x < MAP_SIZE; x++) {
            battlefield[y][x].unit = NULL;
            battlefield[y][x].owner = 0;
        }
    }

    while (1) {
        if (current_mode == REZIM_MENU) {
            int volba = zobraz_menu_sipky();
            switch (volba) {
                case 1:
                    resetuj_hru(battlefield, army_1, &pocet1, army_2, &pocet2);
                    interaktivne_nacitanie_armady(army_1, &pocet1, "Hrac 1");
                    interaktivne_nacitanie_armady(army_2, &pocet2, "Hrac 2");
                    umiestni_jednotky_na_mapu(army_1, pocet1, 1);
                    umiestni_jednotky_na_mapu(army_2, pocet2, 2);
                    current_mode = REZIM_HRA;
                    break;
                case 2:
                    if(nacitaj_hru(army_1, &pocet1, army_2, &pocet2, battlefield)) current_mode=REZIM_HRA;
                    break;
                case 3:
                    uloz_hru(army_1, pocet1, army_2, pocet2, battlefield);
                    break;
                case 4:
                    zobraz_napovedu();
                    break;
                case 5:
                    endwin();
                    return 0;
                default:
                    mvprintw(12, 5, "Neplatna volba.");
                    getch();
                    break;
            }

        } else if (current_mode == REZIM_HRA) {
            if (!ma_jednotky(battlefield, 1)) {
                mvprintw(20, 5, "Hrac 2 vyhral!");
                mvprintw(21, 5, "Stlac enter pre pokracovanie!");
                getch();
                current_mode = REZIM_MENU;
                continue;
            }
            int res1 = hrac_na_tahu(battlefield, 1);
            if (res1 == 1) {
                current_mode = REZIM_IN_GAME_MENU;
                continue;
            }
            if (!ma_jednotky(battlefield, 2)) {
                mvprintw(20, 5, "Hrac 1 vyhral!");
                mvprintw(21, 5, "Stlac enter pre pokracovanie!");
                getch();
                current_mode = REZIM_MENU;
                continue;
            }
            int res2 = hrac_na_tahu(battlefield, 2);
            if (res2 == 1) {
                current_mode = REZIM_IN_GAME_MENU;
                continue;
            }

        } else if (current_mode == REZIM_IN_GAME_MENU) {
            int volba = zobraz_in_game_menu();
            switch (volba) {
                case 1:
                    uloz_hru(army_1, pocet1, army_2, pocet2, battlefield);
                    break;
                case 2:
                    nacitaj_hru(army_1, &pocet1, army_2, &pocet2, battlefield);
                    current_mode = REZIM_HRA;
                    break;
                case 3:
                    current_mode = REZIM_MENU;
                    break;
                case 4:
                    endwin();
                    return 0;
                case 5:
                    zobraz_napovedu();
                    break;
                case 6:
                    current_mode = REZIM_HRA;
                    break;
                default:
                    break;
            }
        }
    }
}
