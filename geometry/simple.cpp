#include <catch2/catch.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/geometry/geometries/register/ring.hpp>
#include <boost/geometry/geometries/register/point.hpp>
#include <boost/geometry/views/detail/boundary_view.hpp>
#include <iostream>
#include <fstream>

template <class T>
struct unimplement;

namespace bg = boost::geometry;
namespace bgs = bg::strategy;

using point = bg::model::point<double, 2, bg::cs::cartesian>;
using multi_point = bg::model::multi_point<point>;
using line_string = bg::model::linestring<point>;
using multi_line_string = bg::model::multi_linestring<line_string>;
using ring = bg::model::ring<point, false, false>;
using polygon = bg::model::polygon<point, false, false>;
using multipolygon = bg::model::multi_polygon<polygon>;

TEST_CASE( "geometry-buffer-test", "[single-file]" ) {
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


TEST_CASE( "geometry-intersetion-test", "[single-file]" ) {
    ring ring1{{0, 0}, {100, 0}, {100, 100}, {0, 100}};
    ring ring2{{10, 50}, {90, 50}, {50, 150}};
    
    bg::correct(ring1);
    bg::correct(ring2);
    
    multipolygon polygonOut;
    bg::intersection(ring1, ring2, polygonOut);
    std::cout << bg::wkt(polygonOut) << "\n";
    
    multi_point pointOut;
    bg::intersection(ring1, ring2, pointOut);
    std::cout << bg::wkt(pointOut) << "\n";
    
    multi_line_string linestringOut;
    bg::intersection(ring2, ring1, linestringOut);
    std::cout << bg::wkt(linestringOut) << "\n";
    
    multi_line_string linestringOut2;
    bg::intersection(bg::detail::boundary_view<ring>(ring2), ring1, linestringOut2);
    std::cout << bg::wkt(linestringOut2) << "\n";
    
    std::cout << std::boolalpha <<  bg::within(ring2, ring1) << "\n";
}


class Point {
public:
    double _x, _y;
    Point():_x(),_y(){}
    Point(double x, double y):_x(x),_y(y){}
};

BOOST_GEOMETRY_REGISTER_POINT_2D(Point, double, bg::cs::cartesian, _x, _y)
BOOST_GEOMETRY_REGISTER_RING(std::vector<Point>)

namespace bg = boost::geometry;

template <typename G>
void test(G const& g1, G const& g2) {
    std::cout << "----\nIntersecting\n\t" << bg::wkt(g1) << "\n\t" << bg::wkt(g2) << "\nresult: ";

    std::vector<G> polygon_results;
    bg::intersection<G, G>(g1, g2, polygon_results);

    for (auto polygon : polygon_results)
        std::cout << bg::wkt(polygon) << "\n";
}

TEST_CASE( "geometry-adapting-test", "[single-file]" ) {
    using Ring = std::vector<Point>;

    test<Ring>(
            {{749,  271999},  {270000, 272000}, {270000, -228000},    {750, -227999},     {749,  271999}},
            {{-230000, -228000}, {-230000,  39250}, {270000,   39250}, {270000, -228000}, {-230000, -228000}});
    test<Ring>(
            {{0.075,   27.2},  { 27,   27.2}, { 27, -22.8 }, { 0.075, -22.8 }, { 0.075,  27.2 }},
            {{ -23, -22.8 }, { -23, 3.925 }, { 27, 3.925 },    { 27, -22.8 },   { -23, -22.8 }});
}
