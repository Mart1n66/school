void main() {
    int[] data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // break
    for (int value : data) {
        if (value > 5) {
            break;
        }
        IO.print(value); // 12345
    }
    IO.println();

    // continue
    for (int value : data) {
        if (value % 2 == 0) {
            continue;
        }
        IO.print(value); // 13579
    }
    IO.println();

    // break, label (navestie)
    loop1:
    for (int value : data) {
        for (int i = 0; i < 3; ++ i) {
            if (value > 5) {
                break loop1;
            }
            IO.print(value); // 111222333444555
        }
    }
    IO.println();

    // continue, label (navestie)
    loop2:
    for (int i = 0; i < 3; ++ i) {
        for (int value : data) {
            if (value > 5) {
                continue loop2;
            }
            IO.print(value); // 123451234512345
        }
    }
    IO.println();

}
