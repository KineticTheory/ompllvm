cmake_minimum_required(VERSION 3.18.0 FATAL_ERROR)
project( ompllvm CXX )

# ----- compiler options ----------------------------------------------
string(APPEND CMAKE_C_FLAGS " -openmp:llvm")
set( CMAKE_C_FLAGS_DEBUG "/MDd /RTC1 /Od /Zi")
set( CMAKE_C_FLAGS_RELEASE "/MD /O2")

string(REPLACE "/EHs" "/EHa" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
string( APPEND CMAKE_CXX_FLAGS " ${CMAKE_C_FLAGS} /Zc:__cplusplus" )
set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}" )
set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}" )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR} )

# ----- build code ----------------------------------------------------
add_executable( tstomp tstomp.cc )
set_target_properties( tstomp PROPERTIES 
  CXX_STANDARD 14       
  CXX_EXTENSIONS OFF
  CXX_STANDARD_REQUIRED ON 
  INTERPROCEDURAL_OPTIMIZATION_RELEASE OFF
  POSITION_INDEPENDENT_CODE ON )
