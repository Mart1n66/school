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
(8)  V prvych osmich prikladoch mozete pouzit iterativnu alebo rekurzivnu implementaciu. <- SPECIALNE INSTRUKCIE PRE TOTO ZADANIE
     V pripade implementacie rekurziou, moze byt hlavna cast implemetovana v pridanej rekurzivnej funkcii. <- SPECIALNE INSTRUKCIE PRE TOTO ZADANIE
(9)  Vase riesenie otestujte (vo funkcii 'main' a pomocou doplnenych pomocnych funkcii alebo datovych typov).
     Testovaci kod ale nebude hodnoteny.
(10) Funkcia 'main' musi byt v zdrojovom kode posledna.
*/


#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <exception>
#include <set>
#include <string>

using namespace std;

//-------------------------------------------------------------------------------------------------
// DATOVE TYPY
//-------------------------------------------------------------------------------------------------

// Uzol binarneho vyhladavacieho stromu
struct Node {
    int value;     // hodnota uzla
    Node *smaller; // uzol 'smaller' a jeho nasledovnici maju hodnotu mensiu ako 'value'
    Node *greater; // uzol 'greater' a jeho nasledovnici maju hodnotu vacsiu ako 'value

    explicit Node(int value = 0, Node *smaller = nullptr, Node *greater = nullptr)
    : value(value)
    , smaller(smaller)
    , greater(greater)
    {
    }
};

size_t countNodes(const Node* node) noexcept;
void inorder(const Node *node, std::list<int> &result) noexcept;
size_t countGreaterNode(const Node *node, int value) noexcept;
void clearNode(Node *node) noexcept;

// Binarny vyhladavaci strom
struct BinarySearchTree {
    Node *root; // koren stromu

    explicit BinarySearchTree(Node *root = nullptr)
    : root(root)
    {
    }
};

// Vynimka oznacujuca, ze uzol so zadanou hodnotou v strome neexistuje
class ValueNotExistsException : public std::exception {
};

//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati najmensiu hodnotu v strome.
    V pripade neexistencie tejto hodnoty vyhodi vynimku.

    Riesenie (tejto, aj dalsich uloh) musi vyuzivat vlastnosti binarneho vyhladavacieho stromu.
    Napriklad, pri hladani minima treba prejst len cez potrebne uzly. Netreba prehladavat vsetky uzly (okrem specialnych pripadov).

    VSTUPNY PARAMETER:
        [in] tree - strom, v ktorom funkcia hlada minimum

    NAVRATOVA HODNOTA:
        najmensia hodnota v strome

    VYNIMKA:
        ValueNotExistsException - ak je strom prazdny
*/

int min(const BinarySearchTree *tree) {
    if (tree == nullptr || tree->root == nullptr) {
      throw ValueNotExistsException();
    }
    Node *curr = tree->root;
    while (curr->smaller != nullptr) {
      curr = curr->smaller;
    }
    return curr->value;
}

//-------------------------------------------------------------------------------------------------
// 2. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati hlbku uzla s hodnotou 'value' v strome 'tree'.
    Hlbka korena je 0.
    Ak hladany uzol v strome nie je, tak funkcia vyhodi vynimku.

    VSTUPNE PARAMETRE:
        [in] tree - strom, v ktorom funkcia hlada uzol
        [in] value - hodnota hladaneho uzla

    NAVRATOVA HODNOTA:
        Hlbka uzla s hodnotou 'value'.

    VYNIMKA:
        ValueNotExistsException - ak sa uzol s hodnotou 'value' v strome nenachdza
*/

size_t depth(const BinarySearchTree *tree, int value) {
    if (tree == nullptr || tree->root == nullptr) {
      throw ValueNotExistsException();
    }
    size_t depth = 0;
    Node *curr = tree->root;
    while (curr != nullptr) {
        if (curr->value == value) {
            return depth;
        }
        if (curr->value > value) {
          curr = curr->smaller;
        }
        else {
          curr = curr->greater;
        }
        depth++;
    }
    throw ValueNotExistsException();
}

