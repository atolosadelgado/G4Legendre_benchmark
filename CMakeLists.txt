#-------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.16...3.21)
project(yours)
set( CMAKE_BUILD_TYPE Release)

# Use Google test and Google benchmark
find_package(GTest REQUIRED)
find_package(benchmark REQUIRED)

# Boost provides special functions
find_package(Boost REQUIRED)  # You can optionally add: COMPONENTS math_c99

# Geant4 has several implementations of Legendre polynomials
# and associated features (eg pol coefficients)
find_package(Geant4 REQUIRED)
include(${Geant4_USE_FILE})

# CLHEP provides a wrap to GSL special functions
find_package(CLHEP REQUIRED)
find_package(GSL)

#-------------------------------------------------------------------------
# Setup global libraries

link_libraries(
    ${Geant4_LIBRARIES}
    ${CLHEP_LIBRARIES}
    GSL::gsl
    benchmark::benchmark
    GTest::GTest
    GTest::Main
)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS}
    ${Geant4_INCLUDE_DIRS}
    ${CLHEP_INCLUDE_DIRS}
    ${benchmark_INCLUDE_DIRS}
)

#-------------------------------------------------------------------------
# define a dedicated test for each implementation of Legendre polynomial
add_executable(test_all                       src/test_all.cc)
add_executable(test_Boost                     src/test_Boost.cc)
add_executable(test_LegTabP                   src/test_LegTabP.cc)
add_executable(test_LegAutoP                  src/test_LegAutoP.cc)
add_executable(test_CLHEP                     src/test_CLHEP.cc)
add_executable(test_G4PHPFastLegendre         src/test_G4PHPFastLegendre.cc)
add_executable(test_G4NuclNuclDiffuseElastic  src/test_G4NuclNuclDiffuseElastic.cc)
add_executable(test_G4LegendrePolynomial      src/test_G4LegendrePolynomial.cc)
add_executable(test_G4LegendrePolynomialAssoc src/test_G4LegendrePolynomialAssoc.cc)

