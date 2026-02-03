#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

vector <int> subtract(vector <int> digits, const int amount) {
    //cout << "amount = " << amount << endl;
    //cout << "started subtract(), digits.at(digits.back() - 1) = " << digits.at(digits.size() - 1) << endl;
    if (amount > digits.at(digits.size() - 1)) {
        //cout << "carrying" << endl;

       //if (digits.at(digits.size() - 1) == 0) { //will it turn negative once carried?
        //cout << "turned negative" << endl;

            for (int i = 0; i < 50; i++) {
                //cout << "in for loop:" << i << endl;

                if (digits.at(digits.size() - 1 - i - 1) == 0) { // just asking the same question
                    //cout << "=9" << endl;
                    digits.at(digits.size() - 1 - i - 1) = 9;
                } else {
                    //cout << "-1" << endl;
                    digits.at(digits.size() - 1 - i - 1) -= 1;
                    goto exit;
                }

            }
            exit:

        //}
        //cout << "subtracting ones digit in IF statement: " << (digits.at(digits.size() - 1)+10 - amount) << endl;
        digits.at(digits.size() - 1) = (digits.at(digits.size() - 1)+10 - amount);
    } else {
        //cout << "subtracting ones digit in ELSE statement: " << digits.at(digits.size() - 1) << " to " << (digits.at(digits.size() - 1) - amount) << endl;
        digits.at(digits.size() - 1) = (digits.at(digits.size() - 1) - amount);
    }
    //remove redundant 0s
    for (int i = 0; i < digits.size(); i++) {
        if (digits.at(0) == 0) digits.erase(digits.begin());
        else break;
    }

    return digits;
    
}

bool isDivisible(vector <int> digits) {
    if (digits.size() < 2) return false;
    if (digits.at(0) == digits.at(1)) return true; else return false;
}

int main () {
    int times;
    vector<int> digits, tmp;
    string s;
    //cout << "enter times";
    cin >> times;

    for (int p = 0; p < times; p++) {
        digits.erase(digits.begin(), digits.end());
    cin >> s;
    stringstream ss(s);
    int size = s.length();
    
    for (int i = 0; i < size; i++) {
        int x = ss.get() - '0';
        //cout << x << ' ';
        digits.push_back(x); 
    }
    tmp = digits;
    //cout << endl;
    int iteration = 0;
    while (digits.size() > 2) {
        //cout << "iteration " << iteration << endl;
        for (auto x : digits) {
            cout << x;
        }
        cout << endl;
        //cout << "digits.at(digits.back()): " << digits.back() << endl;
        int sub = digits.back();
        //cout << "sub(should be the same as digits.at(digits.back())): " << sub << endl;
        digits.pop_back();

        digits = subtract(digits, sub);
        iteration++;
    }
    //cout << "iteration " << iteration << endl;
    for (auto x : digits) {
            cout << x;
    }
    cout << endl;
    if (isDivisible(digits)) {
        cout << "The number ";
        for (auto x : tmp) {
            cout << x;
        }
        cout <<" is divisible by 11." << endl;
    } else {
        cout << "The number ";
        for (auto x : tmp) {
            cout << x;
        }
        cout <<" is not divisible by 11." << endl;
    }
    if (p < times - 1) {
        cout << "\n";
    }
}
    return 0;
}