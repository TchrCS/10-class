#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Student {
    string name;
    int numberInClass;
    int grade;
};

int main() {
    int MAX_STUDENTS = 15;
    Student students[MAX_STUDENTS];

    ifstream file("Student.txt");
    if (!file.is_open()) {
        cout << "404!" << endl;
        return 1;
    }

    // Четене на 15 ученика
    for (int i = 0; i < MAX_STUDENTS; i++) {
        file >> students[i].name;
        file >> students[i].numberInClass;
        file >> students[i].grade;
    }
    file.close();

    // Сортиране по име (Bubble sort)
    for


    for (int i = 0; i < MAX_STUDENTS - 1; i++) {
        for (int j = 0; j < MAX_STUDENTS - i - 1; j++) {
            if (students[j].name > students[j + 1].name) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    // Извеждане на учениците
    cout << "Учениците подредени по азбучен ред:" << endl;
    for (int i = 0; i < MAX_STUDENTS; i++) {
        cout << students[i].name << " " 
             << students[i].gradeClass << " " 
             << students[i].number << " " 
             << students[i].yearMark << endl;
    }

    return 0;
}
