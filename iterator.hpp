#include "graph.h"

template<class I, class V, class E>
void my::graph<I, V, E>::iterator_dfs::swap (iterator_dfs &_itr) noexcept
{
    iterator_dfs tmp(_itr);
    _itr.color = color;
    _itr.G = G;
    _itr.elem = elem;
    _itr.passed = passed;
    color = tmp.color;
    G = tmp.G;
    elem = tmp.elem;
    passed = tmp.passed;
}

template<class I, class V, class E>
my::graph<I, V, E>::iterator_dfs::iterator_dfs(graph<I, V, E> &_G):G(_G)
{
    direct_vertex_iterator itr = G.ver_begin(), end =G.ver_end();
    for (;itr != end; itr++){
        color[itr->first] = 0;
    }
}

template<class I, class V, class E>
my::graph<I, V, E>::iterator_dfs::iterator_dfs(iterator_dfs const &_itr):color(_itr.color), passed(_itr.passed),
                                                                            elem(_itr.elem), G(_itr.G)
{ }

template<class I, class V, class E>
my::graph<I, V, E>::iterator_dfs::iterator_dfs(iterator_dfs &&_itr)noexcept: G(_itr.G)
{
    color = std::move(_itr.color);
    passed = std::move(_itr.passed);
    elem = std::move(_itr.elem);
}

template<class I, class V, class E>
void my::graph<I, V, E>::iterator_dfs::operator =(iterator_dfs const &_itr)
{
    iterator_dfs tmp(_itr);
    this->swap(tmp);
}

template<class I, class V, class E>
void my::graph<I, V, E>::iterator_dfs::operator =(iterator_dfs &&_itr)
{
    color = std::move(_itr.color); // можно так делать или нет? не будет ли подтекать память в этом месте?
    passed = std::move(_itr.passed);
    elem = std::move(_itr.elem);
}

template<class I, class V, class E>
typename my::graph<I, V, E>::vertex & my::graph<I, V, E>::iterator_dfs::operator *()
{
    return *(elem->second);
}

template<class I, class V, class E>
typename my::graph<I, V, E>::vertex & my::graph<I, V, E>::iterator_dfs::operator ->()
{
    return *(elem->second);
}

template<class I, class V, class E>
typename my::graph<I, V, E>::iterator_dfs & my::graph<I, V, E>::iterator_dfs::operator ++()
{
    if (passed.empty()){
        auto itr = color.begin(), end = color.end();
        for (;itr != end; itr++){
            if (itr->second == 0){
                passed.push(itr->first);
                itr->second = 1;
                elem = G.vertexes.find(itr->first);
                return *this;
            }
        }
        elem = G.vertexes.end();
        return *this; //граф закончился
    }

    while(true){
        std::vector<std::pair<I, V> > ver = G.getAccessVertexes(passed.top());
        for (auto itr = ver.begin(), end = ver.end(); itr != end; itr++){
            if (color[itr->first] == 0){
                passed.push(itr->first);
                color[itr->first] = 1;
                elem = G.vertexes.find(itr->first);
                return *this;
            }
        }
        elem = G.vertexes.find(passed.top());
        color[passed.top()] = 2;
        passed.pop();
        return *this;
    }
}

template<class I, class V, class E>
typename my::graph<I, V, E>::iterator_dfs my::graph<I, V, E>::iterator_dfs::operator ++(int)
{
    iterator_dfs i(*this);
    if (passed.empty()){
        auto itr = color.begin(), end = color.end();
        for (;itr != end; itr++){
            if (itr->second == 0){
                passed.push(itr->first);
                itr->second = 1;
                elem = G.vertexes.find(itr->first);
                return i;
            }
        }
        elem = G.vertexes.end();
        return i; //граф закончился
    }

    while(true){
        std::vector<std::pair<I, V> > ver = G.getAccessVertexes(passed.top());
        for (auto itr = ver.begin(), end = ver.end(); itr != end; itr++){
            if (color[itr->first] == 0){
                passed.push(itr->first);
                color[itr->first] = 1;
                elem = G.vertexes.find(itr->first);
                return i;
            }
        }
        elem = G.vertexes.find(passed.top());
        color[passed.top()] = 2;
        passed.pop();
        return i;
    }
}

template<class I, class V, class E>
bool my::graph<I, V, E>::iterator_dfs::operator !=(iterator_dfs _itr)
{
    return elem != _itr.elem;
}

template<class I, class V, class E>
bool my::graph<I, V, E>::iterator_dfs::operator ==(iterator_dfs _itr)
{
    return elem == _itr.elem;
}

template<class I, class V, class E>
int my::graph<I, V, E>::iterator_dfs::getColor()
{
    return color[elem->first];
}

