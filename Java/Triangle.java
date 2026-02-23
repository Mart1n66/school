public class Triangle {
    void main() {
        // printTriangle(0, 5); // chceme zadavat len hlbku, preto vytvorime vhodnejsiu funkciu/metodu pre pouzivanie
        printTriangle(5);
    }

    void printTriangle(int height) { // pre pouzivanie v maine, len potrebny parameter
        printTriangle(0, height);
    }

    void printTriangle(int spaces, int height) { // pracovna, pouziva rekurziu, potrebuje dalsi parameter
        if (height < 1) {
            return;
        }

        printTriangle(spaces + 1, height - 1);

        for (int i = 0; i < spaces; ++ i) {
            IO.print(" ");
        }
        for (int i = 0; i < 2 * height -1; ++ i) {
            IO.print("*");
        }
        IO.println();
    }
}
