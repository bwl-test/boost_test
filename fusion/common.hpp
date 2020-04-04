#pragma once

#include <string>
#include <boost/fusion/adapted.hpp>

struct MyStruct {
    int i;
    double d;
    std::string name;
};

BOOST_FUSION_ADAPT_STRUCT (
    MyStruct,
    i,
    d,
    name
)