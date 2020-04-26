#include <iostream>
#include <type_traits>
#include <tuple>
#include <catch2/catch.hpp>
#include <boost/fusion/include/filter_view.hpp>

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/filter.hpp>
#include <boost/fusion/include/find.hpp>
#include <boost/fusion/include/push_back.hpp>
#include <boost/fusion/adapted.hpp>
#include <boost/fusion/container.hpp>
//#include <boost/fusion/sequence.hpp>
#include <boost/fusion/include/at_key.hpp>

using namespace boost;

template <class T>
struct unimplement;

TEST_CASE( "trival-test", "[single-file]" ) {
    std::cout << "--------------trival-test------------------\n";
    std::cout << std::boolalpha;
    
    using tuple_t = std::tuple<int, std::string, std::string, bool>;
    tuple_t tuple = std::make_tuple(10, "hello tuple", "hello tuple2", true);
    std::cout << fusion::as_vector(tuple) << "\n";
    
    auto set = fusion::as_set(tuple);
    fusion::at_key<std::string>(set) = "Another string";
    std::cout << set << "\n";
    std::cout << fusion::as_vector(tuple) << "\n";
    
//    fusion::detail::at_key_impl<decltype(set), std::string, fusion::set_tag> b;
    
//    unimplement<decltype(fusion::as_set(tuple))> a;
    
    fusion::filter_view<tuple_t, std::is_integral<mpl::_1>> view{tuple};
    std::cout << view << "\n";
    fusion::for_each(view, [](auto &val) {
        std::cout << "visit " << val << "\n";
    });
    
    std::cout << fusion::filter<std::string>(tuple) << "\n";
    std::cout << *fusion::find<bool>(tuple) << "\n";
    
    auto const &iter = fusion::begin(tuple);
    std::cout << *iter << "\n";
    
    auto const &next_2_iter = fusion::advance_c<2>(iter);
    std::cout << *next_2_iter << "\n";
    
    std::cout << "size of tuple: " << fusion::size(tuple) << "\n";
    
    auto const &tuple2 = fusion::push_back(tuple, 'X');
    std::cout << "size of tuple2: " << fusion::size(tuple2) << "\n";
    
    std::cout << "size of tuple2: " << fusion::size(tuple2) << "\n";
//    std::cout << "end of tuple2: " << *fusion::end(tuple2) << "\n";
}
