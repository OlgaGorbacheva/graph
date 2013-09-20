#ifndef ITERATOR_H
#define ITERATOR_H
#include "graph.h"

//template<class V, class E>
//graph<V, E>::iterator_dfs::iterator_dfs(graph<V, E> &_G):G(_G)
//{ // заполнить color 0
//}

//template<class V, class E>
//graph<V, E>::iterator_dfs::iterator_dfs(graph<V, E>::iterator_dfs const &itr):color(itr.color),
//    elem(itr.elem), passed(itr.passed), G(itr.G)
//{}

//template<class  V, class E>
//typename graph<V, E>::iterator_dfs & graph<V, E>::iterator_dfs::operator ++()
//{
//    if (passed.size() == 0){ //стек dfs пуст
//        typename std::unordered_map<int, char>::iterator itr = color.begin(), end = color.end(); //пробежимся по вершинам и их цветам
//        for (; itr != end; itr++)
//            if (itr->second == 0){ //если белая вершина найдена - стек не пуст, можно выходить из цикла
//                passed.push(itr->first);
//                itr->second = 1;
//                elem = G.ver.find(itr->first);
//                break;
//            }
//        if (itr == end){ //если нет, конец графа
//            elem = G->ver.end();
//            return *this;
//        }
//    }
//    bool flag = true;
//    while (flag){
//        flag = false;
//        std::list<std::pair<int, V> > l = G.getAccessVertexes(passed.top()); //пробежимся по списку смежности для поиска непосещенных вершин
//        auto itr = l.begin(), end = l.end();
//        for(; itr != end && !flag; itr++){
//            if ()
//                ;
//            typename vector<shared_ptr<vertex<TypeV> > >::iterator cur = find(G->ver.begin(), G->ver.end(), (itr->first).lock()),
//                    beg = G->ver.begin();
//            if (color[cur - beg] == 0){
//                flag = true; // нашли белую вершину => можем перейти в нее
//                color[cur - beg] = 1;
//                passed.push(cur - beg);
//            }
//        }
//    }
//    color[passed.top()] = 2; //выход из цикла, значит идти некуда => вершина становится черной
//    elem = G->ver.begin() + passed.top();
//    passed.pop();
//    return *this;
//}

//template<class TypeV, class TypeE>
//shared_ptr<vertex<TypeV> > & graph<TypeV, TypeE>::iterator_dfs::operator *()
//{
//    return *elem;
//}

//template<class TypeV, class TypeE>
//bool graph<TypeV, TypeE>::iterator_dfs::operator ==(graph<TypeV, TypeE>::iterator_dfs const itr)
//{
//    return elem == itr.elem;
//}

//template<class TypeV, class TypeE>
//bool graph<TypeV, TypeE>::iterator_dfs::operator !=(graph<TypeV, TypeE>::iterator_dfs const itr)
//{
//    return elem != itr.elem;
//}


///////////////////////////////////////////

//template<class DataV, class DataE>
//graph<DataV, DataE>::iterator_bfs::iterator_bfs(graph<DataV, DataE> *_G):G(_G)
//{
//    color.resize(G->Inf.size(), 0);
//}

//template<class DataV, class DataE>
//DataV & graph<DataV, DataE>::iterator_bfs::operator *()
//{
//    return *elem;
//}

//template<class DataV, class DataE>
//typename graph<DataV, DataE>::iterator_bfs& graph<DataV, DataE>::iterator_bfs::operator ++()
//{
//    if (passed.size() == 0){
//        vector<char>::iterator itr = color.begin(), end = color.end();
//        for (int i = 0; itr != end; itr++, i++)
//            if (*itr == 0){
//                passed.push(i);
//                *itr = 1;
//                break;
//            }
//        if (itr == end){
//            elem = G->Inf.end();
//            return *this;
//        }
//    }
//    typename list<pair<int, DataE> >::const_iterator itr = G->AdjR[passed.front()].begin(), end = G->AdjR[passed.front()].end();
//    for(; itr != end; itr++){
//        if (color[itr -> first] == 0){
//            color[itr -> first] = 1;
//            passed.push(itr -> first);
//        }
//    }
//    color[passed.front()] = 2;
//    elem = G->Inf.begin() + passed.front();
//    passed.pop();
//    return *this;
//}

//template<class DataV, class DataE>
//graph<DataV, DataE>::iterator_dfs::iterator_dfs(graph<DataV, DataE>::iterator_dfs const &itr):color(itr.color),
//    elem(itr.elem), passed(itr.passed), G(itr.G)
//{}

//template<class DataV, class DataE>
//graph<DataV, DataE>::iterator_bfs::iterator_bfs(graph<DataV, DataE>::iterator_bfs const &itr):color(itr.color),
//    elem(itr.elem), passed(itr.passed), G(itr.G)
//{}

//template<class DataV, class DataE>
//bool graph<DataV, DataE>::iterator_bfs::operator ==(graph<DataV, DataE>::iterator_bfs const itr)
//{
//    return elem == itr.elem;
//}

//template<class DataV, class DataE>
//bool graph<DataV, DataE>::iterator_bfs::operator !=(graph<DataV, DataE>::iterator_bfs const itr)
//{
//    return elem != itr.elem;
//}

#endif // ITERATOR_H
