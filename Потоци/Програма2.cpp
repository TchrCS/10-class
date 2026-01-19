#include <iostream>
#include <fstream>
using namespace std;

int main() {
int n;
    ofstream file("ArrayData.txt");
for (int i=0;i<10;i++) {
    cin>>n;
    file<<n << " ";
}
    file.close();
    return 0;
}
