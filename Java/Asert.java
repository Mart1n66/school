public class Assertt {
    void main() {
        IO.println(isWeekend(1)); // false
        IO.println(isWeekend(7)); // true
        IO.println(isWeekend(8)); // ak povolena kontrola assert-ami, tak program spadne
    }

    boolean isWeekend(int dayInWeek) { // dayInWeek: 1 - pondelok, 2 - utorok
        assert dayInWeek >= 1 && dayInWeek <= 7;
        assert dayInWeek >= 1 && dayInWeek <= 7: "dayInWeek should be between 1 and 7";

        return dayInWeek == 6 || dayInWeek == 7;
    }
}
