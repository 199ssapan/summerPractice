project(source)

add_executable(source main.c)
include_directories(../bigIntLib)
target_link_libraries(source bigIntLib)