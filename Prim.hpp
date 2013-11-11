#include "graph_algorithm.h"

template<class I, class V, class E>
bool less(std::pair<I, std::pair<I, E>> e1, std::pair<I, std::pair<I, E>> e2)
{
    if (e1.second.second == -1)
        return false;
    if (e2.second.second == -1)
        return true;
    return e1.second.second < e2.second.second;
}

template<class I, class V, class E>
my::graph<I, V, E> Prim(my::graph<I, V, E> const &G)
{
    if (G.empty())
        return G;
    std::vector<std::pair<I, V>> vertexes = G.getVertexes();
    I source = vertexes[0].first;
    my::graph<I, V, E> tree; //мин остовное дерево
    std::set<I> visited; // посещенные вершины
    visited.insert(source);
    tree.insertVertex(source, G[source]);
    std::unordered_map<I, std::pair<I, E>> candidates;//vertex, parent, value
//    std::vector<std::pair<I, std::pair<I, E>>> _candidates;
    std::vector<std::pair<I, E>> newEdges = G.getOutEdges(source); //вершины, которые, возможно, стоит добавить
    std::for_each(vertexes.begin(), vertexes.end(), [&candidates, &source](std::pair<I, V> vertex){
        if (vertex.first != source) {
            candidates.insert(std::make_pair(vertex.first, (std::make_pair(source, -1))));
        }
    });
    std::for_each(newEdges.begin(), newEdges.end(), [&candidates, &source](std::pair<I, E> edge) {
        typename std::unordered_map<I, std::pair<I, E>>::iterator it;
        if (edge.first != source) {
            it = candidates.find(edge.first);
            if (less<I, V, E>(std::make_pair(edge.first, std::make_pair(source, edge.second)), (*it)))
                it->second = std::make_pair(source, edge.second);
        }
    });
    while(true) {
        if (candidates.empty())
            break;
        std::pair<I, std::pair<I, E>> current = *(std::min_element(candidates.begin(), candidates.end(), less<I, E, V>));
        if (current.second.second == -1)
            throw "Graph is not connected";
        tree.insertVertex(current.first, G[current.first]);
        tree.insertEdge(current.first, current.second.first, current.second.second);
        tree.insertEdge(current.second.first, current.first, current.second.second);
        visited.insert(current.first);
        candidates.erase(current.first);
        newEdges = G.getOutEdges(current.first);
        std::for_each(newEdges.begin(), newEdges.end(), [&candidates, &current](std::pair<I, E> edge) {
            typename std::unordered_map<I, std::pair<I, E>>::iterator it;
            if ((it = candidates.find(edge.first)) != candidates.end() && edge.first != current.first) {
                if (less<I, V, E>(std::make_pair(edge.first, std::make_pair(current.first, edge.second)), (*it)))
                    it->second = std::make_pair(current.first, edge.second);
            }
        });
    }
    return tree;
}
