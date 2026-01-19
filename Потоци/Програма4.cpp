#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream file("ArrayData.txt");
    if (!file.is_open()) {
        cerr << "404!" << endl;
    }
    string line;
    int index = 0;
    double avg = 0;
    while (getline(file,line)) {
        cout << line << endl;
       for (int i = 0; i < line.size(); i++) {
           if (line[i] == ' ') { index++; }
           else {
               avg += stoi(line[i]);
           }
       }
        avg = avg / (index+1);
    }
    cout << "Average is " << avg << endl;
    file.close();
    return 0;
}
