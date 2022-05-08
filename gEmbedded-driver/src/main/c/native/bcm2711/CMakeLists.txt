include_directories(include)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    SET(LIBRARY_NAME gEmbeddedRaspi4B64)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    SET(LIBRARY_NAME gEmbeddedRaspi4B32)
endif()

SET(SHARED_LIB_NAME ${LIBRARY_NAME})

add_subdirectory(src)
add_subdirectory(test)