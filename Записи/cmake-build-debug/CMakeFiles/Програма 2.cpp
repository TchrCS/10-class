#include <iostream>
#include <string>
using namespace std;

struct Student {
    string name;
    int grade;
    string speciality;
    double score;
};

Student createStudent() {
    Student s;
    cout << "Enter name: ";
    cin >> s.name;
    cout << "Enter grade: ";
    cin >> s.grade;
    cout << "Enter speciality: ";
    cin >> s.speciality;
    cout << "Enter average grade: ";
    cin >> s.score;
    return s;
}

double calculateAverage(Student *s, int n) {
    double sum = 0;
    for(int i = 0; i < n; i++){
        sum += s[i].score;
    }
    return  sum / n;
}

void printStudents(Student *students, int n) {
    for(int i = 0; i < n; i++){
        cout << students[i].name << ", " << students[i].grade << " клас, "
             << students[i].speciality << ", успех: " << students[i].score << endl;
    }
}

int main() {
    int n;
    cout << "Въведете брой ученици: ";
    cin >> n;
    cin.ignore();
    Student students[n]; // масив от записи

    // Въвеждане на данни
    for(int i = 0; i < n; i++){
        students[i] = createStudent();
    }

    // Извеждане на резултати
    cout << "\nСреден успех на групата: " << calculateAverage(students, n) << endl;
    cout << "\nУченици, подредени по успех:\n";
    printStudents(students, n);

    return 0;
}
