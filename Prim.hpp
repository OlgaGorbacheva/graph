#include "graph_algorithm.h"

template<class I, class V, class E>
my::graph<I, V, E> Prim(my::graph<I, V, E> const &G)
{
    I source;
    try{
        source = G.getVertexes().at(0).first;
    }
    catch(std::out_of_range){
        return G;
    }
    my::graph<I, V, E> tree;
    std::set<I> visited;
    visited.insert(source);
    tree.insertVertex(source, G[source]);
    while(true) {
        std::multimap<E, std::pair<I, I>> candidates; // edge's wheight, parent, vertex
        std::for_each(visited.begin(), visited.end(), [&candidates, &G, &visited](I id) {
            std::vector<std::pair<I, E>> edges = G.getOutEdges(id);
            typename std::vector<std::pair<I, E>>::iterator minEdge = edges.begin();
            bool isExist = false;
            if (visited.find(minEdge->first) == visited.end())
                isExist = true;
            for (auto itr = ++edges.begin(), end = edges.end(); itr != end; itr++){
                if ((itr->second < minEdge->second && visited.find(itr-> first) == visited.end()) ||
                        (!isExist && visited.find(itr-> first) == visited.end())) {
                    isExist = true;
                    minEdge = itr;
                }
            }
            if (isExist) {
                candidates.insert(std::make_pair(minEdge->second, std::make_pair(id, minEdge->first)));
            }
//            std::sort(edges.begin(), edges.end(), [](std::pair<I, E> a, std::pair<I, E> b){
//                return a.second < b.second;
//            });
        });
        if (candidates.empty())
            break;

        tree.insertVertex(candidates.begin()->second.second, G[candidates.begin()->second.second]);
        tree.insertEdge(candidates.begin()->second.first, candidates.begin()->second.second, candidates.begin()->first);
        tree.insertEdge(candidates.begin()->second.second, candidates.begin()->second.first, candidates.begin()->first);
        visited.insert(candidates.begin()->second.second);
    }
    if (visited.size() < G.getVertexes().size())
        throw "Graph is not connected";
    return tree;
}
