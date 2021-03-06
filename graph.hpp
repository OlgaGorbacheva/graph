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
    _G.swap(*this);
}

template<class I, class V, class E>
my::graph<I, V, E>::~graph()
{ }

template<class I, class V, class E>
void my::graph<I, V, E>::swap(graph<I, V, E> &_G) noexcept
{
    std::swap(edges, _G.edges);
    std::swap(vertexes, _G.vertexes);
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
    _G.swap(*this);
}


template<class I, class V, class E>
typename my::graph<I, V, E>::direct_vertex_iterator
            my::graph<I, V, E>::insertVertex(I const &_id, V const &_value)
{
    if (vertexes.find(_id) != vertexes.end())
        throw "Vertex has already existed";
    return vertexes.insert(std::make_pair(_id, static_cast<std::shared_ptr<vertex> > (new vertex(_id, _value)))).first;
}

template<class I, class V, class E>
void my::graph<I, V, E>::eraseVertex(I const &_id)
{
    direct_vertex_iterator itr;
    if ((itr = vertexes.find(_id)) == vertexes.end())
        throw "Vertex doesn't exist";
    for (auto ver_itr = itr->second->rList.begin(), end = itr->second->rList.end();
         ver_itr != end; ver_itr++) {
        if (!(ver_itr->second.expired()))
            edges.erase(std::make_pair(_id, ver_itr->first));
    }
    for (auto ver_itr = itr->second->tList.begin(), end = itr->second->tList.end();
         ver_itr != end; ver_itr++) {
        if (!(ver_itr->second.expired()))
            edges.erase(std::make_pair( ver_itr->first, _id));
    }
    vertexes.erase(itr);
}

