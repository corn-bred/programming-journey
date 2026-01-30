#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

string input1, input2;

int main () {
    getline(cin, input1);
    stringstream sinput1(input1);
    input1.clear();
    string tmpinput1;
    while (sinput1 >> tmpinput1) {
        input1.append(tmpinput1);
    }
    sort(input1.begin(), input1.end());
    //cout << input1 << endl;

    getline(cin, input2);
    stringstream sinput2(input2);
    input2.clear();
    string tmpinput2;
    while (sinput2 >> tmpinput2) {
        input2.append(tmpinput2);
    }
    sort(input2.begin(), input2.end());
    //cout << input2 << endl;
    if (input1 == input2) cout << "Is an anagram." << endl; else cout << "Is not an anagram." << endl;
    
    return 0;
}