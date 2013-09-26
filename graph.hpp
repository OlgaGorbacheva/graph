#include "graph.h"


template<class I, class V, class E>
my::graph<I, V, E>::graph()
{ }

template<class I, class V, class E>
my::graph<I, V, E>::graph(graph<I, V, E> const &_G)
{
    for (direct_vertex_iterator itr = _G.vertexes.begin(), end = _G.vertexes.end(); itr != end; itr++){
        this->insertVertex(itr->second->id, itr->second->value);
    }
    for (direct_edge_iterator itr = _G.edges.begin(), end = _G.edges.end(); itr != end; itr++){
        this->insertEdge(itr->first.first, itr->first.second, itr->second->value);
    }
}

template<class I, class V, class E>
my::graph<I, V, E>::graph(graph<I, V, E> &&_G) noexcept
{
    vertexes = std::move(_G.vertexes);
    edges = std::move(_G.edges);
}

template<class I, class V, class E>
my::graph<I, V, E>::~graph()
{ }

template<class I, class V, class E>
void my::graph<I, V, E>::swap(graph<I, V, E> &_G) noexcept
{
    graph<I, V, E> tmp(*this);
    this->vertexes.clear();
    this->edges.clear();
    for (direct_vertex_iterator itr = _G.vertexes.begin(), end = _G.vertexes.end(); itr != end; itr++){
        this->insertVertex(itr->second->id, itr->second->value);
    }
    for (direct_edge_iterator itr = _G.edges.begin(), end = _G.edges.end(); itr != end; itr++){
        this->insertEdge(itr->first.first, itr->first.second, itr->second->value);
    }
    _G.vertexes.clear();
    _G.edges.clear();
    for (direct_vertex_iterator itr = tmp.vertexes.begin(), end = tmp.vertexes.end(); itr != end; itr++){
        _G.insertVertex(itr->second->id, itr->second->value);
    }
    for (direct_edge_iterator itr = tmp.edges.begin(), end = tmp.edges.end(); itr != end; itr++){
        _G.insertEdge(itr->first.first, itr->first.second, itr->second->value);
    }
}

template<class I, class V, class E>
void my::graph<I, V, E>::operator =(my::graph<I, V, E> const &_G)
{
    graph<I, V, E> tmp(_G);
    this->swap(tmp);
}

template<class I, class V, class E>
void my::graph<I, V, E>::operator =(my::graph<I, V, E> &&_G)
{
    vertexes = std::move(_G.vertexes);
    edges = std::move(_G.edges);
}

template<class I, class V, class E>
typename my::graph<I, V, E>::direct_vertex_iterator
            my::graph<I, V, E>::insertVertex(I const &_id, V const &_value)
{
    if (vertexes.find(_id) != vertexes.end())
        throw "Vertex has already existed";
    return vertexes.insert(std::make_pair(_id,
            static_cast<std::shared_ptr<vertex> > (new vertex(_id, _value)))).first;
}

template<class I, class V, class E>
void my::graph<I, V, E>::eraseVertex(I const &_id)
{
    direct_vertex_iterator itr;
    if ((itr = vertexes.find(_id)) == vertexes.end())
        throw "Vertex doesn't exist";
    vertexes.erase(itr);
}

template<class I, class V, class E>
void my::graph<I, V, E>::eraseVertex(direct_vertex_iterator const _itr)
{
    vertexes.erase(_itr); //может ли erase выкинуть исключение?
}

template<class I, class V, class E>
typename my::graph<I, V, E>::direct_edge_iterator
        my::graph<I, V, E>::insertEdge(I const &id_1, I const &id_2, E const &_value)
{
    direct_vertex_iterator itr1, itr2;
    if ((itr1 = vertexes.find(id_1)) == vertexes.end())
        throw "Vertex doesn't exist";
    if ((itr2 = vertexes.find(id_2)) == vertexes.end())
        throw "Vertex doesn't exist";
    if (edges.find(std::make_pair(id_1, id_2)) != edges.end())
        throw "Edge has already exist";
    std::shared_ptr<edge> e(new edge(static_cast<std::weak_ptr<vertex> >(itr1->second),
           static_cast<std::weak_ptr<vertex> >(itr2->second), _value));
    itr1->second->rList.insert(std::make_pair(id_2, static_cast<std::weak_ptr<edge> >(e)));
    itr2->second->tList.insert(std::make_pair(id_1, static_cast<std::weak_ptr<edge> >(e)));
    return edges.insert(std::make_pair(std::make_pair(id_1, id_2), e)).first;
}

template<class I, class V, class E>
void my::graph<I, V, E>::eraseEdge(I const &id_1, I const &id_2)
{
    direct_edge_iterator itr;
    if ((itr = edges.find(std::make_pair(id_1, id_2))) == edges.end())
        throw "Edge doesn't exist";
    edges.erase(itr);
}

