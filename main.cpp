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
    cout << v1->getId() <<' '<< v2->getValue() << ' ' << e.getValue() << ' ' << e.getVertexes().first;
    return 0;
}

