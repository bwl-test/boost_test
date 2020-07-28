get_filename_component(PREFIX ${CMAKE_CURRENT_LIST_DIR} NAME)

message("prefix: ${PREFIX}")

set (
	TARGETS 
	simple
	spatial_index
)

foreach(TARGET ${TARGETS})
	set(FINAL_TARGET ${PREFIX}_${TARGET})

	set(SRCS main.cpp ${TARGET}.cpp)
	if(EXISTS ${TARGET}.hpp)
		list(APPEND SRCS ${TARGET}.hpp)
	endif()
	
	add_executable(${FINAL_TARGET} ${SRCS})

	target_link_libraries(
		${FINAL_TARGET}
		PRIVATE
		Boost::boost
		Boost::context
		Catch2
	)
endforeach()
