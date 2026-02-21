/*
Meno a priezvisko: Martin Slatárovič

POKYNY:
(1)  Implementujte funkcie tak, aby splnali popis pri ich deklaraciach.
(2)  Cela implementacia musi byt v tomto jednom subore.
(3)  Odovzdajte len tento zdrojovy subor (s vypracovanymi rieseniami).
(4)  Program musi byt kompilovatelny.
(5)  Globalne a staticke premenne su zakazane.
(6)  V ziadnom pripade nemente deklaracie funkcii, ktore mate za ulohu naprogramovat
     (nemente nazvy, navratove hodnoty, ani typ a pocet parametrov v zadanych funkciach).
     Nemente implementacie zadanych datovych typov, ani implementacie hotovych pomocnych funkcii
     (ak nie je v zadani ulohy uvedene inak).
(7)  V pripade potreby mozete kod doplnit o dalsie pomocne funkcie alebo datove typy.
(8)  Vase riesenie otestujte (vo funkcii 'main' a pomocou doplnenych pomocnych funkcii alebo datovych typov).
     Testovaci kod ale nebude hodnoteny.
(9)  Funkcia 'main' musi byt v zdrojovom kode posledna.
*/

#include <iostream>
#include <cstring>

using namespace std;

//-------------------------------------------------------------------------------------------------
// DATOVE TYPY
//-------------------------------------------------------------------------------------------------

// Uzol zretazeneho zoznamu
struct Node {
    int data; // hodnota uzla
    Node* next; // smernik na dalsi uzol zoznamu
};

// Zretazeny zoznam
struct List {
    Node* first; // smernik na prvy uzol zoznamu
};

//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada pole 'data' od najvacsieho prvku po najmensi prvok.
    Pouzite algoritmus insertion sort.

    PARAMETRE:
        [in, out] data - pole, ktore funkcia usporiada
        [in] length    - pocet prvkov pola

    VSTUPNE PODMIENKY:
        'length' moze mat lubovolnu hodnotu
        'data' ukazuje na platne pole

    PRIKLADY:
        (1, 3, 2) -> (3, 2, 1)
        (1, 2, 2, 1) -> (2, 2, 1, 1)
        (5) -> (5)
        () -> ()
*/
void insertionSort(int *data, const size_t length) {
    if(length == 0) {
      return;
    }

    for(size_t i = 1; i < length; i++) {
      int curr = data[i];
      size_t j = i;

      while(j > 0 && data[j - 1] < curr) {
        data[j] = data[j - 1];
        --j;
      }
      data[j] = curr;
    }
}

//-------------------------------------------------------------------------------------------------
// 2. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada textove retazce v poli 'data' od najvacsieho prvku po najmensi (lexikograficky).
    Preusporiadajte smerniky v poli.
    Pouzite algoritmus insertion sort.

    PARAMETRE:
        [in, out] data - pole, ktore funkcia usporiada.
                Pole obsahuje smerniky na textove retazce.
                Kazdy textovy retazec je ukonceny '\0'.
                Posledny smernik ma hodnotu 'nullptr'. Podla toho urcite pocet prvkov pola (pocet textovych retazcov).

    VSTUPNE PODMIENKY:
        'data' obsahuje minimalne jeden smernik.
        Posledny smernik ma hodnotu 'nullptr'.

    PRIKLADY:
        ("Juraj", "Peter", "Andrej", nullptr) -> ("Peter", "Juraj", "Andrej", nullptr)
        ("Juraj", "Anabela", "Peter", "Andrej", nullptr) -> ("Peter", "Juraj", "Andrej", "Anabela", nullptr)
        ("Andrej", "Juraj", "Andrej", nullptr) -> ("Juraj", "Andrej", "Andrej", nullptr)
        ("Andrej", nullptr) -> ("Andrej", nullptr)
        (nullptr) -> (nullptr)

    POZNAMKY:
        Pri testovani mozete jednoducho pole vytvorit nasledovnym sposobom:
        const char *mena[] = {"Juraj", "Peter", "Andrej", nullptr};

        Na porovnanie obsahu textovych retazcov vyuzite prislusnu funkciu zo standardnej kniznice.
*/
void insertionSort(const char *data[]) {
    if(data == nullptr) {
      return;
    }

    size_t len = 0;
    while(data[len] != nullptr) {
        ++len;
    }

    for(size_t i = 1; i < len; i++) {
        const char *curr = data[i];
        size_t j = i;

        while(j > 0 && strcmp(data[j - 1], curr) < 0) {
            data[j] = data[j - 1];
            --j;
        }
        data[j] = curr;
    }
}

//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada zretazeny zoznam 'list' od najvacsieho prvku po najmensi.
    Preusporiadajte uzly v zozname (nekopirujte hodnoty v uzloch).
    Pouzite algoritmus insertion sort.

    PARAMETRE:
        [in, out] list - zretazeny zoznam, ktory funkcia usporiada

    VSTUPNE PODMIENKY:
        'list' obsahuje lubovolny pocet uzlov (moze byt prazdny)
        'list' nie je 'nullptr'

    PRIKLADY:
        vstup: 2->1->3,        vystup: 3->2->1
        vstup: 1->2->2->1,     vystup: 2->2->1->1
        vstup: prazdny zoznam, vystup: prazdny zoznam
*/
void insertionSort(List * list) {
    if(list->first == nullptr) {
        return;
    }

    Node *sorted = nullptr;
    Node *curr = list->first;
    while(curr != nullptr) {
        Node *next = curr->next;

        if (sorted == nullptr || curr->data > sorted->data) {
            curr->next = sorted;
            sorted = curr;
        }
        else {
            Node *search = sorted;
            while(search->next != nullptr && search->next->data >= curr->data) {
                search = search->next;
            }
            curr->next = search->next;
            search->next = curr;
        }
        curr = next;
    }
    list->first = sorted;
}

