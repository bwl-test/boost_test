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

TEST_CASE("struct test", "[single-file]") {
    MyStruct mystruct;
    mystruct.a = 1;
    mystruct.b = 2;
    mystruct.name = "jhon";
    auto const &vec = fusion::as_vector(mystruct);
    std::cout << vec << "\n";
    
    std::cout << mystruct.a << "\n";
    std::cout << mystruct.b << "\n";
    std::cout << mystruct.name << "\n";
}