template<class I, class V, class E>
void my::graph<I, V, E>::eraseVertex(direct_vertex_iterator const _itr)
{
    for (auto ver_itr = _itr->second->rList.begin(), end = _itr->second->rList.end();
         ver_itr != end; ver_itr++) {
        if (!(ver_itr->second.expired()))
            edges.erase(std::make_pair(_itr->second->id, ver_itr->first));
    }
    for (auto ver_itr = _itr->second->tList.begin(), end = _itr->second->tList.end();
          ver_itr != end; ver_itr++) {
         if (!(ver_itr->second.expired()))
             edges.erase(std::make_pair(ver_itr->first, _itr->second->id));
    }
    vertexes.erase(_itr);
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
my::graph<I, V, E> my::graph<I, V, E>::transpose() const
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
std::vector<std::pair<I, E> > my::graph<I, V, E>::getOutEdges(I const &id) const
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
std::vector<std::pair<I, E> > my::graph<I, V, E>::getInEdges(I const &id) const
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
std::vector<std::pair<I, V> > my::graph<I, V, E>::getAccessVertexes(I const &id) const
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
                else toErase.push_back(itr);
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
std::vector<std::pair<I, V> > my::graph<I, V, E>::getPreviousVertexes(I const &id) const
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
                else toErase.push_back(itr);
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
std::vector<std::pair<I, V> > my::graph<I, V, E>::getVertexes() const
{
    direct_vertex_iterator itr = vertexes.begin(), end = vertexes.end();
    std::vector<std::pair<I, V> > result;
    for (;itr != end; itr++){
        result.push_back(std::make_pair(itr->first, itr->second->value));
    }
    return result;
}

template<class I, class V, class E>
std::vector<std::pair<std::pair<I, I>, E>> my::graph<I, V, E>::getEdges() const
{
    direct_edge_iterator itr = edges.begin(), end = edges.end();
    std::vector<std::pair<std::pair<I, I>, E>> result;
    for (;itr != end; itr++){
        result.push_back(std::make_pair(itr->first, itr->second->value));
    }
    return result;
}

template<class I, class V, class E>
bool my::graph<I, V, E>::getEdge(I &out, I &in, std::pair<I, E> &edge) const
{
    direct_edge_iterator itr;
    if ((itr = edges.find(std::make_pair(out, in))) == edges.end())
        return false;
    else {
        edge = std::make_pair(itr->first.second, itr->second);
        return true;
    }
}

template<class I, class V, class E>
void my::graph<I, V, E>::clear()
{
    vertexes.clear();
    edges.clear();
}

template<class I, class V, class E>
void my::graph<I, V, E>::merge(my::graph<I, V, E> &G)
{
    for(direct_vertex_iterator v_itr = G.ver_begin(), v_end = G.ver_end(); v_itr != v_end; v_itr++){
        if (vertexes.find(v_itr->first) != vertexes.end())
            throw "Vertex has already exist";
        vertexes.insert(*v_itr);
    }
    for(direct_edge_iterator e_itr = G.ed_begin(), e_end = G.ed_end(); e_itr != e_end; e_itr++){
        edges.insert(*e_itr);
    }
    G.clear();
}

template<class I, class V, class E>
bool my::graph<I, V, E>::empty() const
{
    return vertexes.empty();
}

template<class I, class V, class E>
std::istream& my::operator >> (std::istream &cin, my::graph<I, V, E> &_graph)
{
    _graph.clear();
    unsigned int vertexNum;
    cin >> vertexNum;
    for (unsigned int i = 0; i < vertexNum; i++){
        I id;
        V value;
        cin >> id >> value;
        try{
            _graph.insertVertex(id, value);
        }
        catch(char const * s){
            std::cerr << s << std::endl;
        }
    }
    for (unsigned int i = 0; i < _graph.vertexes.size(); i++){
        unsigned int edgesNum;
        I id1;
        cin >> id1 >> edgesNum;
        for (unsigned int j = 0; j < edgesNum; j++){
            E value;
            I id2;
            cin >> id2 >> value;
            try{
                _graph.insertEdge(id1, id2, value);
            }
            catch(char const * s){
                std::cerr << s << std::endl;
            }
        }
    }
    return cin;
}

template<class I, class V, class E>
std::ostream& my::operator <<(std::ostream &cout, my::graph<I, V, E> const &_graph)
{
    std::vector<std::pair<I, V> > vertexes = _graph.getVertexes();
    cout << vertexes.size() << std::endl;
    auto v_itr = vertexes.begin(), v_end = vertexes.end();
    for (; v_itr != v_end; v_itr++)
        cout << v_itr->first << ' ' << v_itr->second << std::endl;
    cout << std::endl;
    for (v_itr = vertexes.begin(); v_itr != v_end; v_itr++){
        std::vector<std::pair<I, E> > edges = _graph.getOutEdges(v_itr->first);
        cout << v_itr->first << ' ' << edges.size() << std::endl;
        auto e_itr = edges.begin(), e_end = edges.end();
        for (; e_itr != e_end; e_itr++)
            cout << e_itr->first << ' ' << e_itr->second << ' ';
        if (edges.size() != 0)
            cout << std::endl;
    }
    return cout;
}

template<class I, class V, class E>
int my::graph<I, V, E>::getVertexesNumber() const
{
    return vertexes.size();
}

template<class I, class V, class E>
V const & my::graph<I, V, E>::operator [](I const & id) const
{
    try {
        return vertexes.at(id)->value;
    }
    catch(std::out_of_range) {
        throw "Vertex doesn't exist";
    }
}

template<class I, class V, class E>
V & my::graph<I, V, E>::operator [](I const & id)
{
    try {
        return vertexes.at(id)->value;
    }
    catch(std::out_of_range) {
        throw "Vertex doesn't exist";
    }
}

template<class I, class V, class E>
typename my::graph<I, V, E>::direct_vertex_iterator my::graph<I, V, E>::ver_begin() const
{
    return vertexes.begin();
}

template<class I, class V, class E>
typename my::graph<I, V, E>::direct_vertex_iterator my::graph<I, V, E>::ver_end() const
{
    return vertexes.end();
}

template<class I, class V, class E>
typename my::graph<I, V, E>::direct_edge_iterator my::graph<I, V, E>::ed_begin() const
{
    return edges.begin();
}

template<class I, class V, class E>
typename my::graph<I, V, E>::direct_edge_iterator my::graph<I, V, E>:: ed_end() const
{
    return edges.end();
}

template<class I, class V, class E>
typename my::graph<I, V, E>::iterator_dfs my::graph<I, V, E>::begin_dfs() const
{
    iterator_dfs itr(*this);
    ++itr;
    return itr;
}

template<class I, class V, class E>
typename my::graph<I, V, E>::iterator_dfs my::graph<I, V, E>::end_dfs() const
{
    iterator_dfs itr(*this);
    itr.elem = vertexes.end();
    return itr;
}

template<class I, class V, class E>
typename my::graph<I, V, E>::iterator_bfs my::graph<I, V, E>::begin_bfs() const
{
    iterator_bfs itr(*this);
    ++itr;
    return itr;
}

template<class I, class V, class E>
typename my::graph<I, V, E>::iterator_bfs my::graph<I, V, E>::end_bfs() const
{
    iterator_bfs itr(*this);
    itr.elem = vertexes.end();
    return itr;
}

template<class I, class V, class E>
typename my::graph<I, V, E>::iterator_dfs my::graph<I, V, E>::begin_dfs(I _id) const
{
    direct_vertex_iterator _elem;
    if ((_elem = vertexes.find(_id)) == vertexes.end())
        throw "Vertex doesn't exist";
    iterator_dfs itr(*this);
    itr.color[_id] = 1;
    itr.passed.push(_id);
    itr.elem = _elem;
    return itr;
}

template<class I, class V, class E>
typename my::graph<I, V, E>::iterator_bfs my::graph<I, V, E>::begin_bfs(I _id) const
{
    direct_vertex_iterator _elem;
    if ((_elem = vertexes.find(_id)) == vertexes.end())
        throw "Vertex doesn't exist";
    iterator_dfs itr(*this);
    itr.color[_id] = 1;
    itr.passed.push(_id);
    itr.elem = _elem;
    return itr;
}
