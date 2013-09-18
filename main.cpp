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
    ofstream fout("/home/olga/Documents/program/3rd_semester/graph/output.txt");
    if (!fout.is_open()){
        cerr << "Input error" << endl;
        return 0;
    }
    graph<int, int> G;
//    G.insertVertex(0, 1);
//    G.insertVertex(1, 2);
//    G.insertEdge(0, 1, 5);
    fin >> G;
//    try{
//        fin >> G;
//    }
//    catch(char const *s){
//        cerr << s;
//    }
    graph<int, int> V = G.transpose();
    fout << G << endl << endl << endl << endl << V;
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

