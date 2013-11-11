#include "graph_algorithm.h"
#include "sets.h"

template<class I, class V, class E>
my::graph<I, V, E> Kruskal(my::graph<I, V, E> &G)
{
    std::vector<std::pair<std::pair<I, I>, E>> edges = G.getEdges();
    std::vector<std::pair<I, V>> vertexes = G.getVertexes();
    my::set_system<I> ver_set;
    my::graph<I, V, E> tree;
    for (auto itr = vertexes.begin(), end = vertexes.end(); itr != end; itr++) {
        ver_set.make(itr->first);
        tree.insertVertex(itr->first, itr->second);
    }
    std::sort(edges.begin(), edges.end(), [](std::pair<std::pair<I, I>, E> a, std::pair<std::pair<I, I>, E> b){
        return a.second < b.second;
    });
    for (auto itr = edges.begin(), end = edges.end(); itr != end; itr++){
        if (ver_set.find(itr->first.first) != ver_set.find(itr->first.second)) {
            ver_set.merge(itr->first.first, itr->first.second);
            tree.insertEdge(itr->first.first, itr->first.second, itr->second);
            tree.insertEdge(itr->first.second, itr->first.first, itr->second);
        }
    }
    return tree;
}
