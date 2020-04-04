set(SRCS 
	main.cpp 
	common.hpp
	trivial.cpp 
	serialize.hpp test_serialize.cpp
	test_invoke.cpp)

add_executable(fusion ${SRCS})

target_link_libraries(
	fusion
	PRIVATE
	Boost::boost
	Catch2
)