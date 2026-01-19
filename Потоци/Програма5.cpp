#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream file("ArrayData.txt"); // Отваря файла за четене
    if (!file.is_open()) {
        cout << "Не може да се отвори файла!" << endl;
        return 1;
    }

    int sum = 0, number;
    int count = 0;

    // Четене на 10 числа от един ред
    while (file >> number) {
        sum += number;
        count++;
        if (count == 10) break; // Спираме след 10 числа
    }

    file.close();

    if (count == 0) {
        cout << "Файлът е празен или няма числа!" << endl;
        return 1;
    }

    double average = (double)sum / count;
    cout << "Средноаритметичното на числата е: " << average << endl;

    return 0;
}
