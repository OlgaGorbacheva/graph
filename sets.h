#include <unordered_map>

namespace my {
template<class T>
class elem;
template<class T>
class set_system;
}

template<class T>
class my::elem
{
private:
    elem<T>* parent;
    T value;
public:
    elem(elem<T>* _parent, T _value):parent(_parent), value(_value)
    {}
    T get_value() {
        return value;
    }
    elem<T> get_parent() {
        return parent;
    }
    T set_parent(elem<T>* _parent) {
        parent = _parent;
    }
};

template<class T>
class my::set_system
{
private:
    std::unordered_map<my::elem<T>, int> sets;
    std::unordered_map<T, my::elem<T>> elems;
public:
    set_system(){}
    void make(T value) {
        my::elem<T> root(nullptr, value);
        sets.insert(root, 1);
        elems.insert(value, root);
    }
    T find(T value) {
        my::elem<T> elem = elems.at(value);
        my::elem<T> root = elems.at(value);
        my::elem<T> *parent;
        while ((parent = root.get_parent()) != nullptr) {
            root = *parent;
        }
        elem.set_parent(&root);
        return root.get_value();
    }
    void merge(T value1, T value2) {
        T root1 = find_set(value1),
                root2 = find_set(value2);
        if (root1 == root2)
            return;
        my::elem<T> elem_r1 = elems.at(root1), elem_r2 = elems.at(root2);
        if (sets[elem_r1] > sets[elem_r2]) {
            elem_r2.set_parent(&elem_r1);
        } else {
            elem_r1.set_parent(&elem_r2);
        }
    }
};
