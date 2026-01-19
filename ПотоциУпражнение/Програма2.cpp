/**
*Създайте програма, която чете и съхранява филми от CSV файл `"Movies.csv"`.
*Програмата трябва да използва функция `getDate()` за обработка на дати.
*Програмата трябва да има конзолно меню с следните опции:
*1. sortBy() - сортира учениците по ID на ученик
*2. filterBy() - филтрира учениците по клас
*3. convertNumberInSchool() - преобразува номера в училище на символ само на филтрирани ученици
*4. addStudent() - добавя се ученик от потребилетя
*0. Изход
*Проверка за входни данни!
**/

#include <iostream>
#include <fstream>

using namespace std;

struct Student {
    int ID;
    string FirstName;
    string LastName;
    string Grade;
    int SecretMessege;
};
int readData(Student students[]) {
    ifstream file("Students.csv");
    if (!file.is_open()) {
        cerr << "404!" << endl;
        return 1;
    }
    string line;
    int i = 0;
    getline(file, line);

    while (getline(file, line)) {
        string fields[5];
        int index = 0;
        for (char c : line) {
            if (c == ',') {
                index++;
                if (index == 5) break;
            }else {
                fields[index] += c;
            }
        }
        if (index == 4) {
            students[i].ID = stoi(fields[0]);
            students[i].FirstName = fields[1];
            students[i].LastName = fields[2];
            students[i].Grade = fields[3];
            students[i].SecretMessege = stoi(fields[4]);
            i++;
        }
    }
    return i;
}
void sortByName(Student student[], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++) {
            Student temp;
            if (student[i].ID < student[j].ID) {
                temp = student[i];
                student[i] = student[j];
                student[j] = temp;
            }
        }
    }
}
int filterBy(Student student[], int size, string userInput, Student filterStudents[]) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (student[i].Grade == userInput) {
            filterStudents[count] = student[i];
            count++;
        }
    }
    return count;
}
int addStudent(Student student[], int size) {
    size++;
    student[size].ID = size;
    ofstream file("students.csv", ios::app);
    cout << "Enter first name of the student: ";
    cin >> student[size].FirstName;
    cout << "Enter last name of the student: ";
    cin >> student[size].LastName;
    cout << "Enter current grade of the student: ";
    cin >> student[size].Grade;
    cout << "Enter secret messege for the student: ";
    cin >> student[size].SecretMessege;
    file <<student[size].ID << ',' << student[size].FirstName << ',' << student[size].LastName << ',' << student[size].Grade << ',' << student[size].SecretMessege << endl;

    return size;
}
char convertNumberInSchool(Student student) {
    return (char) student.SecretMessege;
}
void printStudent(Student student) {
    cout << "Student name: " << student.FirstName << " " << student.LastName << endl;
    cout << "Strudent grade: " << student.Grade << endl;
    cout << endl;
}

int main() {
    int size = 100;
    Student students[size];

    // четем реалния брой студенти
    size = readData(students);

    Student filteredStudents[size];

    int count;
    int FirstChoose = -1;

    do {
        cout << "\nMENU:\n";
        cout << "1. Sort\n";
        cout << "2. Filter\n";
        cout << "3. Convert filtered\n";
        cout << "4. Add student\n";
        cout << "0. Exit\n";
        cout << "Choose: ";

        cin >> FirstChoose;

        switch (FirstChoose) {

            case 1:   // sortBy()
                sortByName(students, size);
                for (int i = 0; i < size; i++) {
                   printStudent(students[i]);
                }
                break;

            case 2: { // filterBy()
                string userInput;
                cout << "Enter a grade you would like to filter by: ";
                cin >> userInput;
                count = filterBy(students, size, userInput, filteredStudents);

                if (count == 0) {
                    cout << "No students!\n";
                } else {
                    for (int i = 0; i < count; i++) {
                        printStudent(filteredStudents[i]);
                    }
                }

                break;
            }

            case 3: { // convertNumberInSchool()
                cout << "Converted message: ";
                for (int i = 0; i < count; i++) {
                    cout << convertNumberInSchool(filteredStudents[i]);
                }
                cout << endl;
                break;
            }

            case 4: // addStudent()
                size = addStudent(students, size);
                break;

            case 0:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid option!\n";
        }

    } while (FirstChoose != 0);


    return 0;
}
