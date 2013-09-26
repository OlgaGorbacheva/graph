#include "graph.h"
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
//    ifstream fin("/home/olga/Documents/program/3rd_semester/graph/input.txt");
//    if (!fin.is_open()){
//        cerr << "Input error" << endl;
//        return 0;
//    }
//    ofstream fout("/home/olga/Documents/program/3rd_semester/graph/output.txt");
//    if (!fout.is_open()){
//        cerr << "Input error" << endl;
//        return 0;
    int a = 1, b = 2, c = 5;
    my::graph<int, int, int>::vertex *v1 = new my::graph<int, int, int>::vertex(a, a),
            *v2 = new my::graph<int, int, int>::vertex(b, b);
    shared_ptr<my::graph<int, int, int>::vertex> *p_v1 = new shared_ptr<my::graph<int, int, int>::vertex> (v1),
            *p_v2 = new shared_ptr<my::graph<int, int, int>::vertex>(v2);
    weak_ptr<my::graph<int, int, int>::vertex> w_v1(*p_v1), w_v2(*p_v2);
    my::graph<int, int, int>::edge e(w_v1, w_v2, c);
    my::graph<int, int, int> G;
//    cout << v1->getId() <<' '<< v2->getValue() << ' ' << e.getValue() << ' ' << e.getVertexes().first;
    my::graph<int, int, int>::direct_vertex_iterator itr = G.insertVertex(1, 1);
    G.insertVertex(2, 8);
    G.insertVertex(3, 9);
    my::graph<int, int, int>::direct_edge_iterator itr2 = G.insertEdge(1, 2, 3);
    G.insertEdge(2, 3, 4);
    G.eraseEdge(itr2);
    G.eraseEdge(2, 3);
    try{
    my::graph<int, int, int> V = G.transpose();
    my::graph<int, int, int> K(G);
    K = V;
    }
//    G.insertEdge(1,);
//    try{
//        G.eraseEdge(1, 2);
//    }

//    G.eraseVertex(2);
//    try{
//        G.eraseVertex(8);
//    }
    catch(char const *s){
        cerr << s;
    }
//    G.eraseVertex(1);
//    try{
//        G.eraseVertex(itr);
//    }

    return 0;
}

