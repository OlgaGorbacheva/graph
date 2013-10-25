#include "graph_algorithm.h"

template<class I, class V, class E>
my::graph<I, V, E> Kruskal(my::graph<I, V, E> &G)
{
    std::vector<std::pair<std::pair<I, I>, E>> edges = G.getEdges();
    std::vector<std::pair<I, V>> vertexes = G.getVertexes();
    my::sets ver_set;
    my::graph<I, V, E> tree;
    for (auto itr = vertexes.begin(), end = vertexes.end(); itr != end; itr++) {
        ver_set.make(itr->first);
    }
    std::sort(edges.begin(), edges.end(), [](std::pair<std::pair<I, I>, E> a, std::pair<std::pair<I, I>, E> b){
        return a.second < b.second;
    });
}
