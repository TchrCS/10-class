#include <iostream>
#include <string>

using namespace std;

struct Car {
    string brand;   // марка
    string model;   // модел
    int year;       // година
    double price;   // цена
};

Car createCar() {
    Car car;
    // Въвеждане на данни
        cout << "Марка: ";
        getline(cin, car.brand);

        cout << "Модел: ";
        getline(cin, car.model);

        cout << "Година: ";
        cin >> car.year;

        cout << "Цена: ";
        cin >> car.price;
        cin.ignore();
    return car;
}

//Напишете функцията тук
int cheapestCar(Car cars[], int length) {
    int minIndex = 0;
    for(int i = 0; i < length; i++) {
        if (cars[minIndex].price > cars[i].price) {
            minIndex = i;
        }
    }
    return minIndex;
}


int main() {

    Car cars[3];
    for(int i = 0; i < 3; i++) {
        cars[i] = createCar();
    }

    int minIndex = cheapestCar(cars, 3);
    // Извеждане на резултат
    cout << "\nНай-евтиният автомобил е:\n";
    cout << "Марка: " << cars[minIndex].brand << endl;
    cout << "Модел: " << cars[minIndex].model << endl;
    cout << "Година: " << cars[minIndex].year << endl;
    cout << "Цена: " << cars[minIndex].price << endl;

    return 0;
}
