set(TARGETS 
	trivial
	serialize
	invoke
    simple_group
	zip_view
	result_of
	struct)

foreach(target ${TARGETS})
	set(target_src main.cpp common.hpp ${target}.cpp)
	if(EXISTS ${target}.hpp)
		list(APPEND target_src ${target}.hpp)
	endif()
 
    message(${target})
	
	add_executable(fusion-${target} ${target_src})
	target_link_libraries(
		fusion-${target}
		PRIVATE
		Boost::boost
		Catch2
	)
endforeach()
