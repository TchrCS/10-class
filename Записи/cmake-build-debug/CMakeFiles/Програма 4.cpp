#include <iostream>
#include <string>

using namespace std;

struct Movie {
    string name;
    string genre;
    int year;
};

Movie createMovie() {
    Movie m;
    getline(cin, m.name);
    getline(cin, m.genre);
    cin.ignore();
    cin >> m.year;
}

Movie getNewestMovie(Movie m[] ) {
    Movie newestMovie;
    for (int i = 0; i < 5; i++) {
        if (m[i].year > newestMovie.year) {
            newestMovie = m[i];
        }
    }
    return newestMovie;
}

void printMovie(Movie m) {
    cout <<"Name: "<< m.name << endl;
    cout <<"Genre: "<< m.genre << endl;
    cout <<"Year: "<< m.year << endl;

}

void printMovieByReference(const Movie& m) {
    cout << m.name << " (" << m.year << ")" << endl;
}

void printMovieByPointer(const Movie* mPtr) {
    cout << mPtr->name << " (" << mPtr->year << ")" << endl;
}
int main() {

    Movie m[5];
    for (int i = 0; i < 5; i++) {
        createMovie();
    }

    Movie newestMovie = getNewestMovie(m);
    for (int i = 0; i < 5; i++) {
        printMovie(newestMovie);
    }

    return 0;
}
