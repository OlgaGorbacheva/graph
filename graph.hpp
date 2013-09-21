#include "graph.h"


template<class I, class V, class E>
my::graph<I, V, E>::graph()
{ }

//template<class I, class V, class E>



//template<class I, class V, class E>
//template<class I, class V, class E>
//template<class I, class V, class E>
//template<class I, class V, class E>
//template<class I, class V, class E>
//template<class I, class V, class E>
//template<class I, class V, class E>
//template<class I, class V, class E>
//template<class I, class V, class E>
//template<class I, class V, class E>
//template<class I, class V, class E>
//template<class I, class V, class E>
//template<class I, class V, class E>
//template<class I, class V, class E>
//template<class V,  class E>
//graph<V, E> graph<V, E>::transpose()
//{
//    graph result;
//    for (vertex_iterator itr = ver.begin(), end = ver.end(); itr != end; itr++){
//        std::shared_ptr<vertex<V, E> > _new (new vertex<V, E>((itr->second)->value));
//        _new->rList = (itr->second)->tList; //itr->second - это shared_ptr на вершину графа, на кот в map вершин указывает itr
//        _new->tList = (itr->second)->rList;
//        result.ver[itr->first] = _new;
//    }
//    return result;
//}

//template<class V,  class E>
//std::list<std::pair<int, E> > graph<V, E>::getInEdges(int v)
//{
//    vertex_iterator itr = ver.find(v);
//    if (itr == ver.end())
//        throw "Vertex doesn't exist";
//    std::list<std::pair<int, E> > edges;
//    std::vector<int> del;
//    edge_iterator ed_itr = ((itr->second)->tList).begin(), ed_end = ((itr->second)->tList).end(); // itr->second - указатель на вершину v
//    for (;ed_itr != ed_end; ed_itr++){
//        if (((ed_itr->second).first).expired()){ //ed_itr->second)->first - указатель на вершину, с которой текущая имеет ребро
//            del.push_back(ed_itr->first); //проверка валидности weak_ptr и, при необходимости, удаление лишней вершины
//        }else edges.push_back(std::make_pair(ed_itr->first, (ed_itr->second).second)); //ed_itr->first - номер вершины, (itr->second)->second - вес ребра
//    }
//    for(auto i = del.begin(); i != del.end(); i++)
//        (itr->second)->tList.erase(*i);
//    return edges;
//}

//template<class V,  class E>
//std::list<std::pair<int, E> > graph<V, E>::getOutEdges(int v)
//{
//    vertex_iterator itr = ver.find(v);
//    if (itr == ver.end())
//        throw "Vertex doesn't exist";
//    std::list<std::pair<int, E> > edges;
//    std::vector<int> del;
//    edge_iterator ed_itr = ((itr->second)->rList).begin(), ed_end = ((itr->second)->rList).end(); //itr->second - указатель на вершину v
//    for (;ed_itr != ed_end; ed_itr++){
//        if ((ed_itr->second).first.expired()){ //itr->second)->first - указатель на вершину, с которой текущая имеет ребро
//            del.push_back(ed_itr->first);//проверка валидности weak_ptr и, при необходимости, удаление лишней вершины
//        }else edges.push_back(std::make_pair(ed_itr->first, (ed_itr->second).second));
//    }
//    for(auto i = del.begin(); i != del.end(); i++)
//        (itr->second)->rList.erase(*i);
//    return edges;
//}

//template<class V,  class E>
//std::list<std::pair<int, V> > graph<V, E>::getAccessVertexes(int v)
//{
//    vertex_iterator itr = ver.find(v);
//    if (itr == ver.end())
//        throw "Vertex doesn't exist";
//    std::list<std::pair<int, E> > vertexes;
//    std::vector<int> del;
//    edge_iterator ed_itr = ((itr->second)->rList).begin(), ed_end = ((itr->second)->rList).end(); //itr->second - указатель на вершину v
//    for (;ed_itr != ed_end; ed_itr++){
//        if ((ed_itr->second).first.expired()){ //itr->second)->first - указатель на вершину, с которой текущая имеет ребро
//            del.push_back(ed_itr->first); //проверка валидности weak_ptr и, при необходимости, удаление лишней вершины;
//        }else{
//            std::shared_ptr<vertex<V, E> > ver_point = ((ed_itr->second).first).lock(); //указатель на вершину, связанную с v выходящим из в ребром
//            vertexes.push_back(std::make_pair(ed_itr->first, ver_point->value)); //ed_itr->first - n вершины,
//        }
//    }
//    for(auto i = del.begin(); i != del.end(); i++)
//        (itr->second)->rList.erase(*i);
//    return vertexes;
//}

//template<class V,  class E>
//std::list<std::pair<int, V> > graph<V, E>::getPreviousVertexes(int v)
//{
//    vertex_iterator itr = ver.find(v);
//    if (itr == ver.end())
//        throw "Vertex doesn't exist";
//    std::list<std::pair<int, E> > vertexes;
//    std::vector<int> del;
//    edge_iterator ed_itr = ((itr->second)->tList).begin(), ed_end = ((itr->second)->tList).end();
//    for (;ed_itr != ed_end; ed_itr++){
//        if ((ed_itr->second).first.expired()){ //itr->second)->first - указатель на вершину, с которой текущая имеет ребро
//            del.push_back(ed_itr->first); //проверка валидности weak_ptr и, при необходимости, удаление лишней вершины
//        }else{
//            std::shared_ptr<vertex<V, E> > ver_point = ((ed_itr->second).first).lock(); // указатель на вершину, из которой можно прийти в v
//            vertexes.push_back(std::make_pair(ed_itr->first, ver_point->value));
//        }
//    }
//    for(auto i = del.begin(); i != del.end(); i++)
//        (itr->second)->tList.erase(*i);
//    return vertexes;
//}

