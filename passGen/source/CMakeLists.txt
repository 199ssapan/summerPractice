project(source)

add_executable(source main.c)
include_directories(../passGenLib)
target_link_libraries(source passGenLib)
