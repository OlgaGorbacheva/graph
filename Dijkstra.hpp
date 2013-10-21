#include "graph_algorithm.h"

//template<class E>
//E

//aaa;


template<class I, class V, class E>
std::map<I, E> Dijkstra(my::graph<I, V, E> const &G, I const _id)
{
    std::map<I, E> d;
    std::map<I, E> ver;
//    ver.resize(G.getVertexesNumber());
//    int i = 0;
//    std::for_each(G.getVertexes().begin(), G.getVertexes().end(), [&ver, &i](std::pair<I, V> v)
//                {
//                    ver[v.first] = v.second;
//                });
    ver.insert(std::make_pair(_id, E()));
//    std::vector<E> heap;
//    std::for_each(G.getVertexes().begin(), G.getVertexes().end(), [&heap, _id](std::pair<I, V> v)
//                {
//                    if (v->first != _id)
//                        heap[v->first] = INT_MAX;
//                    else heap[v->first] = 0;
//                });
//    std::make_heap(heap.begin(), heap.end()); //мы сделали кучу... далее истеричный смех
//    my::graph<I, V, E>::iterator_bfs itr = G.begin_bfs(heap[0]);
//    //как сделать в stl heap на парах?????
}

