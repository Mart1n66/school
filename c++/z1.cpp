
#include <iostream>
#include <climits>


using namespace std;


struct Position {
    int x; // x-ova suradnica
    int y; // y-ova suradnica
};

// Datum
struct Date {
    int year;  // rok
    int month; // mesiac
    int day;   // den
};

// Uspesnost vykonania funkcie
enum class Result {
    SUCCESS, // funkcia vykonana uspesne
    FAILURE  // chyba pri vykonavani funkcie
};

void print(const Position *position) {
    std::cout << "x: " << position->x << ", y: " << position->y << std::endl;
}


void print(const Position &position) {
    std::cout << "x: " << position.x << ", y: " << position.y << std::endl;
}

void readFromStandardInput(Position *position) {
    std::cin >> position->x >> position->y;
}

int maximum(const int *data, std::size_t length, Result *result) {
    if (length == 0) {
        *result = Result::FAILURE;
        return INT_MIN;
    }
    *result = Result::SUCCESS;
    int max = data[0];
    for (std::size_t i = 1; i < length; i++) {
        if (data[i] > max) {
            max = data[i];
        }
    }
    return max;
}

int numDigits(int value) {
    int digits = 0;
    if (value == 0) {
        return 1;
    }
    if (value < 0) {
        value = -value;
        digits++;
    }
    while (value != 0) {
        value = value / 10;
        digits++;
    }
    return digits;
}

void print(const Date *date, const char *format) {
    for (const char *p = format; *p != '\0'; ++p) {
        if (*p == 'D') {
            std::cout << date->day;
        } else if (*p == 'M') {
            std::cout << date->month;
        } else if (*p == 'Y') {
            std::cout << date->year;
        } else {
            std::cout << *p;
        }
    }
    std::cout << std::endl;
}

Date* create(int day, int month, int year) {
    Date* date = new Date;
    date->year = year;
    date->month = month;
    date->day = day;
    return date;
}

void destroy(Date **date) {
    delete (*date);
    *date = nullptr;
}

bool isInLeapYear(const Date *date) {
    return date->year % 4 == 0 && (date->year % 100 != 0 || date->year % 400 == 0);
}

bool isValid(const Date *date) {
    bool leap_year = isInLeapYear(date);
    if (date->month < 1 || date->month > 12) {
        return false;
    }
    int days_in_every_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (leap_year) {
        days_in_every_month[1] = 29;
    }
    if (date->day < 1 || date->day > days_in_every_month[date->month - 1]) {
        return false;
    }
    return true;
}

int main() {

    Position position = {.x = 10,
    .y = 20,};
    int data[5] = {1,2,7,4,5};
    Date date = {
        .year = 2025,
        .month = 7,
        .day = 5,
    };
    Date *date2 = create(31,10,2400);;
    Result result;
    print(&position);
    print(position);
    readFromStandardInput(&position);
    std::cout << "" << maximum(data,5,&result) << std::endl;//printf("%d\n", maximum(data, 5, &result));
    std::cout << "" << numDigits(25) << std::endl;
    print(&date, "D. Y....D...M    ghroevevev");
    print(date2, "D.D....Y M");
    std::cout << "" << isInLeapYear(date2) << std::endl;
    std::cout << "" << isValid(date2) << std::endl;
    destroy(&date2);
    return 0;
}
