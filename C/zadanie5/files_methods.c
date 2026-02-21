#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// NEMENIT, inak vas kod neprejde testom !!!
#include "data.h"

char *skip_whitespace(char *start) {
    while (isspace(*start)) start++;
    char *end = start + strlen(start) - 1;
    while (end > start && isspace(*end)) {
        *end = '\0';
        end--;
    }
    return start;
}

char *find_string_key(char *text, const char *wanted_word) {
    char word[40];
    sprintf(word, "\"%s\"", wanted_word);
    char *result = strstr(text, word);
    if (result == NULL) {
        fprintf(stderr,"ERR_MISSING_ATTRIBUTE");
        return NULL;
    }
    result = strchr(result, ':');
    return skip_whitespace(result + 1);


}

int read_string(char *start, char *name) {
    if (*start == ',') {
        fprintf(stderr,"ERR_MISSING_VALUE");
        return 0;
    }
    if (*start != '"') {
        fprintf(stderr,"ERR_BAD_VALUE");
        return 0;
    }
    start++;
    while (*start != '"') {
        *name++ = *start++;
    }
    *name = '\0';
    return 1;
}

int read_int(char *start, int *value) {
    if (*start == ',' || *start == '\0' || *start == '}') {
        fprintf(stderr,"ERR_MISSING_VALUE");
        return 0;
    }
    char *end;
    *value = strtol(start, &end, 10);
    if (start == end) {
        fprintf(stderr,"ERR_BAD_VALUE");
        return 0;
    }
    end = skip_whitespace(end);
    if (*end != '}' && *end != ',') {
        fprintf(stderr,"ERR_BAD_VALUE");
        return 0;
    }
    return 1;
}

ITEM *load_items(int *count) {
    FILE *f = fopen(ITEMS_FILE, "r");
    if (!f) {
        fprintf(stderr, ERR_FILE);
        return NULL;
    }
    char buffer[10000];
    int line_count = 0;
    int capacity = 100;
    char *content = malloc(capacity * MAX_LINE);
    content[0] = '\0';
    while (fgets(buffer, MAX_LINE, f)) {
        if (line_count >= capacity) {
            capacity *= 2;
            content = realloc(content, capacity * MAX_LINE);
        }
        strcat(content, buffer);
        line_count++;
    }
    fclose(f);
    ITEM *items = malloc(sizeof(ITEM) * 16);
    int index = 0;
    char *ptr;
    char *search_ptr = content;
    while ((ptr = strchr(search_ptr, '{')) != NULL) {
        ITEM item1;
        char *ptr_to_key;

        ptr_to_key = find_string_key(ptr, "name");
        if (ptr_to_key == NULL || read_string(ptr_to_key,item1.name) == 0 ){
            free(content);
            return NULL;
        }

        ptr_to_key = find_string_key(ptr, "att");
        if (ptr_to_key == NULL || read_int(ptr_to_key,&item1.att) == 0 ){
            free(content);
            return NULL;
        }

        ptr_to_key = find_string_key(ptr, "def");
        if (ptr_to_key == NULL || read_int(ptr_to_key,&item1.def) == 0 ){
            free(content);
            return NULL;
        }

        ptr_to_key = find_string_key(ptr, "slots");
        if (ptr_to_key == NULL || read_int(ptr_to_key,&item1.slots) == 0 ){
            free(content);
            return NULL;
        }

        ptr_to_key = find_string_key(ptr, "range");
        if (ptr_to_key == NULL || read_int(ptr_to_key,&item1.range) == 0 ){
            free(content);
            return NULL;
        }

        ptr_to_key = find_string_key(ptr, "radius");
        if (ptr_to_key == NULL || read_int(ptr_to_key,&item1.radius) == 0 ){
            free(content);
            return NULL;
        }
        items[index] = item1;
        index++;
        if (index >= capacity) {
            capacity *= 2;
            items = realloc(items, sizeof(ITEM) * capacity);
        }
        char *end = strchr(ptr, '}');
        if (end == NULL) break;
        search_ptr = end + 1;
    }

    *count = index;
    free(content);
    return items;

}

