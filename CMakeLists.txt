cmake_minimum_required( VERSION 3.0 )

project( warp )

# enable modern C++ coding style
enable_language( CXX )

# By default, perform a debug build, modifying a cache variable
if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE "Debug" )
endif()

# Specific clang configuration
if( NOT CMAKE_CXX_FLAGS )
  set( CMAKE_CXX_FLAGS
       "-W -Wall -Wextra -std=c++1z -ftemplate-depth=768" )
endif()

if( NOT CMAKE_CXX_FLAGS_DEBUG )
  set( CMAKE_CXX_FLAGS_DEBUG "-O0 -g" )
endif()

if( NOT CMAKE_CXX_FLAGS_RELEASE )
  set( CMAKE_CXX_FLAGS_RELEASE "-O3" )
endif()

# specify binary directory outputs both for libs and executables
# binary executables
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY
     ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE} )
# shared libraries
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY
     ${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE} )
# static libraries and object files
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY
     ${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE} )

# delegated work in these subdirs
add_subdirectory( ./src )
