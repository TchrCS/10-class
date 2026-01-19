#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream file("ArrayData.txt");
    string line;
    int index = 0;
    string elementivutre[10];
    while (getline(file,line)) {
        for (int i = 0; i < line.size();i++) {
            if (line[i] == ' ') {
                index++;
            } else {
                elementivutre[index] += line[i];
                //cerr << elementivutre[4][0];
            }
            if (index == 10) break;
        }
    }
    double avg = 0;
    for (int i = 0; i < 10;i++) {
        avg += stoi(elementivutre[i]);
    }
    avg /= 10;

    cout << avg << endl;
    return 0;
}
