cmake_minimum_required(VERSION 3.8)
project(MyFS)

#set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(includes)

add_definitions("-Wall -DFUSE_USE_VERSION=26")

add_executable(mount.myfs src/blockdevice.cpp
        src/myfs.cpp
        src/myinmemoryfs.cpp
        src/myondiskfs.cpp
        src/wrap.cpp
        src/mount.myfs.c)

add_executable(unittests src/blockdevice.cpp
        src/myfs.cpp
        src/myinmemoryfs.cpp
        src/myondiskfs.cpp
        testing/main.cpp
        testing/utest-blockdevice.cpp
        testing/utest-myfs.cpp
        testing/tools.cpp testing/itest.cpp)

add_executable(integrationtests
        src/blockdevice.cpp
        src/myfs.cpp
        src/myinmemoryfs.cpp
        src/myondiskfs.cpp
        testing/main.cpp
        testing/itest.cpp
        testing/tools.cpp)

find_package(PkgConfig)
pkg_check_modules(FUSE fuse)

set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR/catch})
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

target_link_libraries(mount.myfs ${FUSE_LDFLAGS})
target_compile_options(mount.myfs PUBLIC ${FUSE_CFLAGS})
target_include_directories(mount.myfs PUBLIC ${FUSE_INCLUDE_DIRS})

target_link_libraries(unittests PRIVATE Catch ${FUSE_LDFLAGS})
target_compile_options(unittests PUBLIC ${FUSE_CFLAGS})
target_include_directories(unittests PUBLIC ${FUSE_INCLUDE_DIRS})

target_link_libraries(integrationtests PRIVATE Catch ${FUSE_LDFLAGS})
target_compile_options(integrationtests PUBLIC ${FUSE_CFLAGS})
target_include_directories(integrationtests PUBLIC ${FUSE_INCLUDE_DIRS})
