project(voltdb-post-get-cpp)
cmake_minimum_required(VERSION 2.8)
set(VOLTDB_ROOT ${CMAKE_SOURCE_DIR}/../voltdb-client-cpp-linux-x86_64-3.0)
set(CMAKE_CXX_FLAGS "-g3 -O3")
include_directories(${VOLTDB_ROOT}/include)
include_directories(${CMAKE_SOURCE_DIR})
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})


target_link_libraries(${PROJECT_NAME}
    ${VOLTDB_ROOT}/libvoltdbcpp.a
    ${VOLTDB_ROOT}/libevent_pthreads.a
${VOLTDB_ROOT}/libevent.a
    rt
    pthread)
