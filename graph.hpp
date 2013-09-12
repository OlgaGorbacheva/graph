#include "graph.h"

using namespace std;

template<class TypeV,  class TypeE>
graph<TypeV, TypeE>::graph()
{ }

//template<class DataV,  class DataE>
//istream& operator >> (istream &cin, graph<DataV, DataE>& _graph)
//{
//    unsigned int n;
//    cin >> n;
//    _graph.AdjR.resize(n);
//    _graph.AdjT.resize(n);
//    for (unsigned int i = 0; i < n; i++){
//        unsigned int m;
//        DataV _data;
//        cin >> _data;
//        _graph.Inf.push_back(_data);
//        cin >> m;
//        if (m > (n - 1)){
//            cerr << i << endl;
//            throw "too many edges";
//        }
//        for (unsigned int j = 0; j < m; j++){
//            unsigned int k;
//            DataE _data;
//            cin >> k;
//            if (k > (n - 1))
//                throw "unexpectable edge";
//            cin >> _data;
//            _graph.AdjR[i].push_back(make_pair(k, _data));
//        }
//        typename list<pair<int, DataE> >::iterator itr = _graph.AdjR[i].begin(), end = _graph.AdjR[i].end();
//        for (; itr != end; itr++){
//            _graph.AdjT[itr->first].push_back(make_pair(i, itr->second));
//        }
//    }
//    return cin;
//}

//template<class DataV,  class DataE>
//ostream& operator << (ostream &cout, graph<DataV, DataE>& _graph)
//{
//    cout << _graph.AdjR.size() << endl;
//    for (unsigned int i = 0; i < _graph.AdjR.size(); i++){
//        cout << _graph.Inf[i] << ' ';
//        cout << _graph.AdjR[i].size() << ' ';
//        typename list<pair<int, DataE> >::iterator itr = _graph.AdjR[i].begin(), end = _graph.AdjR[i].end();
//        for (; itr != end; itr++){
//            cout << (*itr).first << ' ';
//            cout << (*itr).second << ' ';
//        }
//        cout << endl;
//    }
//    return cout;
//}

template<class TypeV,  class TypeE>
graph<TypeV, TypeE> graph<TypeV, TypeE>::transpose()
{
    graph result;
    result.ver = ver;
    result.rList = tList;
    result.tList = rList;
    return result;
}

template<class TypeV,  class TypeE>
list<pair<weak_ptr<vertex<TypeV> >, TypeE> > graph<TypeV, TypeE>::getInEdges(shared_ptr<vertex<TypeV> > v)
{
    edges_iterator i;
    for (i = rList.begin(); i != rList.end(); i++){
        shared_ptr<vertex<TypeV> > current_vertex;
        current_vertex = (i->begin())->first.lock(); //создаем shared_ptr от первой вершины списков смежности
        if (current_vertex == v)
            break;
    }
    if (i == rList.end())
        throw "Vertex doesn't exist";
    return *i;
}

template<class TypeV,  class TypeE>
list<pair<weak_ptr<vertex<TypeV> >, TypeE> > graph<TypeV, TypeE>::getOutEdges(shared_ptr<vertex<TypeV> > v)
{
    edges_iterator i;
    for (i = tList.begin(); i != tList.end(); i++){
        shared_ptr<vertex<TypeV> > current_vertex;
        current_vertex = (i->begin())->first.lock(); //создаем shared_ptr от первой вершины списков смежности
        if (current_vertex == v)
            break;
    }
    if (i == tList.end())
        throw "Vertex doesn't exist";
    return *i;
}

//template<class DataV,  class DataE>
//list<pair<int, DataV> > graph<DataV, DataE>::getInVertex(unsigned v)
//{
//    if (v >= AdjT.size())
//        throw "vertex does not exist";
//    list<pair<int, DataV> > result;
//    typename list<pair<int, DataE> >::iterator itr = AdjT[v].begin(), end = AdjT[v].end();
//    for (; itr != end; itr++)
//        result.push_back(make_pair(itr -> first, Inf[itr -> first]));
//    return result;
//}

//template<class DataV,  class DataE>
//list<pair<int, DataV> > graph<DataV, DataE>::getOutVertex(unsigned v)
//{
//    if (v >= AdjR.size())
//        throw "vertex does not exist";
//    list<pair<int, DataV> > result;
//    typename list<pair<int, DataE> >::iterator itr = AdjR[v].begin(), end = AdjR[v].end();
//    for (; itr != end; itr++)
//        result.push_back(make_pair((*itr).first, Inf[(*itr).first]));
//    return result;
//}

//template<class DataV,  class DataE>
//vector< DataV> graph<DataV, DataE>::getVertex()
//{
//    return Inf;
//}

//template<class DataV,  class DataE>
//void graph<DataV, DataE>::InsertV(DataV _data)
//{
//    Inf.push_back(_data);
//    AdjR.resize(AdjR.size() + 1);
//    AdjT.resize(AdjT.size() + 1);
//}

//template<class DataV,  class DataE>
//void graph<DataV, DataE>::InsertE(unsigned int v1, unsigned int v2, DataE _data)
//{
//    if (v1 >= AdjR.size() || v2 >= AdjR.size())
//        throw "vertex does not exist";
//    AdjR[v1] = make_pair(v1, _data);
//}
//template<class DataV,  class DataE>
//typename graph<DataV, DataE>::iterator_dfs graph<DataV, DataE>::begin()
//{
//    iterator_dfs itr(this);
//    ++itr;
//    return itr;
//}

//template<class DataV,  class DataE>
//typename graph<DataV, DataE>::iterator_dfs graph<DataV, DataE>::end()
//{
//    iterator_dfs itr(this);
//    itr.elem = Inf.end();
//    return itr;
//}

//template<class DataV,  class DataE>
//typename graph<DataV, DataE>::iterator_bfs graph<DataV, DataE>::begin(int)
//{
//    iterator_bfs itr(this);
//    ++itr;
//    return itr;
//}

//template<class DataV,  class DataE>
//typename graph<DataV, DataE>::iterator_bfs graph<DataV, DataE>::end(int)
//{
//    iterator_bfs itr(this);
//    itr.elem = Inf.end();
//    return itr;
//}
