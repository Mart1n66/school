void main() {
    int vysledok1 = vynasob(10, 20);
    IO.println(vysledok1); // 200

    String vysledok2 = vynasob(5, 'a');
    IO.println(vysledok2); // aaaaa

}

int vynasob(int a, int b) {
    return a * b;
}

String vynasob(int pocet, char znak) {
    StringBuilder builder = new StringBuilder();
    for (int i = 0; i < pocet; ++ i) {
        builder.append(znak);
    }
    return builder.toString();
}

