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
#include <string>
#include <map>
#include <list>
#include <stack>
#include <queue>
#include <vector>
#include <sstream>

using namespace std;

//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori frontu, ktora obsahuje rovnake prvky ako vstupny zoznam, ale v opacnom poradi.
    Obsah vstupneho zoznamu nemeni.

    Implementujte pomocou reverzneho iteratora!

    PARAMETER:
        [in] data - zoznam prvkov, ktore funkcia nakopiruje do vytvorenej fronty.

    NAVRATOVA HODNOTA:
        Nova fronta, obsahujuca kopie prvkov vstupneho zoznamu v opacnom poradi
*/

queue<int> reverse(const list<int> & data) noexcept {
    std::queue<int> q;
    for(auto ri = data.rbegin(); ri != data.rend(); ri++) {
      q.push(*ri);
    }
    return q;
}

//-------------------------------------------------------------------------------------------------
// 2. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia preusporiada prvky vo fronte tak, ze budu v opacnom poradi.

    Implementujte pomocou zasobnika!
    Algoritmus ulozi prvky z fronty do zasobnika a potom zo zasobnika naspat do fronty.
    Priebeh alogoritmu je znazorneny v animacii.

    PARAMETER:
        [in, out] data - fronta, v ktorej funkcia zmeni poradie prvkov na opacne
*/

void reverse(queue<int> & data) noexcept {
    std::stack<int> stack;
    while(!data.empty()) {
        stack.push(data.front());
        data.pop();
    }

    while(!stack.empty()) {
        data.push(stack.top());
        stack.pop();
    }
}

//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori vektor, ktoreho prvkami su vektory cisiel typu 'int'.

    PARAMETRE:
        [in] size1 - pocet prvkov hlavneho vektora (pocet vnorenych vektorov)
        [in] size2 - pocet prvkov kazdeho vektora, ktory je prvkom hlavneho vektora (vnorene vektory budu rovnako dlhe, ich dlzka bude 'size2')
        [in] value - hodnota kazdeho celeho cisla vo vektore vektorov

    NAVRATOVA HODNOTA:
        Vektor, ktoreho prvkami su vektory cisiel (pocet jeho prvkov je 'size1').
        Vnorene vektory su rovnako dlhe (pocty ich prvkov su 'size2').
        Vsetky cisla vo vektore vektorov maju hodnotu 'value'.

    PRIKLAD:
        vstup:
            size1 = 2, size2 = 5, value = 10
        vystup:
            ( (10, 10, 10, 10, 10), (10, 10, 10, 10, 10) )
*/

vector<vector<int>> create2dVector(const size_t size1, const size_t size2, const int value) noexcept {
    std::vector<std::vector<int> > data(size1, std::vector<int>(size2, value));
    return data;
}

//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati textovy retacec, ktory vznikne zretazenim textu 'text', medzery  a cisla 'number'.

    PARAMETRE:
        [in] text - textovy retazec
        [in] number - cislo

    NAVRATOVA HODNOTA:
        Novy textovy retazec, ktory vznikne zretazenim 'text', jednej medzery a 'number'
        (cislo 'number' je skonvertovane na textovy retazec).

    PRIKLADY:
        1. priklad:
            text: "abc", number: 10, vystup: "abc 10"
        2. priklad:
            text: " abc ", number: 10, vystup: " abc  10"
        3. priklad:
            text: "", number: -10, vystup: " -10"
*/

string connectWithSpace(const string & text, const int number) noexcept {
    std::stringstream ss;
    ss << text << " " << number;
    return ss.str();
}

//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia precita cisla zo vstupneho textoveho prudu a vrati ich sucet.
    Funkcia cita cele cisla (reprezentovatelne typom int).
    Ak sa vo vstupnom prude vyskytne text, ktory sa neda skonvertovat na cislo,
    tak citanie skonci a vrati sucet precitanych cisiel (funkcia neskusa hladat dalsie cisla).
    Pred, medzi a za cislami moze byt lubovolny pocet bielych znakov.

    PARAMETER:
        [in] text - vstupny textovy prud

    NAVRATOVA HODNOTA:
        Sucet precitanych cisiel (do konca, alebo po vyskyt chyby pri citani alebo konvertovani textu na cislo)

    PRIKLADY:
        text: "10 20 30 10", vystup: 70
        text: " 10   20 30 10 ", vystup: 70
        text: "10 a 20", vystup: 10 (pri konverzii "a" na cislo nastala chyba, funkcia vratila sucet cisiel po vyskyt prvej chyby citania/konverzie)
        text: "", vystup: 0
        text: " ", vystup: 0
*/

