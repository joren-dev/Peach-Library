foreach(component ${peach_library_FIND_COMPONENTS})
    include(${CMAKE_CURRENT_LIST_DIR}/peach_library-${component}-config.cmake)
endforeach()
