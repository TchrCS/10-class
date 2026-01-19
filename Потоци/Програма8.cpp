#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Структура за автомобил
struct Car {
    string brand;
    string model;
    int year;
    double price;
};

// Функция за въвеждане на автомобил
Car inputCar() {
    Car c;
    cout << "Въведете марка: ";
    cin.ignore();
    getline(cin, c.brand);
    cout << "Въведете модел: ";
    getline(cin, c.model);
    cout << "Въведете година: ";
    cin >> c.year;
    cout << "Въведете цена: ";
    cin >> c.price;
    return c;
}

// Функция за запис на автомобил във файл
void writeCarToFile(const Car &c, const string &filename) {
    ofstream file(filename, ios::app); // добавяне
    if (!file.is_open()) {
        cout << "Не може да се отвори файла!" << endl;
        return;
    }
    file << c.brand << " " << c.model << " " << c.year << " " << c.price << endl;
    file.close();
}

// Функция за четене на автомобили от файл и намиране на най-евтиния
Car findCheapestCar(const string &filename, int numCars) {
    ifstream file(filename);
    Car cheapest, c;
    if (!file.is_open()) {
        cout << "Не може да се отвори файла!" << endl;
        return cheapest;
    }

    for (int i = 0; i < numCars; i++) {
        file >> c.brand >> c.model >> c.year >> c.price;
        if (i == 0 || c.price < cheapest.price) {
            cheapest = c;
        }
    }

    file.close();
    return cheapest;
}

int main() {
    string filename = "Cars.txt";

    // Въвеждане на 10 автомобила
    for (int i = 0; i < 10; i++) {
        cout << "\nАвтомобил #" << i + 1 << ":\n";
        Car c = inputCar();
        writeCarToFile(c, filename);
    }

    // Намиране на най-евтиния автомобил
    Car cheapest = findCheapestCar(filename, 10);
    cout << "\nНай-евтиният автомобил е:\n";
    cout << "Марка: " << cheapest.brand 
         << ", Модел: " << cheapest.model 
         << ", Година: " << cheapest.year 
         << ", Цена: " << cheapest.price << endl;

    return 0;
}
