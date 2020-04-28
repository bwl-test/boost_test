#include <iostream>
#include <string>
#include <catch2/catch.hpp>
#include <boost/fusion/adapted.hpp>
#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/include/sequence.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/next_prior.hpp>

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

///
struct my_vec_tag;
struct my_vec_iterator_tag;

///tag_of
template <class Seq>
struct tag_of {
    using type = typename Seq::fusion_tag;
};

///vector元素类型推导模拟
template <size_t N, class T>
struct Store{
    using ElementType = T;
    
    Store(T item) : element(item) {}
    ElementType element;
};

template <class Index, class... Ts>
struct VectorImpl;

template <size_t... I, class... Ts>
struct VectorImpl<std::index_sequence<I...>, Ts...> : public Store<I, Ts>...
{
    template<class... Us>
    VectorImpl(Us&&... us) : Store<I, Ts>(std::forward<Us>(us))... {}
};

template <size_t N, class U>
Store<N, U> store_at_impl(const Store<N, U>&);

template <class... Ts>
struct Vector : VectorImpl<std::make_index_sequence<sizeof...(Ts)>, Ts...>
{
public:
    using fusion_tag = my_vec_tag;
    using base = VectorImpl<std::make_index_sequence<sizeof...(Ts)>, Ts...>;
    
    template<class... Us>
    Vector(Us&&... us) : base(std::forward<Us>(us)...) {}
    
private:
    template <size_t J>
    using at_store = decltype(store_at_impl<J>(std::declval<Vector>()));
    
public:
    template <size_t J>
    typename at_store<J>::ElementType& at_impl() {
        return at_store<J>::element;
    }
};

template <size_t N, class U>
U value_at_impl(const Store<N, U> &);

///iterator
template <class Seq, class N>
struct MyVectIterator {
    using Vector = Seq;
    using Index = N;
    
    MyVectIterator(Seq &seq) : _seq(seq) {}
    
    Seq &_seq;
};

///begin
template <class tag>
struct begine_impl;

template <>
struct begine_impl<my_vec_tag> {
    template <class Seq>
    struct apply {
        using type = MyVectIterator<Seq, mpl_::int_<0>>;
        
        static type
        call(Seq &seq) {
            return type{seq};
        }
    };
};


template <class Seq>
struct begin : begine_impl<typename tag_of<Seq>::type >{};


using MyVec = Vector<int, short, std::string, float, double>;

TEST_CASE("vector simulation", "[single-file]") {
    decltype(value_at_impl<2>(std::declval<MyVec>())) a = "hello you!!";
    
    MyVec myvec{1, 2, "hello my vec", 3, 4.0};
    std::cout << myvec.at_impl<1>() << "\n";
    
    myvec.at_impl<1>() = 5;
    std::cout << myvec.at_impl<1>() << "\n";
}
