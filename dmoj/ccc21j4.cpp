#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main () {
    int numberofswaps = 0;
    ios::sync_with_stdio(0);
    cin.tie(0);

    string input;
    vector<int> books;
    cin >> input;

    for (auto x : input) {
        if (x == 'L') {
            books.push_back(3);
        }
        if (x == 'M') {
            books.push_back(2);
        }
        if (x == 'S') {
            books.push_back(1);
        }
    }

    /*for (auto x:books) {
        cout << x << " ";
    }
    cout << endl;*/

    int currentIndexSort = 0;

    while (currentIndexSort < books.size()) {
        //cout << "vector [" << currentIndexSort << "]\n";

        int biggestNumberIndex = currentIndexSort;
        //cout << biggestNumberIndex << endl;

        //cout << "Find smallest number..." << endl;
        for (int i = currentIndexSort; i < books.size(); i++) {
            if (books.at(i) > books.at(biggestNumberIndex)) {
                biggestNumberIndex = i; 
                //cout << "found bigger number at index " << biggestNumberIndex << " which holds: " << books.at(biggestNumberIndex) << endl;
            }
        }

        //cout << "Swapping..." << endl;

        if (books.at(biggestNumberIndex) != books.at(currentIndexSort)) {
                swap(books.at(biggestNumberIndex), books.at(currentIndexSort));
                numberofswaps++;
        }

        //cout << "after sorting array " << currentIndexSort << ": ";
        /*for (auto x:books) {
        cout << x << " ";
        }
        cout << endl;*/
        currentIndexSort++;
    }
    /*for (auto x:books) {
        cout << x << " ";
    }
    cout << endl;*/

    cout << numberofswaps << endl;

    return 0;
}