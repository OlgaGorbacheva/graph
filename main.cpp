#include "graph.h"
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream fin("input.txt");
    if (!fin.is_open()){
        cerr << "Input error" << endl;
        return 0;
    }
    graph<int, int> G;
    try{
        fin >> G;
    }
    catch(char const *s){
        cerr << s;
    }
//    graph<int, int>::iterator_bfs itr = G.begin(5), end = G.end(5);
//    for (; itr != end; ++itr)
//        cout << *itr;
//    cout << endl;
    graph<int, int>::iterator_dfs itr = G.begin(), end = G.end();
    for (; itr != end; ++itr)
        cout << *itr;
    cout << endl;
    return 0;
}