int sum(istringstream & text) noexcept {
    int sum = 0;
    int num;
    while(true) {
        if (text >> num) {
            sum += num;
        }
        else {
            break;
        }
    }
    return sum;
}

//-------------------------------------------------------------------------------------------------
// 6. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia prelozi zoznam slov 'sentence' z jedneho jazyka do druheho pomocou slovnika 'translator' a vrati prelozeny zoznam slov.
    Pri prekladani zachova vstupne poradie slov.
    Ak sa v slovniku 'translator' nenachadza preklad, tak do vystupneho zoznamu zapise namiesto prekladu otaznik.
    Pri preklade sa rozlisuju male a velke pismena, cize pri hladani prekladu netreba konvertovat velke pismena na male, alebo opacne.

    PARAMETERE:
        [in] translator - mapuje slova zo vstupneho jazyka do vystupneho jazyka
        [in] sentence   - zoznam slov vo vstupnom jazyku

    NAVRATOVA HODNOTA:
        Novy zoznam slov, prelozenych zo vstupneho do vystupneho jazyka, v poradi, v ktorom boli v 'sentence'.
        Ak slovnik 'translator' neobsahuje preklad slova, tak je vo vystupnom zozname namiesto prekladu otaznik.

    PRIKLADY:
        Vo vsetkych prikladoch predpokladajme obsah prekladoveho slovnika:
            translator: {
                "read" -> "citat",
                "write" -> "pisat",
                "book" -> "kniha",
                "I" -> "ja",
                "you" -> "ty",
                "he" -> "on",
                "she" -> "ona",
                "it" -> "ono"
                "a" -> "",
                "an" -> "",
                "the" -> ""
            }
        1. priklad:
            sentence: ("I", "read", "a", "book"), vystup: ("ja", "citat", "", "kniha")
        2. priklad:
            sentence: ("I", "am", "reading", "a", "book"), vystup: ("ja", "?", "?", "", "kniha")
        3. priklad:
            sentence: ("He", "reads", "a", "book"), vystup: ("?", "?", "", "kniha"), poznamka: neprelozil "He", pretoze v slovniku je len "he"
*/

list<string> translate(const map<string, string> & translator, const list<string> & sentence) noexcept {
    std::list<string> result;
    for (const auto & word : sentence) {
        auto it = translator.find(word);
        if (it != translator.end()) {
            result.push_back(it->second);
        }
        else {
            result.emplace_back("?");
        }
    }
    return result;
}

//-------------------------------------------------------------------------------------------------
// 7. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia zisti, ci su vo vstupnom textovom retazci spravne sparovane zatvorky.
    Ak ano, vrati 'true', inak vrati 'false'.
    Testuje nasledujuce typy zatvoriek: ( ) { } [ ] < >

    V implementacii pouzite na ukladanie otvaracich zatvoriek zasobnik.
    Porovnavajte zatvaracie zatvorky s poslednou otvaracou zatvorkou (na vrchole zasobnika).
    Princip algoritmu je znazorneny v prezentacii.

    PARAMETER:
        [in] mathExpression - textovy retazec, v ktorom funkcia testuje spravnost sparovania zatvoriek

    NAVRATOVA HODNOTA:
        Ak su zatvorky spravne sparovane vrati 'true', inak vrati 'false'.

    PRIKLADY:
        vstup: "a + (2 * (3 + 4))", vystup: 'true'
        vstup: "ab - (c< d > 1) + {[23 ( [ 45] ) 6] 7} 8 ", vystup: 'true'
        vstup: "1 + (2", vystup: 'false'
        vstup: "(", vystup: 'false'
        vstup: "())", vystup: 'false'
        vstup: "{ >", vystup: 'false'
        vstup: "", vystup: 'true'
*/

bool areParenthesisPaired(const string & mathExpression) noexcept {
    std::stack<char> stack;
    for (const auto & m : mathExpression) {
        if (m == '(' || m == '{' || m == '[' || m == '<') {
            stack.push(m);
        }
        else if (m == ')' || m == '}' || m == ']' || m == '>') {
            if (stack.empty()) {
                return false;
            }
            char top = stack.top();
            stack.pop();

            if ((m == ')' && top != '(') ||
                (m == '}' && top != '{') ||
                (m == ']' && top != '[') ||
                (m == '>' && top != '<')) {
                return false;
                }
        }
    }
    return stack.empty();
}

