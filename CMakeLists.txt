cmake_minimum_required(VERSION 3.8)
project(MyFS)

#set(CMAKE_VRBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(MOUNT
        src/blockdevice.cpp
        src/myfs.cpp
        src/wrap.cpp
        src/mount.myfs.c
        src/myinmemoryfs.cpp)

set(UNITTESTS
        src/blockdevice.cpp
        src/myfs.cpp
        testing/main.cpp
        testing/utest-blockdevice.cpp
        testing/utest-myfs.cpp
        testing/helper.cpp src/myinmemoryfs.cpp includes/myinmemoryfs.h)

include_directories(includes)

set(COMPILE_FLAGS "-Wall -DFUSE_USE_VERSION=26")

add_definitions(${COMPILE_FLAGS})

add_executable(mount.myfs ${MOUNT} src/myinmemoryfs.cpp includes/myinmemoryfs.h)
add_executable(unittests ${UNITTESTS} src/myinmemoryfs.cpp includes/myinmemoryfs.h)

find_package(PkgConfig)
pkg_check_modules(FUSE fuse)

target_link_libraries(mount.myfs ${FUSE_LDFLAGS})
target_compile_options(mount.myfs PUBLIC ${FUSE_CFLAGS})
target_include_directories(mount.myfs PUBLIC ${FUSE_INCLUDE_DIRS})

target_link_libraries(unittests ${FUSE_LDFLAGS})
target_compile_options(unittests PUBLIC ${FUSE_CFLAGS})
target_include_directories(unittests PUBLIC ${FUSE_INCLUDE_DIRS})