//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati zoznam hodnot uzlov, ktore musi prejst pri hladani uzla s hodnotou 'value'.
    Prva hodnota vystupneho zoznamu je hodnota korena, druha hodnota zoznamu je lavy alebo pravy nasledovnik korena, atd.
    Poslednou hodnotou vo vystupnom zozname je hodnota uzla, na ktorom sa hladanie zastavilo.
    Ak 'tree' obsahuje uzol s hodnotou 'value', tak poslednou hodnotou vystupeho zoznamu je 'value'.

    VSTUPNE PARAMETRE:
        [in] tree - strom, v ktorom funkcia hlada uzol s hodnotou 'value'
        [in] value - hodnota hladaneho uzla

    NAVRATOVA HODNOTA:
        Zoznam hodnot uzlov, ktorych hodnoty musela funkcia pri hladani porovnavat.
        Poradie hodnot vo vystupnom zozname musi zodpovedat poradiu prechadzania uzlov stromu.

    PRIKLADY:
        V prikladoch predpokladajme strom:
                  40
                 /  \
               20    50
              /  \    \
            10   30    60

        1. priklad
            value: 30 -> vystup: (40, 20, 30)
        2. priklad
            value: 20 -> vystup: (40, 20)
        3. priklad
            value: 45 -> vystup: (40, 50)
*/

list<int> path(const BinarySearchTree *tree, int value) noexcept {
    std::list<int> result;
    if (tree == nullptr || tree->root == nullptr) {
      return result;
    }
    Node *curr = tree->root;
    while (curr != nullptr) {
      result.push_back(curr->value);
      if (curr->value == value) {
        return result;
      }
      if (curr->value > value) {
        curr = curr->smaller;
      }
      else {
        curr = curr->greater;
      }
    }
    return result;
}

//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati pocet uzlov stromu.

    VSTUPNY PARAMETER:
        [in] tree - strom, ktoreho pocet uzlov funkcia zistuje

    NAVRATOVA HODNOTA:
        pocet uzlov stromu
*/

size_t count(const BinarySearchTree *tree) noexcept {
    if (tree == nullptr){
      return 0;
    }
    return countNodes(tree->root);
}

//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati zoznam hodnot vsetkych uzlov v strome 'tree'.
    Zoznam musi byt usporiadany od najmensieho prvku po najvacsi.

    Usporiadanie dosiahnite vhodnou postupnostou prechadzania uzlov stromu!

    VSTUPNY PARAMETER:
        [in] tree - strom, ktoreho hodnoty funkcia vrati

    NAVRATOVA HODNOTA:
        hodnoty uzlov, v poradi od najmensej po najvacsiu
*/

list<int> all(const BinarySearchTree *tree) noexcept {
    std::list<int> result;
    if (tree == nullptr || tree->root == nullptr) {
      return result;
    }
    inorder(tree->root, result);
    return result;
}

//-------------------------------------------------------------------------------------------------
// 6. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati pocet uzlov stromu 'tree', ktorych hodnota je vacsia ako 'value'.

    VSTUPNE PARAMETRE:
        [in] tree - strom, v ktorom funkcia pocita pocet uzlov splnajich podmienku
        [in] value - hodnota, podla ktorej sa vyberaju uzly

    NAVRATOVA HODNOTA:
        pocet uzlov s hodnotou vacsou ako 'value'
*/

size_t countGreater(const BinarySearchTree *tree, int value) noexcept {
    if (tree == nullptr || tree->root == nullptr) {
      return 0;
    }
    return countGreaterNode(tree->root, value);
}

//-------------------------------------------------------------------------------------------------
// 7. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia odstrani vsetky uzly stromu a dealokuje ich.

    Na dealokaciu pouzite operator 'delete'!

    VSTUPNY PARAMETER:
        [in, out] tree - strom, ktoreho uzly funkcia odstrani

    VYSTUPNE PODMIENKY:
        vsetky uzly su dealokovane
        'tree->root' je nulovy smernik
*/

void clear(BinarySearchTree *tree) noexcept {
    if (tree == nullptr || tree->root == nullptr) {
      return;
    }
    clearNode(tree->root);
    tree->root = nullptr;
}

