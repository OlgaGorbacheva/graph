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
    int a = 1, b = 2;
    my::vertex<int, int, int> *v1 = new my::vertex<int, int, int>(a),
            *v2 = new my::vertex<int, int, int>(b);
    shared_ptr<my::vertex<int, int, int> > *p_v1 = new shared_ptr<my::vertex<int, int, int> > (v1),
            *p_v2 = new shared_ptr<my::vertex<int, int, int> >(v2);
    weak_ptr<my::vertex<int, int, int> > w_v1(*p_v1), w_v2(*p_v2);
    my::edge<int, int, int> e(w_v1, w_v2);
    try{
        cout << v1->getId() << ' ' ;
        cout << v2->getValue() << ' ' ;
        delete p_v1;
        cout << e.getValue() << ' ' ;
        cout << e.getVertexes().first << ' ' ;
        cout << e.getVertexes().second;
    }
    catch(char const* s){
        cerr << s;
    }

    return 0;
}

