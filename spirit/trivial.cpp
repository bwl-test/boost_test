#include <iostream>
#include <type_traits>
#include <tuple>
#include <catch2/catch.hpp>
#include <boost/fusion/adapted.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/algorithm/transformation/zip.hpp>

using namespace boost;

struct MyStruct { int i; bool b; double d; };

BOOST_FUSION_ADAPT_STRUCT (
    MyStruct,
    i,
    b,
    d
)

auto to_tuple(MyStruct const& ms){
   std::tuple<int, bool, double> ret;
   auto z = fusion::zip(ret, ms);
   fusion::for_each(z, [](auto& ze){std::get<0>(ze) = std::get<1>(ze);});
   return ret;
}

TEST_CASE( "simple", "[single-file]" ) {
    MyStruct a{1, false, 3.0};
    auto tuple = to_tuple(a);
    REQUIRE(tuple == std::tie(a.i, a.b, a.d));
}
