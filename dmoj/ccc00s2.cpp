#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main () {
    int n;
    float tmpINPUT;
    //cout << "enter in number of streams" << endl;
    cin >> n;
    vector<float> streams;
    //cout << "enter in streams" << endl;
    for (int i = 0; i < n; i++) {
        cin >> tmpINPUT;
        streams.push_back(tmpINPUT);
    }
    //cout << "enter in behavior" << endl;
    do {
        //for (auto x : streams) {
        //    cout << round(x) << ' ';
        //}
        //cout << endl;
        cin >> tmpINPUT;
        //cout << "tmpINPUT: " << tmpINPUT << endl;
        if (tmpINPUT == 99) { // SPLIT
            //array #
            cin >> tmpINPUT;
            int streampos = tmpINPUT -1; //because "labelled 1 to n", not "labelled 0 to n"
            //percentage
            cin >> tmpINPUT;
            float Lstream, Rstream;
            Lstream = streams.at(streampos) * (tmpINPUT / 100.0f); // /100 to turn it into a decimal
            //cout << "Lstream: " << Lstream << endl;
            Rstream = streams.at(streampos) - Lstream;
            //cout << "Rstream: " << Rstream << endl;
            streams.erase( streams.begin() + (streampos) ); // to make it still work against vector
            streams.insert(streams.begin() + (streampos), Rstream);
            streams.insert(streams.begin() + (streampos), Lstream);
        } else if (tmpINPUT == 88) { // JOIN
            //array#
            cin >> tmpINPUT;
            //implement
            int streampos = tmpINPUT - 1;
            float joinedstream;

            joinedstream = streams.at(streampos) + streams.at(streampos + 1);
            //delete the former
            streams.erase(streams.begin() + streampos, streams.begin() + streampos + 2);
            //add the new
            streams.insert(streams.begin() + streampos, joinedstream);
        } else if (tmpINPUT == 77) break;
    } while (true);
    for (auto x : streams) {
            cout << round(x) << ' ';
    }
    //cout << endl;
    return 0;
}