get_filename_component(PREFIX ${CMAKE_CURRENT_LIST_DIR} NAME)

message("prefix: ${PREFIX}")

find_package(Boost 
			 REQUIRED
			 COMPONENTS
			 serialization)

set (
	TARGETS 
	simple
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
		Boost::serialization
		Catch2
	)
endforeach()
