void  main() {
    for (int i = 1; i <= 10; ++ i) {
        IO.print(i + " "); // bez odriadkovania (bez ln)
    }
    IO.println(); // odriadkovanie

    char[] data = {'a', 'b', 'c', 'd'};

//  char[] a, b; // Obe premenne (a aj b) su polia
//  char a[], b; // 'a' je pole, ale 'b' je len jeden obycajny char

    for (int i = 0; i < data.length; ++ i) {
        IO.print(data[i] + " ");
    }
    IO.println(); // potom zamena za enhanced for loop

    for (char d: data) { // for each
        IO.print(d + " ");
    }
    IO.println();

    boolean opakuj = true;
    while (opakuj) {
        IO.println("while");
        opakuj = false;
    }

    do {
        IO.println("do while");
    } while (opakuj);
}
