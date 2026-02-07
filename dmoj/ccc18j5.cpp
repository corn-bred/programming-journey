#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

pair<bool, int> BFS(vector<int> graph[10000], int size) {
    bool reachable; int shortestpath;

    vector<bool> graphpassed;//did it pass all of the pages? if yes, then reachable = true;
    graphpassed.resize(size, false);
    
    vector<int> togo;
    vector<int> nexttogo;
    togo.push_back(0);
    int indextogoempty = 1;

    bool init = true;

    while(!togo.empty()) {
        nexttogo.erase(nexttogo.begin(), nexttogo.end());

        if (!init)
        togo = nexttogo;

        const int currplace = togo.front();

        

        if (graphpassed[currplace] == false) {
            graphpassed[currplace] = true;

            for (int i = 0; i < graph[currplace].size(); i++) {
                nexttogo.push_back(graph[currplace][i]);
            }

            {
                reachable = true;
                for (int i = 0; i < size; i++) {
                    if (graphpassed[i] != true) {reachable = false; goto cont;}
                }
                cont:
            }

        if (graph[currplace].empty()) { //is the current place of the vector empty? if so, then its an ending and you end it
            shortestpath = indextogoempty;
        }
        } else {
            
        }

        
        togo.pop_back();
        indextogoempty++;
        init = false;
    }
    pair<bool, int> tmppair = {reachable, shortestpath};
    return tmppair;
}

int main () {
    ios::sync_with_stdio(0);
    
    string tmppages;
    
    getline(cin, tmppages);

    const int pages = stoi(tmppages);

    vector<int> graph[10000];

    for (int i = 0; i < pages; i++) {
        //cout << "graph[" << i << "]: ";
        string input;
        getline(cin, input);
        
        stringstream sinput(input);
        cout << sinput.str() << endl;

        int tmppush_back;
        sinput >> tmppush_back; //remove the thing
        while (sinput >> tmppush_back) {
            cout << tmppush_back << endl;
            if (tmppush_back == 0) {
                cout << "AHHHH" << endl;
                graph[i].push_back(0);
            } else {
                graph[i].push_back(tmppush_back);
            }
        }
    }

    //
    for (int i = 0 ; i < pages; i++) {
        for (int j = 0; j < graph[i].size(); j++) {
            cout << graph[i][j] << ' ';
        }
        cout << endl;
    }
    //
    pair<bool, int> Pair = BFS(graph, pages);

    cout << (Pair.first? "Y" : "N") << "\n" << Pair.second << "\n";
    return 0;
}