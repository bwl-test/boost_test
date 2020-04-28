#include <iostream>
#include <string>
#include <catch2/catch.hpp>
#include <boost/fusion/adapted.hpp>
#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/include/sequence.hpp>

using namespace boost;

BOOST_FUSION_DEFINE_STRUCT (
    (),
    MyStruct,
    (int, a)
    (double, b)
    (std::string, name)
)

BOOST_FUSION_DEFINE_STRUCT (
    (),
    MyStruct2,
    (int, a)
    (double, b)
    (float, c)
)

TEST_CASE("struct test", "[single-file]") {
    MyStruct mystruct{1, 2, "jhon"};
    auto vec = fusion::as_vector(mystruct);
    std::cout << vec << "\n";
    
    mystruct.a = 3;
    mystruct.b = 4;
    mystruct.name = "white";
    vec = mystruct;
    std::cout << vec << "\n";
    
    fusion::at_c<2>(vec) = "jack";
    mystruct = vec;
    std::cout << mystruct.name << "\n";
    
    MyStruct2 mystruct2{7, 8, 9};
//    decltype(vec) vec2{mystruct2};
}
