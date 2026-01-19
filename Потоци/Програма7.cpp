#include <iostream>
#include <fstream>
using namespace std;

// Структура за правоъгълник
struct Rectangle {
    double length;
    double width;
};

// Функция за въвеждане на правоъгълник
Rectangle inputRectangle() {
    Rectangle r;
    cout << "Въведете дължина на правоъгълника: ";
    cin >> r.length;
    cout << "Въведете ширина на правоъгълника: ";
    cin >> r.width;
    return r;
}

// Функция за изчисляване на периметър
double perimeter(const Rectangle &r) {
    return 2 * (r.length + r.width);
}

// Функция за изчисляване на лице
double area(const Rectangle &r) {
    return r.length * r.width;
}

// Функция за запис във файла
void writeRectangleToFile(const Rectangle &r, const string &filename) {
    ofstream file(filename, ios::app); // добавяне, без изтриване
    if (!file.is_open()) {
        cout << "Не може да се отвори файла!" << endl;
        return;
    }
    file << "Rectangle(" << r.length << "," << r.width << "): "
         << "P = " << perimeter(r) << " "
         << "S = " << area(r) << endl;
    file.close();
}

// Функция за извеждане на съдържанието на файла
void printFileContent(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Не може да се отвори файла!" << endl;
        return;
    }
    string line;
    cout << "\nСъдържание на файла " << filename << ":\n";
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

int main() {
    string filename = "Rectangles.txt";
    char choice;

    do {
        Rectangle r = inputRectangle();
        writeRectangleToFile(r, filename);

        cout << "Искате ли да добавите друг правоъгълник? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    // Извеждане на всички редове от файла
    printFileContent(filename);

    return 0;
}
