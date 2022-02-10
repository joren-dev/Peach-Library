set(component exceptions)

add_library(${component} STATIC	src/exception.cpp)

target_compile_features(${component} PRIVATE cxx_std_20)

target_include_directories(${component} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                                               $<INSTALL_INTERFACE:include>
)

install(
    TARGETS ${component}
    EXPORT ${PROJECT_NAME}-targets
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	INCLUDES DESTINATION include
)

if(COMPONENT_TARGETS_ENABLED)
	# generate and install export file for this component target
	install(
		EXPORT ${PROJECT_NAME}-targets
		FILE ${PROJECT_NAME}-${component}-targets.cmake
		NAMESPACE ${PROJECT_NAME}::
		DESTINATION lib/cmake/${PROJECT_NAME}
	)
endif()

# install header files
install(
	DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
	TYPE INCLUDE
	FILES_MATCHING
	PATTERN "*.hpp"
)
