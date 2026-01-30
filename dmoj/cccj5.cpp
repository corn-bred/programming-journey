#include <iostream>
#include <string>
#include <sstream>

using namespace std;

string unionizestring(string s, int start, int end) {
    string rets;
    for (int i = start + 1; i < end && i < s.size(); i++) {
        rets.push_back(s.at(i));
    }
    return rets;
}

int findS(
    string word //The word that has B and S
    , int index //index for the B
) {
    for (int i = index; i < word.length(); i++) {
        if (word[i] == 'S') {return i;}
    }
    return -1;
}

bool isBSWord(string word) {
    int indentdepth;
    for (int i = 0; i < word.length(); i++) {
        if (word.at(i) == 'B') indentdepth++;
        if (word.at(i) == 'S') indentdepth--;
    }
    if (indentdepth == 0) {
        return true;
    } else return false;
}

bool monkeyword(string word) {
    if (!isBSWord(word)) {
        return false;
    }
    if (word.length() > 1) {
        if (word.at(0) == 'A' || word.at(0) == 'B') {
            if (word.at(0) == 'B') {

                if (findS(word, 0) != -1) {
                    string nextmonkeyword2 = unionizestring(word,1, findS(word, 1));
                    if (!monkeyword(nextmonkeyword2)) return false;

                } 
                else return false;
            }

            if (word.at(1) == 'N') {

                string nextmonkeyword = word;
                nextmonkeyword.erase(nextmonkeyword.begin());
                nextmonkeyword.erase(nextmonkeyword.begin());
                cout << nextmonkeyword << endl;
                if (!monkeyword(nextmonkeyword)) {return false;}
                
            } else {return false;}
        } else {return false;}
    } else {
        if (word != "A") return false;
    }
    return true;
}



int main() {
    string word = "HELLO WORLD";
    while (word != "X") {
        cin >> word;
        cout << monkeyword(word) << endl;
    }
    //cout << unionizestring(word, 1, 10); //LLO WORL
    return 0;
}