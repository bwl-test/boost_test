#include <iostream>
#include <string>
#include <catch2/catch.hpp>
#include <boost/fusion/adapted.hpp>
#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/include/sequence.hpp>

///vector tag声明却无定义并不影响作为tag使用!!
struct MyStructIteratorTag;

template <class Tag>
struct MyAdvance {
    using type = void;
};

template <>
struct MyAdvance<MyStructIteratorTag> {
    using type = int;
};

///vector元素类型推导模拟
template <size_t N, class T>
struct Store{
    T element;
};

template <class Index, class... Ts>
struct VectorImpl;

template <size_t... I, class... Ts>
struct VectorImpl<std::index_sequence<I...>, Ts...> : public Store<I, Ts>...
{};

template <class... Ts>
struct Vector : VectorImpl<std::make_index_sequence<sizeof...(Ts)>, Ts...>
{};

template <size_t N, class U>
U value_at_impl(const Store<N, U> &);

using MyVec = Vector<int, short, std::string, float, double>;


TEST_CASE("vector simulation", "[single-file]") {
    decltype(value_at_impl<2>(std::declval<MyVec>())) a = "hello you!!";
}