#include "common.hpp"
#include <iostream>
#include <type_traits>
#include <tuple>
#include <string>
#include <catch2/catch.hpp>
#include "serialize.hpp"
#include <boost/fusion/adapted.hpp>



TEST_CASE( "serialize misc", "[single-file]" ) {
    std::cout << "--------------serialize_test------------------\n";
    int a = 0;
    simple::Serializer serializer;
    serializer(a);
    
    MyStruct mystruct{1, 2.0, "hello mystruct"};
    serializer(mystruct);
    
    std::vector<int> vec{4,5,6,7};
    simple::serialize(vec);
    
    auto tuple = std::tie(a, mystruct, vec);
    simple::serialize(tuple);
}
