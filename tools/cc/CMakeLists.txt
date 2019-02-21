configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fscio-cc.cpp.in ${CMAKE_BINARY_DIR}/fscio-cc.cpp)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fscio-cpp.cpp.in ${CMAKE_BINARY_DIR}/fscio-cpp.cpp)

add_tool(fscio-cc)
add_tool(fscio-cpp)
