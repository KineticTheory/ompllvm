cmake_minimum_required(VERSION 3.18.0 FATAL_ERROR)
project( ompllvm CXX )

# compiler options

set( CMAKE_GNUtoMS ON CACHE BOOL "Compatibility flag for MinGW/MSVC." FORCE)
set( _USE_MATH_DEFINES 1 )
set( MD_or_MT "MD" )
set( MD_or_MT_debug "MDd /RTC1" )
string(APPEND CMAKE_C_FLAGS " /nologo /Gy /fp:precise /DWIN32 /D_WINDOWS /MP /wd4251" )
string(APPEND CMAKE_C_FLAGS " -openmp:llvm -D__STDC_CONSTANT_MACROS -D_POSIX_C_SOURCE=200112 -D_XOPEN_SOURCE=600")
if(HAVE_HARDWARE_AVX2)
  string(APPEND CMAKE_C_FLAGS " /arch:AVX2")
endif()
set( CMAKE_C_FLAGS_DEBUG "/${MD_or_MT_debug} /Od /Zi /DDEBUG /D_DEBUG" )
set( CMAKE_C_FLAGS_RELEASE "/${MD_or_MT} /O2 /DNDEBUG" )
set( CMAKE_C_FLAGS_MINSIZEREL "/${MD_or_MT} /O1 /DNDEBUG" )
set( CMAKE_C_FLAGS_RELWITHDEBINFO "/${MD_or_MT} /O2 /Zi /DDEBUG" )

if(MSVC_VERSION GREATER 1399)
  string( APPEND CMAKE_C_FLAGS
    " /D_CRT_SECURE_NO_DEPRECATE /D_SCL_SECURE_NO_DEPRECATE /D_SECURE_SCL=0" )
endif()
string(REPLACE "/EHs" "/EHa" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
string( APPEND CMAKE_CXX_FLAGS " ${CMAKE_C_FLAGS} /Zc:__cplusplus" )
set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}" )
set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}" )
set( CMAKE_CXX_FLAGS_MINSIZEREL "/${MD_or_MT} /O1 /DNDEBUG" )
set( CMAKE_CXX_FLAGS_RELWITHDEBINFO "/${MD_or_MT} /O2 /Zi /DDEBUG" )

set( DRACO_LINK_OPTIONS "$<$<CONFIG:DEBUG>:/ignore:4099>")
set(Draco_std_target_props_CXX
  CXX_STANDARD 14              # Force strict C++ 14 standard
  CXX_EXTENSIONS OFF
  CXX_STANDARD_REQUIRED ON )
set(Draco_std_target_props
  INTERPROCEDURAL_OPTIMIZATION_RELEASE OFF
  POSITION_INDEPENDENT_CODE ON )
    
        
include(FeatureSummary)
include(CTest)
enable_testing()
if( "${CMAKE_INSTALL_PREFIX}" STREQUAL "/usr/local" OR
    "${CMAKE_INSTALL_PREFIX}" MATCHES "C:/Program Files" )
   set( CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/../install" )
   get_filename_component( CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}"
    ABSOLUTE )
   set( CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}" CACHE PATH
      "Install path prefix, prepended onto install directories" FORCE)
endif()
mark_as_advanced( EXECUTABLE_OUTPUT_PATH )
mark_as_advanced( LIBRARY_OUTPUT_PATH )
mark_as_advanced( DART_TESTING_TIMEOUT )


set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR} )


if( ${CMAKE_GENERATOR} MATCHES "Visual Studio" )
   option( BUILD_USE_SOLUTION_FOLDERS "Enable grouping of projects in VS" ON )
   set_property( GLOBAL PROPERTY USE_FOLDERS ${BUILD_USE_SOLUTION_FOLDERS} )
endif()


set(DBSCFGDIR "\$<CONFIG>/" CACHE STRING
  "Install subdirectory for multiconfig build tools.")
set(DBSCFGDIR_LIBRARY "\$<CONFIG>/bin" CACHE STRING
  "Shared object library install subdirectory for multiconfig build tools.")
set(DBSCFG_IMPORT_PREFIX
  "$<INSTALL_PREFIX>/$<CONFIG>/include"
  CACHE STRING
  "Prefix hack to properly set path to header files listed in draco-targets cmake.")
foreach( config ${CMAKE_CONFIGURATION_TYPES} )
  file( MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/${config}/include )
endforeach()


set( CMAKE_SKIP_BUILD_RPATH OFF )
set( CMAKE_BUILD_WITH_INSTALL_RPATH OFF )
set( CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib" CACHE PATH
 "RPATH to embed in dynamic libraries and executables when targets are installed." FORCE )
set( CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE )

# Sources
file( GLOB test_sources *.cc )
add_executable( tstomp ${test_sources} )
set_target_properties( tstomp PROPERTIES 
  LINK_OPTIONS ${DRACO_LINK_OPTIONS} 
  ${Draco_std_target_props_CXX}
  ${Draco_std_target_props}
  )
  