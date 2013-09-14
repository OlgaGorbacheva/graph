#include "graph.h"

using namespace std;

template<class TypeV,  class TypeE>
graph<TypeV, TypeE>::graph()
{ }

template<class V,  class E>
graph<V, E> graph<V, E>::transpose()
{
    graph result;
    for (vertex_iterator itr = ver.begin(), end = ver.end(); itr != end; itr++){
        std::shared_ptr<vertex<V, E> > _new (new vertex<V, E>((itr->second)->value));
        _new->rList = (itr->second)->tList;
        _new->tList = (itr->second)->rList;
        result.ver[itr->first] = _new;
    }
    return result;
}

template<class V,  class E>
std::list<std::pair<int, E> > graph<V, E>::getInEdges(int v)
{
    vertex_iterator itr = ver.find(v);
    if (itr == ver.end())
        throw "Vertex doesn't exist";
    std::list<std::pair<int, E> > edges;
    edge_iterator ed_itr = ((itr->second)->tList).begin(), ed_end = ((itr->second)->tList).end();
    for (;ed_itr != ed_end; ed_itr++)
        edges.push_back(std::make_pair(itr->first, (itr->second)->second));
    return edges;
}


template<class V,  class E>
std::list<std::pair<int, E> > graph<V, E>::getOutEdges(int v)
{
    vertex_iterator itr = ver.find(v);
    if (itr == ver.end())
        throw "Vertex doesn't exist";
    std::list<std::pair<int, E> > edges;
    edge_iterator ed_itr = ((itr->second)->rList).begin(), ed_end = ((itr->second)->rList).end();
    for (;ed_itr != ed_end; ed_itr++)
        edges.push_back(std::make_pair(itr->first, (itr->second)->second));
    return edges;
}


//template<class TypeV,  class TypeE>
//typename graph<TypeV, TypeE>::edges_iterator graph<TypeV, TypeE>::r_check_existed_ver(shared_ptr<vertex<TypeV> > v)
//{
//    edges_iterator i;
//    for (i = rList.begin(); i != rList.end(); i++){
//        shared_ptr<vertex<TypeV> > current_vertex;
//        current_vertex = (i->begin())->first.lock(); //создаем shared_ptr от первой вершины списков смежности
//        if (current_vertex == v)
//            break;
//    }std::pair<std::shared_ptr<vertex<V,
//    if (i == rList.end())
//        throw "Vertex doesn't exist";
//    return i;
//}

//template<class TypeV,  class TypeE>
//typename graph<TypeV, TypeE>::edges_iterator graph<TypeV, TypeE>::t_check_existed_ver(shared_ptr<vertex<TypeV> > v)
//{
//    edges_iterator i;
//    for (i = tList.begin(); i != tList.end(); i++){
//        shared_ptr<vertex<TypeV> > current_vertex;
//        current_vertex = (i->begin())->first.lock(); //создаем shared_ptr от первой вершины списков смежности
//        if (current_vertex == v)
//            break;
//    }
//    if (i == tList.end())
//        throw "Vertex doesn't exist";
//    return i;
//}

//template<class TypeV,  class TypeE>
//istream& operator >> (istream &cin, graph<TypeV, TypeE>& _graph)
//{
//    _graph.rList.clear();
//    _graph.tList.clear();
//    _graph.ver.clear();
//    unsigned int n;
//    cin >> n; //количество вершин
//    for (unsigned int i = 0; i < n; i++){
//        TypeV _data;
//        cin >> _data;
//        _graph.InsertV(_data);
//    }
//    for (unsigned int i = 0; i < n; i++){
//        unsigned int m;
//        cin >> m;
//        for (unsigned int j = 0; j < m; j++){
//            TypeE _data;
//            int num;
//            cin >> num >> _data;
//            _graph.InsertE(_graph.ver[i], _graph.ver[num], _data);
//        }
//    }
//    return cin;
//}