//template<class V,  class E>
//void graph<V, E>::insertVertex(int v, V _value)
//{
//    if (ver.find(v) != ver.end())
//        throw "Vertex has already existed";
//    std::shared_ptr<vertex<V, E> > new_ver(new vertex<V, E>(_value));
//    ver[v] = new_ver;
//}

//template<class V,  class E>
//void graph<V, E>::eraseVertex(int v)
//{
//    if (ver.find(v) == ver.end())
//        throw "Vertex doesn't' exist";
//    ver.erase(v);
//}

//template<class V,  class E>
//void graph<V, E>::insertEdge(int v1, int v2, E _value)
//{
//    vertex_iterator itr1, itr2;
//    if (((itr1 = ver.find(v1)) == ver.end())
//            || ((itr2 = ver.find(v2)) == ver.end()))
//        throw "Vertex doesn't' exist";
//    if ((((itr1->second)->rList.find(v2)) != (itr1->second)->rList.end()) && !((((itr1->second)->rList.find(v2))->second.first).expired()))
//        // itr1->second - shared_ptr на вершину;
//        throw "Edge has already existed";
//    (itr1->second)->rList[v2] = std::make_pair(static_cast<std::weak_ptr<vertex<V, E> > >(itr2->second), _value);
//    (itr2->second)->tList[v1] = std::make_pair(static_cast<std::weak_ptr<vertex<V, E> > >(itr1->second), _value);
//}

//template<class V,  class E>
//void graph<V, E>::eraseEdge(int v1, int v2)
//{
//    vertex_iterator itr1, itr2;
//    if (((itr1 = ver.find(v1)) == ver.end())
//            || ((itr2 = ver.find(v2)) == ver.end()))
//        throw "Vertex doesn't' exist";
//    if (((itr1->second)->rList.find(v2)) == (itr1->second)->rList.end() ||
//            (((itr1->second)->rList.find(v2))->second).first.expired())
//        throw "Edge doesn't exist";
//    (itr1->second)->rList.erase(v2);
//    (itr2->second)->tList.erase(v1);
//}

//template<class V,  class E>
//std::istream& operator >> (std::istream &cin, graph<V, E>  &_graph)
//{
//    _graph.ver.clear();
//    unsigned int n;
//    cin >> n; //количество вершин
//    for (unsigned int i = 0; i < n; i++){
//        V _data;
//        int num;
//        cin >> num;
//        cin >> _data;
//        try{
//            _graph.insertVertex(num, _data);
//        }
//        catch (char const *s){
//            std::cerr << num << ": " << s << std::endl;
//        }
//    }
//    for (unsigned int i = 0; i < _graph.ver.size(); i++){
//        int out; // из какой вершины выходят ребра
//        unsigned int m;
//        cin >> out;
//        cin >> m;
//        for (unsigned int j = 0; j < m; j++){
//            E _data;
//            int in;
//            cin >> in >> _data;
//            try{
//                _graph.insertEdge(out, in, _data);
//            }
//            catch (char const *s){
//                std::cerr << out << " " << in << ": " << s << std::endl;
//            }
//        }
//    }
//    return cin;
//}

//template<class V,  class E>
//std::ostream& operator << (std::ostream &cout, graph<V, E> &_graph)
//{
//    cout << _graph.ver.size() << std::endl; //количество вершин
//    typename graph<V, E>::vertex_iterator itr = _graph.ver.begin(), end = _graph.ver.end();
//    for (; itr != end; itr++)
//        cout << itr->first << ' ' << ((itr->second)->get()) << std::endl; //itr->first - номер вершины,
//    for (itr = _graph.ver.begin(); itr != end; itr++){
//        std::list<std::pair<int, E> > l = _graph.getOutEdges(itr->first);
//        auto e_itr = l.begin(), e_end = l.end();
//        cout << std::endl << itr->first << ' ' << l.size() << std::endl; //выводим номер вершины и кол-во связвнных
//        for (;e_itr != e_end; e_itr++)
//            cout << e_itr->first << ' ' << e_itr->second << ' '; // вывод номера вершины и веса ребра
//    }
//    return cout;
//}

//////template<class TypeV,  class TypeE>
//////typename graph<TypeV, TypeE>::iterator_dfs graph<TypeV, TypeE>::begin_dfs()
//////{
//////    iterator_dfs itr(this);
//////    ++itr;
//////    return itr;
//////}

//////template<class TypeV,  class TypeE>
//////typename graph<TypeV, TypeE>::iterator_dfs graph<TypeV, TypeE>::end_dfs()
//////{
//////    iterator_dfs itr(this);
//////    itr.elem = ver.end();
//////    return itr;
//////}

//////template<class DataV,  class DataE>
//////typename graph<DataV, DataE>::iterator_bfs graph<DataV, DataE>::begin(int)
//////{
//////    iterator_bfs itr(this);
//////    ++itr;
//////    return itr;
//////}

//////template<class DataV,  class DataE>
//////typename graph<DataV, DataE>::iterator_bfs graph<DataV, DataE>::end(int)
//////{
//////    iterator_bfs itr(this);
//////    itr.elem = Inf.end();
//////    return itr;
//////}
