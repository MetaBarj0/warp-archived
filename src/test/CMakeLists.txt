# create an executable using the test library
add_executable( warp-test main.cpp
                test.cpp )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../warp )