/////////////////////////////////////////////////////////////////

template<class I, class V, class E>
void my::graph<I, V, E>::iterator_bfs::swap (iterator_bfs &_itr) noexcept
{
    iterator_bfs tmp(_itr);
    _itr.color = color;
    _itr.G = G;
    _itr.elem = elem;
    _itr.passed = passed;
    color = tmp.color;
    G = tmp.G;
    elem = tmp.elem;
    passed = tmp.passed;
}

template<class I, class V, class E>
my::graph<I, V, E>::iterator_bfs::iterator_bfs(graph<I, V, E> &_G):G(_G)
{
    direct_vertex_iterator itr = G.ver_begin(), end = G.ver_end();
    for (;itr != end; itr++){
        color[itr->first] = 0;
    }
}

template<class I, class V, class E>
my::graph<I, V, E>::iterator_bfs::iterator_bfs(iterator_bfs const &_itr):color(_itr.color), passed(_itr.passed),
                                                                            elem(_itr.elem), G(_itr.G)
{ }

template<class I, class V, class E>
my::graph<I, V, E>::iterator_bfs::iterator_bfs(iterator_bfs &&_itr)noexcept: G(_itr.G)
{
    color = std::move(_itr.color);
    passed = std::move(_itr.passed);
    elem = std::move(_itr.elem);
}

template<class I, class V, class E>
void my::graph<I, V, E>::iterator_bfs::operator =(iterator_bfs const &_itr)
{
    iterator_bfs tmp(_itr);
    this->swap(tmp);
}

template<class I, class V, class E>
void my::graph<I, V, E>::iterator_bfs::operator =(iterator_bfs &&_itr)
{
    color = std::move(_itr.color); // можно так делать или нет? не будет ли подтекать память в этом месте?
    passed = std::move(_itr.passed);
    elem = std::move(_itr.elem);
}

template<class I, class V, class E>
typename my::graph<I, V, E>::vertex & my::graph<I, V, E>::iterator_bfs::operator *()
{
    return *(elem->second);
}

template<class I, class V, class E>
typename my::graph<I, V, E>::vertex & my::graph<I, V, E>::iterator_bfs::operator ->()
{
    return *(elem->second);
}

template<class I, class V, class E>
typename my::graph<I, V, E>::iterator_bfs & my::graph<I, V, E>::iterator_bfs::operator ++()
{
    if (passed.empty()){
        auto itr = color.begin(), end = color.end();
        for (;itr != end; itr++){
            if (itr->second == 0){
                passed.push(itr->first);
                itr->second = 1;
                elem = G.vertexes.find(itr->first);
                return *this;
            }
        }
        elem = G.vertexes.end();
        return *this; //граф закончился
    }

    while(true){
        std::vector<std::pair<I, V> > ver = G.getAccessVertexes(passed.front());
        for (auto itr = ver.begin(), end = ver.end(); itr != end; itr++){
            if (color[itr->first] == 0){
                passed.push(itr->first);
                color[itr->first] = 1;
                elem = G.vertexes.find(itr->first);
                return *this;
            }
        }
        elem = G.vertexes.find(passed.front());
        color[passed.front()] = 2;
        passed.pop();
        return *this;
    }
}

template<class I, class V, class E>
typename my::graph<I, V, E>::iterator_bfs my::graph<I, V, E>::iterator_bfs::operator ++(int)
{
    iterator_bfs i(*this);
    if (passed.empty()){
        auto itr = color.begin(), end = color.end();
        for (;itr != end; itr++){
            if (itr->second == 0){
                passed.push(itr->first);
                itr->second = 1;
                elem = G.vertexes.find(itr->first);
                return i;
            }
        }
        elem = G.vertexes.end();
        return i; //граф закончился
    }

    while(true){
        std::vector<std::pair<I, V> > ver = G.getAccessVertexes(passed.front());
        for (auto itr = ver.begin(), end = ver.end(); itr != end; itr++){
            if (color[itr->first] == 0){
                passed.push(itr->first);
                color[itr->first] = 1;
                elem = G.vertexes.find(itr->first);
                return i;
            }
        }
        elem = G.vertexes.find(passed.front());
        color[passed.front()] = 2;
        passed.pop();
        return i;
    }
}

template<class I, class V, class E>
bool my::graph<I, V, E>::iterator_bfs::operator !=(iterator_bfs _itr)
{
    return elem != _itr.elem;
}

template<class I, class V, class E>
bool my::graph<I, V, E>::iterator_bfs::operator ==(iterator_bfs _itr)
{
    return elem == _itr.elem;
}


template<class I, class V, class E>
int my::graph<I, V, E>::iterator_bfs::getColor()
{
    return color[elem->first];
}
