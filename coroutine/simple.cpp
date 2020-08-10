#include <catch2/catch.hpp>
#include <iostream>
#include <boost/coroutine2/coroutine.hpp>

using namespace boost::coroutines2;

typedef boost::coroutines2::asymmetric_coroutine<int> coro_t;

void int_number_generate(coro_t::push_type &sink) {
	for(auto i=0; i< 100; ++i) {
		sink(i);
	}
    std::cout << "pull drive sink done!\n";
}

TEST_CASE( "coroutine-simple-test", "[single-file]" ) {
	coro_t::pull_type source{int_number_generate};

	for (auto num : source) {
		std::cout << num << "\n";
	}
    std::cout << "pull drive print done!\n";
}


void int_number_print(coro_t::pull_type &source) {
    for (auto num : source) {
        std::cout << num << "\n";
    }
    
    std::cout << "print done!\n";
}

TEST_CASE( "push-drive", "[single-file]" ) {
    coro_t::push_type sink{int_number_print};

    for(auto i=0; i< 100; ++i) {
        sink(i);
    }
    std::cout << "sink done!\n";
}