const ITEM* find_item(const char *zadany_predmet, ITEM *items) {
    for (int i = 0; i < 16; i++) {
        skip_whitespace(items[i].name);
        if (strcmp(items[i].name, zadany_predmet) == 0) {
            return &items[i];
        }
    }
    return NULL;
}

int reading_input(UNIT *army, int *count, FILE *f, ITEM *items) {
    if(!f) {
        fprintf(stderr,ERR_FILE);
        return 0;
    }
    fscanf(f, "%d", count);
    if (*count <= 0 || *count > 5) {
        fprintf(stderr,ERR_UNIT_COUNT);
        return 0;
    }
    fgetc(f);
    char buffer[MAX_LINE];
    for (int i = 0; i < *count; i++) {
        int taken_slots = 0;

        fgets(buffer, MAX_LINE, f);
        char *name = strtok(buffer, " ");
        strcpy(army[i].name,name);
        army[i].name[strcspn(army[i].name, "\n")] = '\0';
        char *word = strtok(NULL, " ");
        if (word == NULL) {
            fprintf(stderr,ERR_ITEM_COUNT);
            return 0;
        }
        word[strcspn(word, "\n")] = '\0';
        const ITEM *item1 = find_item(word, items);
        if (item1 == NULL) {
            fprintf(stderr,ERR_WRONG_ITEM);
            return 0;
        }
        army[i].item1 = item1;
        taken_slots += item1->slots;
        word = strtok(NULL, " ");
        if (word != NULL) {
            word[strcspn(word, "\n")] = '\0';
            const ITEM *item2 = find_item(word, items);
            if (item2 == NULL) {
                fprintf(stderr, ERR_WRONG_ITEM);
                return 0;
            }
            army[i].item2 = item2;
            taken_slots += item2->slots;
        }
        else
            army[i].item2 = NULL;
        word = strtok(NULL, " ");
        if (word != NULL) {
            printf(ERR_ITEM_COUNT);
            return 0;
        }
        if (taken_slots > 2) {
            printf(ERR_SLOTS);
            return 0;
        }
    }
    fclose(f);
    return 1;
}

void print_army(UNIT *units, int *count, const char *name) {
    printf("%s\n",name);
    for (int i = 0; i < *count; i++) {
        printf("   Unit: %d\n",i);
        printf("   Name: %s\n",units[i].name);
        printf("   HP: %d\n",100);
        printf("   Item 1: %s,%d,%d,%d,%d,%d\n",units[i].item1->name,units[i].item1->att,units[i].item1->def,units[i].item1->slots,units[i].item1->range,units[i].item1->radius);
        if (units[i].item2 != NULL) {
            printf("   Item 2: %s,%d,%d,%d,%d,%d\n",units[i].item2->name,units[i].item2->att,units[i].item2->def,units[i].item2->slots,units[i].item2->range,units[i].item2->radius);
        }
        printf("\n");
    }
}

int main(const int argc, char *argv[]) {
    if (argc != 1 && argc != 3) {
        fprintf(stderr, ERR_CMD);
        return 0;
    }
    int count = 0;
    ITEM *items = load_items(&count);
    if (!items) return 0;
    if (argc == 1) {
        for (int i = 0; i < count; i++) {
            printf("Name: %s\n", items[i].name);
            printf("Attack: %d\n", items[i].att);
            printf("Defense: %d\n", items[i].def);
            printf("Slots: %d\n", items[i].slots);
            printf("Range: %d\n", items[i].range);
            printf("Radius: %d\n", items[i].radius);
            printf("\n");
        }
        return 0;
    }
    if (argc == 3) {
        FILE *f1 = fopen(argv[1], "r");
        FILE *f2 = fopen(argv[2], "r");
        int count1 = 0, count2 = 0;
        UNIT army1[5], army2[5];
        if (reading_input(army1, &count1, f1, items) == 0) return 0;
        if (reading_input(army2, &count2, f2, items) == 0) return 0;
        print_army(army1, &count1, "Army 1");
        print_army(army2, &count2, "Army 2");
    }
    return 0;
}