//-------------------------------------------------------------------------------------------------
// 8. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia 'execute' zavola funkciu 'function', s parametrami 'parameter1' a 'parameter2' a vrati jej vysledok.

    PARAMETRE:
        [in] function   - funkcia, ktoru funkcia 'execute' zavola
        [in] parameter1 - pri volani 'function' bude pouzity ako 1. parameter
        [in] parameter2 - pri volani 'function' bude pouzity ako 2. parameter

    NAVRATOVA HODNOTA:
        Vysledok volania 'function(parameter1, parameter2)'

    Funkcie 'multiply' a 'maxValue' su priklady funkcii, ktore mozu byt pouzite ako parameter funkcie 'execute'.

    PRIKLADY:
        1. priklad:
            volanie: execute(multiply, 20, 50) alebo execute(&multiply, 20, 50)
            vystup: 1000
        2. priklad:
            volanie: execute(maxValue, 20, 50) alebo execute(&maxValue, 20, 50)
            vystup: 50
        3. priklad:
            volanie: execute([](int a, int b)->int { return a - b; }, 20, 50)
            vystup: -30
*/

int multiply(int a, int b) noexcept {
    return a * b;
}

int maxValue(int a, int b) noexcept {
    if(a >= b) {
        return a;
    }
    else {
        return b;
    }
}

int execute(int (*function)(int, int), int parameter1, int parameter2) {
    return function(parameter1, parameter2);
}

//-------------------------------------------------------------------------------------------------
// 9. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia 'detectException' zavola funkciu 'function', ktora je vstupnym parametrom.
    Vrati hodnotu podla toho, ci a aku vynimku funkcia 'function' pri volani vyhodi.

    PARAMETER:
        [in] function - funkcia, ktora bude zavolana a testovana (ci a aku vynimku vyhodi)

    NAVRATOVA HODNOTA:
        ExceptionType::NO_EXCEPTION - ak 'function' nevyhodi ziadnu vynimku
        ExceptionType::INVALID_ARGUMENT - ak 'function' vyhodi vynimku typu 'std::invalid_argument'
        ExceptionType::BAD_ALLOC - ak 'function' vyhodi vynimku typu 'std::bad_alloc'
        ExceptionType::UNKNOWN_EXCEPTION - ak 'function' vyhodi iny typ vynimky

    Funkcie: 'doNotThrow', 'throwInvalidArgument', 'throwBadAlloc', 'throwOutOfRange' mozete pouzit pre testovanie.
*/

void doNotThrow() noexcept {
}

void throwInvalidArgument() {
    throw std::invalid_argument("popis vynimky"); // konstruktor vynimky ma parameter
}

void throwBadAlloc() {
    throw std::bad_alloc(); // konstruktor vynimky nema parameter
}

void throwOutOfRange() {
    throw std::out_of_range("popis vynimky");
}

enum class ExceptionType {
    NO_EXCEPTION,
    INVALID_ARGUMENT,
    BAD_ALLOC,
    UNKNOWN_EXCEPTION
};

ExceptionType detectException(void (*function)()) noexcept {
    try {
        function();
        return ExceptionType::NO_EXCEPTION;
    }
    catch (const std::invalid_argument &) {
        return ExceptionType::INVALID_ARGUMENT;
    }
    catch (const std::bad_alloc &) {
        return ExceptionType::BAD_ALLOC;
    }
    catch (...) {
        return ExceptionType::UNKNOWN_EXCEPTION;
    }
}

//-------------------------------------------------------------------------------------------------
// 10. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori zoznam, ktoreho jeden prvok bude mat hodnotu 1, ostatne prvky hodnotu 0.
    Zoznam bude mat 'length' prvkov.
    Prvok s indexom 'indexOfOne' bude mat hodnotu 1, ostatne prvky hodnotu 0. Prvy prvok ma index nula.
    V pripade chybnych vstupnych parametrov, funkcia vyhodi vynimku.

    PARAMETRE:
        [in] length - pocet prvkov vytvoreneho zoznamu
        [in] indexOfOne - index prvku, ktory bude mat hodnotu 1

    NAVRATOVA HODNOTA:
        Zoznam, ktory obsahuje jednu 1 (prvok s indexom 'indexOfOne') a ostatne jeho prvky maju hodnotu 0.
        Pocet prvkov zoznamu je 'length'

    VYNIMKA:
        Ak 'indexOfOne' >= 'length', tak funkcia vyhodi vynimku typu 'IndexOutOfRangeException',
        ktora nesie informacie o pozadovanej dlzke zoznamu a indexe kde mala byt hodnota 1.

    PRIKLADY:
        1. priklad
            vstup: length = 5, indexOfOne = 0
            vystup: {1, 0, 0, 0, 0}
        2. priklad
            vstup: length = 5, indexOfOne = 1
            vystup: {0, 1, 0, 0, 0}
        3. priklad
            vstup: length = 5, indexOfOne = 5
            vyhodi vynimku, ktorej metoda 'getLength' vrati 5 a 'getIndex' vrati 5
        4. priklad
            vstup: length = 5, indexOfOne = 10
            vyhodi vynimku, ktorej metoda 'getLength' vrati 5 a 'getIndex' vrati 10
        5. priklad
            vstup: length = 0, indexOfOne = 0
            vyhodi vynimku, ktorej metoda 'getLength' vrati 0 a 'getIndex' vrati 0