//-------------------------------------------------------------------------------------------------
// 8. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia hlada hodnotu 'value' vo vektore 'data'.
    Vrati pocet prvkov v 'data', ktore pri hladni porovnala s 'value'.
    Vektor 'data' obsahuje usporiadane hodnoty.
    Casova narocnost algoritmu je O(log(n)), kde n je pocet prvkov vektora.

    PARAMETRE:
        [in] data - hodnoty usporiadane od najmensieho prvku po najvacsi
        [in] value - hodnota hladana v 'data'

    NAVRATOVA HODNOTA:
        Pocet prvkov 'data', ktore funkcia pri hladani porovnala s 'value'.
        (bez ohladu na to, ci 'data' obsahuje hodnotu 'value').

    VSTUPNA PODMIENKA:
        Hodnoty v 'data' su usporiadane od najmensieho prvku po najvacsi.

    PRIKLADY:
        data = (100, 102, 104, 106, 108, 110, 112), value = 106 -> vystup: 1
        data = (100, 102, 104, 106, 108, 110, 112), value = 110 -> vystup: 2
        data = (100, 102, 104, 106, 108, 110, 112), value = 108 -> vystup: 3
        data = (100, 102, 104, 106, 108, 110), value = 104 -> vystup: 1 alebo 3
        data = (100, 102, 104, 106, 108, 110), value = 107 -> vystup: 3
        data = (100), value = 100 -> vystup: 1
        data = (100), value = 200 -> vystup: 1
        data = (), value = 100 -> vystup: 0
*/

size_t contains(const vector<int> & data, int value) noexcept {
    if(data.empty()) {
      return 0;
    }
    size_t count = 0;
    size_t left = 0, right = data.size() - 1;

    while (left <= right) {
        size_t mid = left + (right - left) / 2;
        count ++;
        if (data[mid] == value) {
          return count;
        }
        if (data[mid] > value) {
          if(mid == 0) break;
          right = mid - 1;
        }
        else {
          left = mid + 1;
        }
    }
    return count;
}

