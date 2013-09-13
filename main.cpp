#include "graph.h"
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream fin("/home/olga/Documents/program/3rd_semester/graph/input.txt");
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
    graph<int, int> V = G.transpose();
    cout << V << endl;
////    graph<int, int>::iterator_bfs itr = G.begin(5), end = G.end(5);
////    for (; itr != end; ++itr)
////        cout << *itr;
////    cout << endl;
//    graph<int, int>::iterator_dfs itr = G.begin_dfs(), end = G.end_dfs();
//    for (; !(itr == end); ++itr)
//        cout << *itr << endl;
    cout << endl;
    return 0;
}