*/

class IndexOutOfRangeException {
private:
    const size_t length;
    const size_t index;
public:
    IndexOutOfRangeException(size_t length, size_t index) noexcept
            : length(length)
            , index(index) {
    }

    size_t getLength() const noexcept {
        return length;
    }

    size_t getIndex() const noexcept {
        return index;
    }

    string what() const noexcept {
        return "index out of range: " + to_string(index) + " >= " + to_string(length);
    }
};

list<int> createList(const list<int>::size_type length, const list<int>::size_type indexOfOne) {
    if (indexOfOne >= length) {
        throw IndexOutOfRangeException(length, indexOfOne);
    }

    std::list<int> result;
    for (size_t i = 0; i < length; i++) {
        result.push_back(i == indexOfOne ? 1 : 0);
    }
    return result;
}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

// tu mozete doplnit pomocne testovacie funkcie a datove typy

int main() {

    // tu mozete doplnit testovaci kod
    /*list<int> data = {1, 2, 3, 4, 5};
    queue<int> q = reverse(data);
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;*/ // uloha 1

    /*queue<int> q;
    for (int i = 1; i <= 5; ++i) q.push(i);
    reverse(q);
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;*/ // uloha 2

    /*auto v = create2dVector(2, 5, 10);
    for (const auto &row : v) {
        for (int x : row) cout << x << " ";
        cout << endl;
    }*/ //uloha 3

    /*cout << "4. connectWithSpace:\n";
    cout << connectWithSpace("abc", 10) << endl;
    cout << connectWithSpace(" abc ", 10) << endl;
    cout << connectWithSpace("", -10) << endl;*/ // uloha 4

    /*istringstream iss("10 20 30 10");
    cout << sum(iss) << endl;
    istringstream iss1("10 a 20");
    cout << sum(iss1) << endl;
    istringstream iss2("");
    cout << sum(iss2) << endl;*/ //uloha 5

    /*map<string, string> translator = {
        {"read", "citat"}, {"write", "pisat"}, {"book", "kniha"},
        {"I", "ja"}, {"you", "ty"}, {"he", "on"}, {"she", "ona"},
        {"it", "ono"}, {"a", ""}, {"an", ""}, {"the", ""}
    };

    list<string> s1 = {"I", "read", "a", "book"};
    list<string> s2 = {"I", "am", "reading", "a", "book"};
    list<string> s3 = {"He", "reads", "a", "book"};

    auto print_list = [](const list<string> &lst) {
        for (auto &w : lst) cout << "\"" << w << "\" ";
        cout << endl;
    };

    print_list(translate(translator, s1));
    print_list(translate(translator, s2));
    print_list(translate(translator, s3)); */ // uloha 6

    /*cout << boolalpha;
    cout << areParenthesisPaired("a + (2 * (3 + 4))") << endl;
    cout << areParenthesisPaired("ab - (c< d > 1) + {[23 ( [ 45] ) 6] 7} 8 ") << endl;
    cout << areParenthesisPaired("1 + (2") << endl;
    cout << areParenthesisPaired("(") << endl;
    cout << areParenthesisPaired("())") << endl;
    cout << areParenthesisPaired("{ >") << endl;
    cout << areParenthesisPaired("") << endl;*/ // uloha 7

    //std::cout << execute(multiply, 10, 2) << std::endl; uloha 8

    /*cout << (int)detectException(doNotThrow) << endl;
    cout << (int)detectException(throwInvalidArgument) << endl;
    cout << (int)detectException(throwBadAlloc) << endl;
    cout << (int)detectException(throwOutOfRange) << endl;*/ // uloha 9

    /*try {
        auto lst = createList(5, 1);
        for (int x : lst) cout << x << " ";
        cout << endl;
    } catch (const IndexOutOfRangeException &e) {
        cout << e.what() << endl;
    }

    try {
        auto lst = createList(5, 5); // výnimka
    } catch (const IndexOutOfRangeException &e) {
        cout << e.what() << " (len=" << e.getLength() << ", idx=" << e.getIndex() << ")" << endl;
    }*/ // uloha 10
    return 0;
}