//-------------------------------------------------------------------------------------------------
// 9. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori a vrati histogram slov v 'data' (zisti, kolko krat sa ktore slovo nachadza v 'data').

    PARAMETER:
        [in] data - vektor slov

    NAVRATOVA HODNOTA:
        histogram slov (pre kazde slovo z 'data' obsahuje pocet jeho vyskytov)

    VSTUPNE PODMIENKY:
        'data' moze obsahovat lubobolny pocet slov
        'data' moze obsahovat opakujuce sa slova
        slova mozu byt prazdne retazce

    VYSTUPNE PODMIENKY:
        Histogram obsahuje iba slova, ktore sa v 'data' nachadzaju

    PRIKLADY:
        vstup: data = ("pocitac", "lietadlo", luk", "pocitac", "pocitac", "okno", "luk")
        vystup: {"pocitac" -> 3, "lietadlo" -> 1, "luk" -> 2, "okno" -> 1}

        vstup: data = ("pocitac", "")
        vystup: {"pocitac" -> 1, "" -> 1}

        vstup: data = ()
        vystup: {}
*/

map<string, size_t> histogram(const vector<string> & data) noexcept {
    std::map<string, size_t> result;
    for (const auto &word : data) {
        result[word]++;
    }
    return result;
}

//-------------------------------------------------------------------------------------------------
// 10. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori a vrati index slov v 'data' (pre kazde slovo mnozinu indexov jeho vyskytu).

    PARAMETER:
        [in] data - vektor slov

    NAVRATOVA HODNOTA:
        index slov (pre kazde slovo z 'data' obsahuje indexy, na ktorych sa slovo v 'data' nachadza)

    VSTUPNE PODMIENKY:
        'data' moze obsahovat lubobolny pocet slov
        'data' moze obsahovat opakujuce sa slova
        slova mozu byt prazdne retazce

    VYSTUPNE PODMIENKY:
        Index obsahuje zoznamy vyskytov len pre slova, ktore sa nachadzaju v 'data'

    PRIKLADY:
        vstup: data = ("pocitac", "lietadlo", luk", "pocitac", "pocitac", "okno", "luk")
        vystup: {"pocitac" -> {0, 3, 4}, "lietadlo" -> {1}, "luk" -> {2, 6}, "okno" -> {5}}

        vstup: data = ("pocitac", "")
        vystup: {"pocitac" -> {0}, "" -> {1}}

        vstup: data = ()
        vystup: {}
*/

map<string, set<size_t>> index(const vector<string> & data) noexcept {
    std::map<string, set<size_t> > result;
    for (size_t i = 0; i < data.size(); ++i) {
        const std::string &word = data[i];
        result[word].insert(i);
    }
    return result;
}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

// tu mozete doplnit pomocne funkcie a struktury

size_t countNodes(const Node* node) noexcept {
    if (node == nullptr) {
        return 0;
    }
    return 1 + countNodes(node->smaller) + countNodes(node->greater);
}

void inorder(const Node *node, std::list<int> &result) noexcept {
    if (node == nullptr) {
        return;
    }

    inorder(node->smaller, result);
    result.push_back(node->value);
    inorder(node->greater, result);
}

size_t countGreaterNode(const Node *node, int value) noexcept {
    if (node == nullptr) {
        return 0;
    }

    if (node->value > value) {
        return 1
             + countGreaterNode(node->smaller, value)
             + countGreaterNode(node->greater, value);
    } else {
        return countGreaterNode(node->greater, value);
    }
}

void clearNode(Node *node) noexcept {
    if (node == nullptr) {
        return;
    }
    clearNode(node->smaller);
    clearNode(node->greater);
    delete node;
}

void printList(const std::list<int>& xs) {
    cout << "(";
    bool first = true;
    for (int x : xs) {
        if (!first) cout << ", ";
        cout << x;
        first = false;
    }
    cout << ")";
}

void printSet(const std::set<size_t>& s) {
    cout << "{";
    bool first = true;
    for (auto x : s) {
        if (!first) cout << ", ";
        cout << x;
        first = false;
    }
    cout << "}";
}

void printHistogram(const std::map<std::string, size_t>& m) {
    cout << "{";
    bool first = true;
    for (const auto& [k, v] : m) {
        if (!first) cout << ", ";
        cout << "\"" << k << "\" -> " << v;
        first = false;
    }
    cout << "}";
}

void printIndex(const std::map<std::string, std::set<size_t>>& m) {
    cout << "{";
    bool first = true;
    for (const auto& [k, s] : m) {
        if (!first) cout << ", ";
        cout << "\"" << k << "\" -> ";
        printSet(s);
        first = false;
    }
    cout << "}";
}

Node* n(int v, Node* s=nullptr, Node* g=nullptr) { return new Node(v, s, g); }

int main() {

    // tu mozete doplnit testovaci kod
    BinarySearchTree t(
            n(40,
              n(20, n(10), n(30)),
              n(50, nullptr, n(60)))
        );

    cout << "min: " << min(&t) << "\n";
    cout << "depth(30): " << depth(&t, 30) << "\n";
    cout << "path(30): "; printList(path(&t, 30)); cout << "\n";
    cout << "path(45): "; printList(path(&t, 45)); cout << "\n";
    cout << "count: " << count(&t) << "\n";
    cout << "all: "; printList(all(&t)); cout << "\n";
    cout << "countGreater(40): " << countGreater(&t, 40) << "\n";
    clear(&t); // uloha 1 - 7
    cout << endl;

    vector<int> a = {100, 102, 104, 106, 108, 110, 112};
    cout << "contains(106): " << contains(a, 106) << "\n";
    cout << "contains(110): " << contains(a, 110) << "\n";
    cout << "contains(108): " << contains(a, 108) << "\n"; // uloha 8
    cout << endl;

    vector<string> data = {"pocitac", "lietadlo", "luk", "pocitac", "pocitac", "okno", "luk"};
    auto h = histogram(data);
    printHistogram(h); cout << "\n";
    vector<string> data2 = {"pocitac", ""};
    auto h2 = histogram(data2);
    printHistogram(h2); cout << "\n"; // uloha 9
    cout << endl;

    vector<string> data3 = {"pocitac", "lietadlo", "luk", "pocitac", "pocitac", "okno", "luk"};
    auto idx = index(data3);
    printIndex(idx); cout << "\n";
    vector<string> data4 = {"pocitac", ""};
    auto idx2 = index(data4);
    printIndex(idx2); cout << "\n";

    return 0;
}
