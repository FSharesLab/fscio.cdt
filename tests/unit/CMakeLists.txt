list(APPEND CMAKE_MODULE_PATH ${FSCIO_CDT_BIN})
include(FscioCDTMacros)

add_native_executable(name_tests name_tests.cpp)
add_native_executable(system_tests system_tests.cpp)
add_native_executable(print_tests print_tests.cpp)
add_dependencies(name_tests FscioTools)
add_dependencies(system_tests FscioTools)
add_dependencies(print_tests FscioTools)
