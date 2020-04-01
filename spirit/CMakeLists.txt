set(SRCS main.cpp trivial.cpp)

add_executable(spirit ${SRCS})

target_link_libraries(
	spirit
	PRIVATE
	Boost::boost
	Catch2
)