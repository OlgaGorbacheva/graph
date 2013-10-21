#include "graph_algorithm.h"

#include <unordered_map>
#include <stack>

template<class I, class V, class E>
std::vector<std::vector<I> > Tarjan(my::graph<I, V, E> const &G)
{
    std::unordered_map<I, std::pair<int, int> > vertexes; // id вершины, index, low_index
    std::vector<std::vector<I> > areas;
    std::stack<I> algo_stack;
    std::vector<std::pair<I, V> > ver = G.getVertexes();
    auto ver_itr = ver.begin(), ver_end = ver.end();
    for (; ver_itr != ver_end; ver_itr++){
        vertexes.insert(std::make_pair(ver_itr->first, std::make_pair(-1, -1)));
    }
    typename my::graph<I, V, E>::iterator_dfs itr = G.begin_dfs(), end = G.end_dfs();
    for (int i = 0; itr != end; itr++){
        if (itr.getColor() == 1){
            algo_stack.push(itr->getId());
            vertexes[(*itr).getId()].first = i;
            vertexes[(*itr).getId()].second = i;
            i++;
        }else{
            std::vector<std::pair<I, V> > acc_ver = G.getAccessVertexes(itr->getId());
            auto acc_ver_itr = acc_ver.begin(), acc_ver_end = acc_ver.end();
            for (; acc_ver_itr != acc_ver_end; acc_ver_itr++){
                if (vertexes[itr->getId()].second > vertexes[acc_ver_itr->first].second &&
                        vertexes[acc_ver_itr->first].second != -1){
                    vertexes[itr->getId()].second = vertexes[acc_ver_itr->first].second;
                }
            }
            if (vertexes[itr->getId()].second == vertexes[itr->getId()].first){
                std::vector<I> cur_area;
                while((*itr).getId() != algo_stack.top()){
                    cur_area.push_back(algo_stack.top());
                    algo_stack.pop();
                }
                cur_area.push_back(algo_stack.top());
                algo_stack.pop();
                areas.push_back(cur_area);
            }
        }
    }
    return areas;
}
