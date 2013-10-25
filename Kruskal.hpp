#include "graph_algorithm.h"

template<class I, class V, class E>
my::graph<I, V, E> Kruskal(my::graph<I, V, E> &G)
{
    std::vector<std::pair<std::pair<I, I>, E>> edges = G.getEdges();
    std::vector<std::pair<I, V>> vertexes = G.getVertexes();
    std::vector<my::graph<I, V, E>> sets;
    my::graph<I, V, E> tree;
    for (int i = 0; i < vertexes.size(); i++) {
        my::graph F();
        F.insertVertex(vertexes[i].first, vertexes[i].second);
        sets.push_back(F);
    }
    std::sort(edges.begin(), edges.end(), [](std::pair<std::pair<I, I>, E> a, std::pair<std::pair<I, I>, E> b){
        return a.second < b.second;
    });
}
