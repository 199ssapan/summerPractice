project(source)

add_executable(source main.c)
include_directories(../sortStringsLib)
target_link_libraries(source sortStringsLib)