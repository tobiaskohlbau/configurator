project(configurator)
cmake_minimum_required(VERSION 3.4)


add_subdirectory(third_party/gflags)

add_executable(${PROJECT_NAME} src/main.cc)
target_include_directories(${PROJECT_NAME} PRIVATE include third_party/json)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
target_link_libraries(${PROJECT_NAME} gflags)
