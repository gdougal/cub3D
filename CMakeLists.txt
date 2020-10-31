cmake_minimum_required(VERSION 3.12)
project(untitled C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "-Lmlx -lmlx -framework OpenGL -framework AppKit")

link_directories(/usr/local/lib libft gnl include)
include_directories(/usr/local/include libft gnl include)

file(GLOB lib_src "${PROJECT_SOURCE_DIR}/libft/*.c")
file(GLOB gnl_src "${PROJECT_SOURCE_DIR}/gnl/*.c")
file(GLOB list "${PROJECT_SOURCE_DIR}/list_func/*.c")


add_executable(untitled
        Parser/parser.c
        window.c
        ${lib_src}
        ${gnl_src}
#        ${list}
        include/struct.h init_struct/init_struct.c render.c include/render.h include/lists.h Trigonometry/vector_vision.c Sprites/sprites.c)
