file(GLOB HEADERS "*.hpp"
                  "*.h")

add_library(fscio
            fsciolib.cpp
            crypto.cpp
            ${HEADERS})

add_native_library(native_fscio
                   fsciolib.cpp
                   crypto.cpp
                   ${HEADERS})

target_include_directories(fscio PUBLIC
                                 ${CMAKE_SOURCE_DIR}/libc/musl/include
                                 ${CMAKE_SOURCE_DIR}/libc/musl/src/internal
                                 ${CMAKE_SOURCE_DIR}/libc/musl/src/crypt
                                 ${CMAKE_SOURCE_DIR}/libc/musl/arch/fsc
                                 {CMAKE_SOURCE_DIR}/libcxx/include
                                 ${CMAKE_SOURCE_DIR}
                                 ${CMAKE_SOURCE_DIR}/boost/include)

target_include_directories(native_fscio PUBLIC
                                 ${CMAKE_SOURCE_DIR}/libc/musl/include
                                 ${CMAKE_SOURCE_DIR}/libc/musl/src/internal
                                 ${CMAKE_SOURCE_DIR}/libc/musl/src/crypt
                                 ${CMAKE_SOURCE_DIR}/libc/musl/arch/fsc
                                 ${CMAKE_SOURCE_DIR}/libcxx/include
                                 ${CMAKE_SOURCE_DIR}
                                 ${CMAKE_SOURCE_DIR}/boost/include)

target_link_libraries( fscio c c++ )
target_link_libraries( native_fscio native_c native_c++ )
add_dependencies( native_fscio fscio )


add_custom_command( TARGET fscio POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:fscio> ${BASE_BINARY_DIR}/lib )
add_custom_command( TARGET native_fscio POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:native_fscio> ${BASE_BINARY_DIR}/lib )

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../fsciolib DESTINATION ${BASE_BINARY_DIR}/include FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")
