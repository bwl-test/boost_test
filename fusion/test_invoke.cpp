#include "common.hpp"
#include <boost/fusion/container.hpp>
#include <boost/fusion/functional.hpp>
#include <boost/fusion/algorithm.hpp>
#include <iostream>
#include <string>
#include <catch2/catch.hpp>

using namespace boost;

void foo(int i, double d, const std::string &name) {
    auto const &vec = fusion::vector_tie(i, d, name);
    for_each(vec, [](auto const &item) {std::cout << item; std::cout << "\n";});
}

TEST_CASE("invoke test", "[single-file]") {
    std::cout << "--------------invoke_test------------------\n";
    MyStruct mystruct{3, 4, "baiwenlei"};
    fusion::invoke(foo, mystruct);
    
    auto const fused_foo = fusion::make_fused(&foo);
    fused_foo(mystruct);
}
