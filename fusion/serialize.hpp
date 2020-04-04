#pragma once
#include <iostream>
#include <type_traits>
#include <vector>
#include <boost/fusion/sequence.hpp>
#include <boost/fusion/support.hpp>
#include <boost/fusion/algorithm.hpp>

namespace simple {

using namespace boost;

struct Serializer {
    template <class T>
    void operator()(const T& t,
                    std::enable_if_t<!fusion::traits::is_sequence<T>::value> *dummy=nullptr) const {
        std::cout << t;
        std::cout << "\n";
    }
    
    template <class T>
    void operator()(const T& t,
                    std::enable_if_t<fusion::traits::is_sequence<T>::value> *dummy=nullptr) const {
        fusion::for_each(t, *this);
    }
    
    template <class T>
    void operator()(const std::vector<T> &vec) const {
        std::cout << "vec capacity: " << vec.size() << "\n";
        for(auto const& item : vec) {
            this->operator()(item);
        }
    }
};

template <class T>
void serialize(const T& t) {
    Serializer serializer;
    serializer(t);
}

}
