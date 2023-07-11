project(source)

add_executable(source main.c)
include_directories(../strtoi_itoa_lib)
target_link_libraries(source strtoi_itoa_lib)