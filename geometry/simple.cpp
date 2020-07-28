#include <catch2/catch.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <iostream>
#include <fstream>

namespace bg = boost::geometry;
namespace bgs = bg::strategy;

using point = bg::model::point<double, 2, bg::cs::cartesian>;
using ring = bg::model::ring<point, false, false>;
using polygon = bg::model::polygon<point, false, false>;
using multipolygon = bg::model::multi_polygon<polygon>;

TEST_CASE( "geometry-simple-test", "[single-file]" ) {
    ring ring1{{0, 0}, {100, 0}, {100, 100}, {0, 100}};
    point p1{50, 50};
    
    std::cout << bg::wkt(ring1) << "\n";
    std::cout << bg::wkt(p1) << "\n";
    
    std::cout << bg::within(p1, ring1) << std::endl;
    
    std::cout << bg::within(point{100, 99}, ring1) << std::endl;
    
    multipolygon bufferdPolygons;
    bgs::buffer::distance_symmetric<double> distance_strategy{20};
    bgs::buffer::side_straight side_strategy;
    bgs::buffer::join_miter join_strategy;
    bgs::buffer::end_flat end_strategy;
    bgs::buffer::point_square point_strategy;
    
    bg::buffer(ring1, bufferdPolygons, distance_strategy, side_strategy, join_strategy, end_strategy, point_strategy);
    std::cout << bg::wkt(bufferdPolygons) << "\n";
    
    // Declare a stream and an SVG mapper
    std::ofstream svg("buffered.svg");
    bg::svg_mapper<point> mapper(svg, 400, 400);
    
    ring ring2{{100, 0}, {200, 0}, {200, 100}, {100, 100}};

    // Add geometries such that all these geometries fit on the map
    mapper.add(ring1);
    mapper.add(ring2);
    mapper.add(bufferdPolygons);

    // Draw the geometries on the SVG map, using a specific SVG style
    mapper.map(ring1, "fill-opacity:0.5;fill:rgb(255,0,0);stroke:rgb(153,204,0);stroke-width:2");
    mapper.map(ring2, "fill-opacity:0.5;fill:rgb(0,255,0);stroke:rgb(153,204,0);stroke-width:2");
    mapper.map(bufferdPolygons, "fill-opacity:0.3;fill:rgb(0,0,255);stroke:rgb(51,51,153);stroke-width:2");
//    mapper.map(c, "opacity:0.4;fill:none;stroke:rgb(212,0,0);stroke-width:5");
    
    std::ofstream raw_svg("buffered_raw.svg");
    raw_svg << bg::svg(bufferdPolygons, "fill-opacity:0.5;fill:rgb(255,0,0);stroke:rgb(153,204,0);stroke-width:2");
}
