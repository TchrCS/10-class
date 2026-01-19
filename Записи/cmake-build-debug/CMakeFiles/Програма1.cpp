#include <iostream>
//#include <string>
using namespace std;


int main() {
    int n;
    cout << "Въведете брой ученици: ";
    cin >> n;
    cin.ignore();

    string name[100], speciality[100];
    int grade[100];
    double score[100];

    for(int i = 0; i < n; i++){
        cout << "\nУченик " << i+1 << ":" << endl;
        cout << "Име: ";
        getline(cin, name[i]);
        cout << "Клас: ";
        cin >> grade[i];
        cin.ignore();
        cout << "Специалност: ";
        getline(cin, speciality[i]);
        cout << "Успех: ";
        cin >> score[i];
        cin.ignore();
    }

    // Изчисляване на среден успех
    double sum = 0;
    for(int i = 0; i < n; i++){
        sum += score[i];
    }
    double average = sum / n;

    // Сортиране по успех (низходящо) - bubble sort
    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < n-i-1; j++){
            if(score[j] < score[j+1]){
                // размяна на успех
                double tempScore = score[j];
                score[j] = score[j+1];
                score[j+1] = tempScore;

                // размяна на имената
                string tempName = name[j];
                name[j] = name[j+1];
                name[j+1] = tempName;

                // размяна на класовете
                int tempGrade = grade[j];
                grade[j] = grade[j+1];
                grade[j+1] = tempGrade;

                // размяна на специалност
                string tempSpec = speciality[j];
                speciality[j] = speciality[j+1];
                speciality[j+1] = tempSpec;
            }
        }
    }

    // Извеждане
    cout << "\nСреден успех на групата: " << average << endl;
    cout << "\nУченици, подредени по успех:\n";

    for(int i = 0; i < n; i++){
        cout << name[i] << ", " << grade[i] << " клас, "
             << speciality[i] << ", успех: " << score[i] << endl;
    }

    return 0;
}
