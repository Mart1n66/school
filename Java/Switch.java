void main() {
    int option = 2;

    // switch - prikaz
    switch (option) {
        case 1:
            IO.println("jeden");
            break;
        case 2:
        case 3:
            IO.println("dva alebo tri");
            break;
        case 4:
            IO.println("styri");
            break;
        default:
            IO.println("ani jeden specialny pripad");
    }

    // switch - vyraz, ma hodnotu
    String text = switch (option) {
        case 1 -> "jeden";
        case 2, 3 -> "dva alebo tri";
        case 4 -> "styri";
        default -> "ani jeden specialny pripad";
    }; // bodkociarka
    IO.println(text);

    // if else sa neda pouzit ako vyraz, ale mozme pouzit ternarny operator ?:
    String text2 = true ? "pravda" : "nepravda";
    String text3 = false ? "pravda" : "nepravda";
    IO.println(text2); // pravda
    IO.println(text3); // nepravda
}
