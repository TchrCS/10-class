/**
 *Създайте програма, която чете и съхранява филми от CSV файл `"Movies.csv"`.
 *Програмата трябва да използва функция `getDate()` за обработка на дати.
 *Програмата трябва да има конзолно меню с следните опции:
 *1. sortBy() - сортира филмите по заглавията
 *2. filterBy() - филтрира филми по жанр
 *3. findFilm() - извежда цялата информация за филм по име
 *4. findNewer() - извежда всички филми по-нови от година
 *5. addMovie() - добавя се филм от потребилетя
 *0. Изход
 *Проверка на входни данни:
 *•	Проверка дали файлът съществува
 *•	Проверка за валидни числа (години 1888-2025)
 *•	Обработка на невалидни CSV редове
 *•	Максимум 100 филма
 **/
#include <iostream>
#include <fstream>

using namespace std;

// Създавам структура Film, като нейните променливи са характеристиките(първия ред), който имам в Movies.csv
//Title,Year,Genre,Director,FamousQuote
struct Movie {
    string title;
    int year;
    string genre;
    string director;
    string famousQuote;

};
Movie film[100]; // Глобално дефиниране на масив от тип Movie

void getData() {
    ifstream file("Movies.csv"); //Дефиниране и инициализиране на входен файлов поток(input file stream) "Movies.csv"
    if (!file.is_open()) { //Проверка, че файла се отваря(За да се отвори, трябва да е в същата директория)
        cout << "404!" << endl;  // cerr е добра практика
    }

    string line;
    int countFilms;
    getline(file, line); // line = Title,Year,Genre,Director,FamousQuote
    while (getline(file, line)) {
        string fields[5];
        int index = 0;

        for (char c : line) {
            if (c == ',') {
                index++;
                if (index == 5) break;
            } else {
                fields[index] += c;
            }
        }
        m.title = fields[0];
        m.year = stoi(fields[1]);
        m.genre = fields[2];
        m.director = fields[3];
        m.famousQuote = fields[4];
        countFilms++; // записваш във масив
    }
    file.close();
}
bool sortBy() {
    for (Movie m : film) {
        for (Movie n : film) {
            swap(n,m);
        }
    }
}
void findFilm(string userInput) {
    for (Movie m : film) {
        if (m.title == userInput) {
            cout << "Movies with titles: " << userInput;
            cout << m.title << "("<< m.year <<")" << endl;
            cout << "Director: " << m.director << endl;
            cout << "Famous Quote: " << m.famousQuote << endl;
        }
    }
}
void filterByString(string userInput) {
    bool check = false;
    for (Movie m : film) {
        if (m.genre == userInput) {
            cout << "Movies with titles: ";
            cout << m.title << "("<< m.year <<")" << endl;
            cout << "Director: " << m.director << endl;
            cout << "Famous Quote: " << m.famousQuote << endl;
            cout << endl;
            check == true;
        }
    }
    if (!check) {
            cout << "There is no movie fromthis ganre!";
        }
}
void findNewer(int userYear) {
    for (Movie m : film) {
        if (m.year > userYear) {
            cout << "Movies with titles: \n" << m.title << "("<< m.year <<")" << endl;
            cout << "Director: " << m.director << endl;
            cout << "Famous Quote: " << m.famousQuote << endl;
        }
    }
}

int main() {
    getData();
    cout << "Здравейте!\n Желая:\n 1 - да филтрирам\n 2 - повече информация за филм\n 3 - видя филми от тази година до сега";
    int choose = 0;
    do {
        cin >> choose;
    }while (choose <= 1 && choose >= 3);
    string userInput;
    if (choose == 1) {
        cout << "Моля въведете какъв жантър филми желате да видите: " << endl;

            cin >> userInput;
        filterByString( userInput);
    } else if (choose == 2) {
        cout << "Моля въведете какъв името на филма, за който желате да"
                " видите повече информация: " << endl;
        cin >> userInput;
        findFilm(userInput);
    }
    else if (choose = 3) {
        int userYear = 0;
        cout << "Моля въведете от коя година искате да виждате филмите: " << endl;
        do {
            cin >> userYear;
        } while (userYear > 1888 && userYear < 2026);
        findFilm(userInput);
    }
    return 0;
}