//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vykona algoritmus merge (cast algoritmu merge sort), ktory ma linearnu vypoctovu zlozitost.
    Kombinuje dve susedne, usporiadane casti v poli 'input', do jednej usporiadanej casti v poli 'output'.
    Usporiadanie je od najvacsieho prvku po najmensi prvok!

    PARAMETRE:
        [out] output - vystupne pole, ktoreho cast output[low]...output[high-1] bude po vykonani funkcie usporiadana
        [in]  input  - vstupne pole, ktoreho casti input[low]...input[middle-1] a input[middle]...input[high-1]
                         musia byt pri volani funkcie usporiadane od najvacsieho prvku po najmensi
        [in]  low    - index 1. prvku lavej usporiadanej casti pola 'input'
        [in]  middle - index 1. prvku pravej usporiadanej casti pola 'input'
        [in]  high   - index za poslednym prvkom pravej usporiadanej casti pola 'input'

    VYSTUPNE PODMIENKY:
        Obsah 'input' je nezmeneny.
        output[low] ... output[high-1] obsahuje usporiadane prvky z input[low] ... input[high-1].
        Prvky s indexami mensimi ako 'low' sa nemenia (ani v jednom poli).
        Prvky s indexami vacsimi alebo rovnymi ako 'high' sa nemenia (ani v jednom poli).

    PRIKLAD:
        low: 4                                          low            middle           high
        middle: 8                                        |               |               |
        hight: 12                                        V               V               V
        input:                         (10, 10, 10, 10,  7,  5,  2,  0,  8,  4,  2,  1, 10, 10, 10, 10)
        output pred vykonanim funkcie: (20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20)
        output po vykonani funkcie:    (20, 20, 20, 20,  8,  7,  5,  4,  2,  2,  1,  0, 20, 20, 20, 20)
*/
void mergeNeighbours(int *output, const int *input, const size_t low, const size_t middle, const size_t high) {
    size_t second = middle;
    size_t first = low;
    size_t i = low;

    while (first < middle && second < high) {
        if (input[first] > input[second]) {
            output[i++] = input[first++];
        }
        else {
            output[i++] = input[second++];
        }
    }

    while (first < middle) {
        output[i++] = input[first++];
    }
    while (second < high) {
        output[i++] = input[second++];
    }
}

//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada prvky v poli 'data' od najvacsieho prvku po najmensi.
    Pouzite algoritmus merge sort.
    Vytvorte jedno pomocne pole. Pre alokaciu a dealokaciu pomocneho pola pouzite new[] a delete[].

    PARAMETRE:
        [in, out] data - pole, ktore funkcia usporiada
        [in] length    - pocet prvkov pola

    VSTUPNE PODMIENKY:
        'data' ukazuje na platne pole

    PRIKLADY:
        (1, 3, 2) -> (3, 2, 1)
        (1, 2, 2, 1) -> (2, 2, 1, 1)
        (5) -> (5)
        () -> ()

    POZNAMKA:
        Ak pouzijete pristup top-down, tak
        - v tejto funkcii zabezpecte vytvorenie a kopirovanie dat do pomocneho pola,
        - vytvorte a zavolajte rekurzivnu funkciu, v ktorej implementujete hlavnu cast algoritmu merge sort.
*/
void mergeSort(int *data, const size_t length) {
    if (length <= 1) {
        return;
    }

    int *temp = new int[length];

    for (size_t width = 1; width < length; width*=2) {
        for (size_t low = 0; low < length; low += 2*width) {
            size_t middle = low + width;
            size_t high = low + 2*width;

            if (middle > length) {
                middle = length;
            }
            if (high > length) {
                high = length;
            }
            mergeNeighbours(temp, data, low, middle, high);
        }

        for (size_t i = 0; i < length; i++) {
            data[i] = temp[i];
        }
    }
    delete[] temp;
}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

// tu mozete doplnit pomocne funkcie a struktury

void printList(const List *list) {
    for (Node *n = list->first; n != nullptr; n = n->next)
        std::cout << n->data << (n->next ? "->" : "\n");
}

int main() {

    // tu mozete doplnit testovaci kod
    /*int arr[] = {5, 2, 9, 1, 5, 6};
    size_t length = sizeof(arr) / sizeof(arr[0]);
    insertionSort(arr, length);
    for(size_t i = 0; i < length; i++) {
      cout << arr[i] << " ";
    }*/ // uloha 1

    /*const char *mena[] = {"Juraj", "Anabela", "Peter", "Andrej", nullptr};
    insertionSort(mena);
    for(size_t i = 0; i < 4; i++) {
        cout << mena[i] << " ";
    }*/ // uloha 2

    /*Node n3{3, nullptr};
    Node n{6, &n3};
    Node n2{1, &n};
    Node n1{2, &n2};
    List list{&n1};
    insertionSort(&list);
    printList(&list);*/ // uloha 3

    /*int input[]  = {20,20,20,10, 9, 7, 5, 2, 0, 8, 4, 2, 1,20,20};
    int output[20] = {20,20,20,10, 9, 7, 5, 2, 0, 8, 4, 2, 1,20,20};
    size_t low = 3, middle = 9, high = 13;
    mergeNeighbours(output, input, low, middle, high);
    for (size_t i = 0; i < 15; i++)
        std::cout << output[i] << " ";
    std::cout << "\n";*/ // uloha 4

    /*int arr[] = {1, 3, 2, 9, 5, 7, 4};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    mergeSort(arr, n);

    for (size_t i = 0; i < n; ++i)
        std::cout << arr[i] << " ";
    std::cout << "\n"; */// uloha 5


    return 0;
}
