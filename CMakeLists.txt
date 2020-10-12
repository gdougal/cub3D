cmake_minimum_required(VERSION 3.12)
project(untitled C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "-Lmlx -lmlx -framework OpenGL -framework AppKit")

link_directories(/usr/local/lib libft gnl include)
include_directories(/usr/local/include libft gnl include)

file(GLOB lib_src "${PROJECT_SOURCE_DIR}/libft/*.c")
file(GLOB gnl_src "${PROJECT_SOURCE_DIR}/gnl/*.c")
#file(GLOB LIBRARIES "${PROJECT_SOURCE_DIR}/minilibx_/libmlx.dylib")
#message("LIBRARIES = ${LIBRARIES}")

add_executable(untitled
        parser.c
        window.c
        ${lib_src}
        ${gnl_src}
        include/struct.h init_struct/init_struct.c include/render.h render.c)
#target_link_libraries(untitled ${LIBRARIES})