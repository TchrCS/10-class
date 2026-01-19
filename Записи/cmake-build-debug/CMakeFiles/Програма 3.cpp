#include <iostream>
using namespace std;

struct Rectangle {
    double width;
    double height;
};

// Функция за въвеждане на правоъгълник
Rectangle createRectangle() {
    Rectangle r;
    cout << "Въведете широчина и височина на правоъгълника: ";
    cin >> r.width >> r.height;
    return r;
}

//Създайте функцията тук!
double calculateArea(Rectangle r[], int n) {
    int index = 0;
    for (int i = 0; i < n; i++) {
        if (r[i].width >= r[index].width) {
            index = i;
        }
    }
    return r[index].width * r[index].height;
}

int main() {
    // Създаваме един правоъгълник чрез функция
    int n = 3;
    Rectangle r[n];
    for (int i = 0; i < n; i++) {
        r[i] = createRectangle();
    }


    cout << "Лицето на правоъгълника е: " << calculateArea(r,n) << endl;

    return 0;
}
