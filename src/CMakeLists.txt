cmake_minimum_required(VERSION 3.0)
project(glife_game)

add_executable(glife 
    main.cpp
    life.cpp
    manager.cpp
    reader.cpp
    ext_lib/canvas.cpp
    ext_lib/lodepng.cpp
)
target_include_directories(glife PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/ext_lib
)
target_sources(glife PRIVATE
    life.h
    manager.h
    reader.h
    ext_lib/canvas.h
    ext_lib/common.h
    ext_lib/lodepng.h
)
