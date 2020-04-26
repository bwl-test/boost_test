#include <iostream>
#include <string>
#include <tuple>
#include <catch2/catch.hpp>
#include <boost/fusion/support.hpp>
#include <boost/fusion/container.hpp>
#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/include/adapted.hpp>
#include <boost/fusion/view.hpp>
#include <boost/fusion/include/io.hpp>


using namespace boost;

template <class T>
struct unimplement;

using point_2i_t = std::tuple<int, int>;
using point_2d_t = std::tuple<double, double>;
using point_3i_t = std::tuple<int, int, int>;
using point_3d_t = std::tuple<double, double, double>;

struct MyPoint {
    int x; double y;
};

class SecretPoint {
public:
    SecretPoint(float x_, float y_) {
        x = x_;
        y = y_;
    }
    
    float getX() const {
        return x;
    }
    
    float getY() const {
        return y;
    }
    
    void setX(float x_) {
        x = x_;
    }
    
    void setY(float y_) {
        y= y_;
    }
    
private:
    float x, y;
};

BOOST_FUSION_ADAPT_STRUCT(MyPoint, x, y)

BOOST_FUSION_ADAPT_ADT(SecretPoint,
                       (float, float, obj.getX(), obj.setX(val))
                       (float, float, obj.getY(), obj.setY(val)))

struct Pythagoras {
    template <class T>
    double operator()(double acc, const T &t) const {
        std::cout << t << "\n";
        auto diff = fusion::at_c<0>(t) - fusion::at_c<1>(t);
        return acc + diff * diff;
    }
};

template <class P1, class P2>
double distance(P1& p1, P2& p2) {
//    static_assert(fusion::result_of::size<P1>::value == fusion::result_of::size<P2>::value
//                  , "p1 p2 has to be same size!");

    typedef fusion::vector<P1&, P2&> zipt;
    auto pythagoras = fusion::fold(fusion::zip_view<zipt>(zipt(p1, p2)), 0, Pythagoras{});
    return sqrt(pythagoras);
}


TEST_CASE("zip_view test", "[single-file]") {
    std::cout << "--------------zip_view test------------------\n";
    
    point_2i_t p1{0, 0};
    point_2d_t p2{3.0, 4.0};
    std::cout << "distance of p0 p1 is: " << distance(p1, p2) << "\n";
    
    point_3d_t p3{6.0, 8.0, 10.0};
    std::cout << "distance between p1 and p3 is: " << distance(p1, p3) << "\n";
    
    MyPoint mypoint{3, 4.0};
    std::cout << "distance between p1 and mypoint is: " << distance(p1, mypoint) << "\n";
    
    SecretPoint secretPoint{6, 8};
    std::cout << "distance between p1 and secret piont is: " << distance(p1, secretPoint) << "\n";
}