//template<class TypeV,  class TypeE>
//ostream& operator << (ostream &cout, graph<TypeV, TypeE>& _graph)
//{
//    cout << _graph.ver.size() << endl; //количество вершин
//    for (unsigned int i = 0; i < _graph.ver.size(); i++){
//        cout << _graph.ver[i]->get() << ' ';
//    }
//    cout << endl;
//    for (unsigned int i = 0; i < _graph.ver.size(); i++){
//        cout << endl;
//        typename graph<TypeV, TypeV>::edges_iterator it = _graph.r_check_existed_ver(_graph.ver[i]);
//        cout << (it->size() - 1) << endl;
//        list<pair<weak_ptr<vertex<TypeV> >, TypeE> > out = _graph.getOutEdges(_graph.ver[i]);
//        for (auto l_it = out.begin(); l_it != out.end(); l_it++){
//            shared_ptr<vertex<TypeV> > current = l_it->first.lock();
//            typename vector<shared_ptr<vertex<TypeV> >>::iterator e_it = find(_graph.ver.begin(), _graph.ver.end(), current);
//            if (e_it == _graph.ver.end())
//                throw "Vertex doesn't exist";
//            cout << (e_it - _graph.ver.begin()) << ' ';
//            cout << l_it->second << ' ';
//        }
//    }
//    return cout;
//}

//template<class TypeV,  class TypeE>
//list<pair<weak_ptr<vertex<TypeV> >, TypeE> > graph<TypeV, TypeE>::getOutEdges(shared_ptr<vertex<TypeV> > v)
//{
//    edges_iterator it = r_check_existed_ver(v);
//    auto it_end = it->end();
//    return { ++(it->begin()), it_end};
////    return {(r_check_existed_ver(v))->begin() + 1, (r_check_existed_ver(v))};
//}

//template<class TypeV,  class TypeE>
//vector<weak_ptr<vertex<TypeV> > > graph<TypeV, TypeE>::getVertex()
//{
//    vector<weak_ptr<vertex<TypeV> > > ver_list;
//    for (existed_vertex_iterator i = ver.begin(); i != ver.end(); i++){
//        ver_list.push_back(*i);
//    }
//    return ver_list;
//}

//template<class TypeV,  class TypeE>
//void graph<TypeV, TypeE>::InsertV(TypeV _data)
//{
//    shared_ptr<vertex<TypeV> > ver_ptr(new vertex<TypeV>(_data));
//    ver.push_back(ver_ptr);
//    rList.resize(rList.size() + 1);
//    rList[rList.size() - 1].resize(1);
//    (rList[rList.size() - 1].begin())->first = static_cast<weak_ptr<vertex<TypeV> > >(ver_ptr);
//    tList.resize(tList.size() + 1);
//    tList[rList.size() - 1].resize(1);
//    (tList[rList.size() - 1].begin())->first = static_cast<weak_ptr<vertex<TypeV> > >(ver_ptr);
//}

//template<class TypeV,  class TypeE>
//void graph<TypeV, TypeE>::InsertE(shared_ptr<vertex<TypeV> > v1, shared_ptr<vertex<TypeV> > v2, TypeE _data)
//{
//    edges_iterator v1_ei = r_check_existed_ver(v1);
//    edges_iterator v2_ei = t_check_existed_ver(v2);
//    v1_ei->push_back(make_pair(static_cast<weak_ptr<vertex<TypeV> > >(v2), _data));
//    v2_ei->push_back(make_pair(static_cast<weak_ptr<vertex<TypeV> > >(v1), _data));
//}

////template<class TypeV,  class TypeE>
////typename graph<TypeV, TypeE>::iterator_dfs graph<TypeV, TypeE>::begin_dfs()
////{
////    iterator_dfs itr(this);
////    ++itr;
////    return itr;
////}

////template<class TypeV,  class TypeE>
////typename graph<TypeV, TypeE>::iterator_dfs graph<TypeV, TypeE>::end_dfs()
////{
////    iterator_dfs itr(this);
////    itr.elem = ver.end();
////    return itr;
////}

////template<class DataV,  class DataE>
////typename graph<DataV, DataE>::iterator_bfs graph<DataV, DataE>::begin(int)
////{
////    iterator_bfs itr(this);
////    ++itr;
////    return itr;
////}

////template<class DataV,  class DataE>
////typename graph<DataV, DataE>::iterator_bfs graph<DataV, DataE>::end(int)
////{
////    iterator_bfs itr(this);
////    itr.elem = Inf.end();
////    return itr;
////}
