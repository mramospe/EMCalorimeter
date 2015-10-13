#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(EMCAL)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

#----------------------------------------------------------------------------
# Locates the Root package
find_package(ROOT REQUIRED)
include_directories(${ROOT_INCLUDE_DIR})

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Compiles the sources atending to the root libaries' properties
add_library(EMCalClasses SHARED ${sources})
set(libsuffix .so)
set(ROOT_LIBRARY_PROPERTIES ${ROOT_LIBRARY_PROPERTIES} SUFFIX ${libsuffix})
set_target_properties(EMCalClasses PROPERTIES ${ROOT_LIBRARY_PROPERTIES})

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 and Root libraries
add_executable(EMCalorimeter EMCalorimeter.cc ${sources} ${headers})
target_link_libraries(EMCalorimeter EMCalClasses ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build EMCal. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
set(EMCAL_SCRIPTS
  physics_lists.mac
  init_vis.mac
  vis.mac
  run_example.mac
  )

foreach(_script ${EMCAL_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# For internal Geant4 use - but has no effect if you build it standalone
add_custom_target(EMCAL DEPENDS EMCalorimeter)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
install(TARGETS EMCalorimeter DESTINATION bin)

#----------------------------------------------------------------------------
# Sets the compiler flags
set( CMAKE_CXX_FLAGS "-Wall" )


