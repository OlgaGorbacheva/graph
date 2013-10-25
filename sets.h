#include <map>

namespace my {
template<class T>
class sets;
}

template<class T>
class my::sets
{
private:
    std::map<T, T> sys; //element, parent
public:
    void make (T elem) {
        sys.insert(std::make_pair(elem, elem));
    }

    T find (T elem) {
        if (sys.find(elem) == sys.end())
            throw "set doesn't exist";
        if (elem == sys[elem])
            return elem;
        return find (sys[elem]);
    }

    void merge (T elem1, T elem2) {
        elem1 = find (elem1);
        elem2 = find (elem2);
        if (elem1 != elem2)
            sys[elem2] = elem1;
    }
};
