set(SRCS main.cpp trivial.cpp)

add_executable(fusion ${SRCS})

target_link_libraries(
	fusion
	PRIVATE
	Boost::boost
	Catch2
)