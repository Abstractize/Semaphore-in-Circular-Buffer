cmake_minimum_required(VERSION 3.0.0)
project(Productor VERSION 0.1.0)

include(CTest)
enable_testing()
file(GLOB SOURCES 
    src/*.c 
    src/*.h 
    src/**/*.h 
    src/**/*.c
)

add_executable(Productor ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(Productor PRIVATE Threads::Threads m)
target_compile_definitions(Productor PRIVATE PROJECT_NAME=${PROJECT_NAME})

include(CPack)