template<class I, class V, class E>
void my::graph<I, V, E>::eraseEdge(direct_edge_iterator const itr)
{
    edges.erase(itr);
}

template<class I, class V, class E>
my::graph<I, V, E> my::graph<I, V, E>::transpose()
{
    graph<I, V, E> result;
    for (direct_vertex_iterator itr = vertexes.begin(), end = vertexes.end(); itr != end; itr++){
        result.insertVertex(itr->second->id, itr->second->value);
    }
    for (direct_edge_iterator itr = edges.begin(), end = edges.end(); itr != end; itr++){
        result.insertEdge(itr->first.second, itr->first.first, itr->second->value);
    }
    return result;
}

template<class I, class V, class E>
std::vector<std::pair<I, E> > my::graph<I, V, E>::getOutEdges(I const &id)
{
    try{
        std::vector<typename std::unordered_map<I, std::weak_ptr<my::graph<I, V, E>::edge> >::iterator> toErase;
        std::vector<std::pair<I, E> > result;
        auto itr = vertexes.at(id)->rList.begin(), end = vertexes.at(id)->rList.end();
        for (;itr != end; itr++) //пройдем по прямому списку связности
            if (itr->second.expired())
                toErase.push_back(itr);
            else result.push_back(std::make_pair(itr->first, itr->second.lock()->value));
        auto er_itr = toErase.begin(), er_end = toErase.end();
        for (;er_itr != er_end; er_itr++)
            vertexes.at(id)->rList.erase(*er_itr);
        return result;

    }
    catch(std::out_of_range){
        throw "Vertex doesn't exist";
    }
}

template<class I, class V, class E>
std::vector<std::pair<I, E> > my::graph<I, V, E>::getInEdges(I const &id)
{
    try{
        std::vector<typename std::unordered_map<I, std::weak_ptr<my::graph<I, V, E>::edge> >::iterator> toErase;
        std::vector<std::pair<I, E> > result;
        auto itr = vertexes.at(id)->tList.begin(), end = vertexes.at(id)->tList.end();
        for (;itr != end; itr++) //пройдем по обратному списку связности
            if (itr->second.expired())
                toErase.push_back(itr);
            else result.push_back(std::make_pair(itr->first, itr->second.lock()->value));
        auto er_itr = toErase.begin(), er_end = toErase.end();
        for (;er_itr != er_end; er_itr++)
            vertexes.at(id)->rList.erase(*er_itr);
        return result;

    }
    catch(std::out_of_range){
        throw "Vertex doesn't exist";
    }
}

template<class I, class V, class E>
std::vector<std::pair<I, V> > my::graph<I, V, E>::getAccessVertexes(I const &id)
{
    try{
        std::vector<typename std::unordered_map<I, std::weak_ptr<my::graph<I, V, E>::edge> >::iterator> toErase;
        std::vector<std::pair<I, V> > result;
        auto itr = vertexes.at(id)->rList.begin(), end = vertexes.at(id)->rList.end();
        for (;itr != end; itr++) //пройдем по прямому списку связности
            if (itr->second.expired())
                toErase.push_back(itr);
            else
                if (!itr->second.lock()->vertexes.second.expired())
                    result.push_back(std::make_pair(itr->first, (itr->second.lock()->vertexes.second).lock()->value));
        auto er_itr = toErase.begin(), er_end = toErase.end();
        for (;er_itr != er_end; er_itr++){
            try{
                vertexes.at(id)->rList.erase(*er_itr);
            }
            catch(std::out_of_range){
            }
        }
        return result;

    }
    catch(std::out_of_range){
        throw "Vertex doesn't exist";
    }
}

template<class I, class V, class E>
std::vector<std::pair<I, V> > my::graph<I, V, E>::getPreviousVertexes(I const &id)
{
    try{
        std::vector<typename std::unordered_map<I, std::weak_ptr<my::graph<I, V, E>::edge> >::iterator> toErase;
        std::vector<std::pair<I, V> > result;
        auto itr = vertexes.at(id)->tList.begin(), end = vertexes.at(id)->tList.end();
        for (;itr != end; itr++) //пройдем по прямому списку связности
            if (itr->second.expired())
                toErase.push_back(itr);
            else
                if (!itr->second.lock()->vertexes.first.expired())
                    result.push_back(std::make_pair(itr->first, (itr->second.lock()->vertexes.first).lock()->value));
        auto er_itr = toErase.begin(), er_end = toErase.end();
        for (;er_itr != er_end; er_itr++){
            try{
                vertexes.at(id)->rList.erase(*er_itr);
            }
            catch(std::out_of_range){
            }
        }
        return result;

    }
    catch(std::out_of_range){
        throw "Vertex doesn't exist";
    }
}

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
