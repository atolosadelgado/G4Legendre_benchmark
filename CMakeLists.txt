#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.16...3.21)
project(yours)

find_package(benchmark REQUIRED)

# Find Boost headers (only)
find_package(Boost REQUIRED)  # You can optionally add: COMPONENTS math_c99

# Add Boost include directories
include_directories(${Boost_INCLUDE_DIRS})

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
#option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
#if(WITH_GEANT4_UIVIS)
#  find_package(Geant4 REQUIRED ui_all vis_all)
#else()
  find_package(Geant4 REQUIRED)
#endif()
set( CMAKE_BUILD_TYPE Release)
message (" INCLUDES are =  ${Geant4_INCLUDE_DIRS}")

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
# add_executable(benchmark src/*.cc)
add_executable(benchmark src/your_file.cc)
target_link_libraries(benchmark ${Geant4_LIBRARIES} benchmark::benchmark gtest gtest_main)
target_include_directories(benchmark PRIVATE ${Boost_INCLUDE_DIRS})
target_include_directories(benchmark PRIVATE ${Geant4_INCLUDE_DIRS})


