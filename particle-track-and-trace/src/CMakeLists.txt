cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(ParticleTrackTrace)

include(CMakePrintHelpers)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(VTK COMPONENTS
  GeovisCore
  CommonColor
  CommonCore
  CommonDataModel
  FiltersGeneral
  FiltersGeometry
  FiltersTexture
  FiltersProgrammable
  FiltersSources
  ImagingSources
  ImagingGeneral
  ImagingCore
  InteractionStyle
  IOImage
  RenderingContextOpenGL2
  RenderingCore
  RenderingCore
  RenderingFreeType
  RenderingGL2PSOpenGL2
  RenderingOpenGL2)


if (NOT VTK_FOUND)
  message(FATAL_ERROR "VtkBase: Unable to find the VTK build folder.")
endif()

# netcdf setup
# find_package(netCDF REQUIRED)

# include(FetchContent)
# FetchContent_Declare(SFML
#         GIT_REPOSITORY https://github.com/SFML/SFML.git
#         GIT_TAG 2.5.x
#         FIND_PACKAGE_ARGS NAMES SFML COMPONENTS system window audio main)
# FetchContent_MakeAvailable(SFML)

find_package(SFML COMPONENTS system window audio)

add_executable(ParticleTrackTrace MACOSX_BUNDLE main.cpp
        layers/BackgroundImage.cpp
        layers/BackgroundImage.h
        layers/EulerGlyphs.cpp
        layers/EulerGlyphs.h
        layers/Layer.cpp
        layers/Layer.h
        layers/LagrangeGlyphs.cpp
        layers/LagrangeGlyphs.h
        Program.cpp
        Program.h
        commands/TimerCallbackCommand.h
        commands/TimerCallbackCommand.cpp
        commands/SpawnPointCallback.h
        commands/SpawnPointCallback.cpp
        commands/CameraMoveCallback.cpp
        commands/CameraMoveCallback.h
        CartographicTransformation.cpp
        advection/kernel/AdvectionKernel.h
        advection/kernel/EulerAdvectionKernel.cpp
        advection/kernel/EulerAdvectionKernel.h
        advection/interpolate.cpp
        advection/interpolate.h
        advection/readdata.cpp
        advection/readdata.h
        advection/kernel/RK4AdvectionKernel.cpp
        advection/kernel/RK4AdvectionKernel.h
        advection/UVGrid.cpp
        advection/UVGrid.h
        advection/Vel.cpp
        advection/Vel.h
        advection/kernel/SnapBoundaryConditionKernel.h
        advection/kernel/SnapBoundaryConditionKernel.cpp
        layers/Character.h
        layers/Character.cpp
        commands/CharacterMoveCallback.h
        commands/CharacterMoveCallback.cpp
        layers/ParticleCollision.h
        layers/ParticleCollision.cpp
        collisions/ParticleCollisionCallback.h
        collisions/DummyCollisionHandler.h
        collisions/DummyCollisionHandler.cpp
        layers/Vessels.h
        layers/Vessels.cpp
        vesselroutes/VesselRoute.h
        vesselroutes/QuadraticBezierRoute.cpp
        vesselroutes/QuadraticBezierRoute.h
        vesselroutes/VesselRouteFactory.cpp
        vesselroutes/VesselRouteFactory.h
        layers/FoodSpawner.cpp
        layers/FoodSpawner.h
        collisions/ParticleRemover.cpp
        collisions/ParticleRemover.h
        vesselroutes/StraightLineRoute.cpp
        vesselroutes/StraightLineRoute.h
        layers/Health.cpp
        layers/Health.h
        layers/Health.h
        collisions/FoodPickup.cpp
        collisions/FoodPickup.h
        collisions/DebrisPickup.cpp
        collisions/DebrisPickup.h
        layers/Camera.cpp
        layers/Camera.h
        layers/GameOverScreen.cpp
        layers/GameOverScreen.h
        gameovers/GameoverCallback.h
        layers/Timer.cpp
        layers/Timer.h
        commands/DismissGameoverScreen.cpp
        commands/DismissGameoverScreen.h
        layers/DayCounter.cpp
        layers/DayCounter.h
        layers/Badges.cpp
        layers/Badges.h
        badges/Badge.h
        badges/Badge.cpp
        badges/StaticBadge.cpp
        badges/StaticBadge.h
        statistics/Statistic.h
        collisions/TrackedCollision.cpp
        collisions/TrackedCollision.h
        badges/Achievement.h
        badges/SimpleAchievement.cpp
        badges/SimpleAchievement.h
        badges/FileBadgeFactory.cpp
        badges/FileBadgeFactory.h
        layers/StatisticsManager.cpp
        layers/StatisticsManager.h
        statistics/Statistic.cpp
        layers/BadgeCounter.cpp
        layers/BadgeCounter.h
        layers/BadgeCounter.h
        statistics/BadgesAcquired.cpp
        statistics/BadgesAcquired.h
        badges/TrackedAchievement.cpp
        badges/TrackedAchievement.h
        commands/CharacterMouseMoveCallback.cpp
        commands/CharacterMouseMoveCallback.h
        layers/CharacterNoStop.h
        layers/CharacterNoStop.cpp
        collisions/SoundEffect.cpp
        collisions/SoundEffect.h
        layers/SplashScreen.cpp
        layers/SplashScreen.h
        commands/DisplaySplashScreenCommand.cpp
        commands/DisplaySplashScreenCommand.h
        commands/DisplayEulerCommand.cpp
        commands/DisplayEulerCommand.h
        commands/UserStudyTimer.h
        commands/UserStudyTimer.cpp
        layers/UserStudyTimerInitialiser.cpp
        layers/UserStudyTimerInitialiser.h
)

SET(Boost_DIR ${Boost_DIR} CACHE PATH "Boost head directory")
SET(Boost_INCLUDE_DIR ${Boost_INCLUDE_DIR} CACHE PATH "Boost's parent include directory")
SET(Boost_LIBRARY_DIR_RELEASE ${Boost_LIBRARY_DIR_RELEASE} CACHE PATH "Boost library directory (release objects)")
SET(Boost_LIBRARY_DIR_DEBUG ${Boost_LIBRARY_DIR_DEBUG} CACHE PATH "Boost library directory (debug objects)")
if(WIN32)
  #set(Boost_USE_STATIC_LIBS        ON) # only find static libs
  set(Boost_USE_MULTITHREADED      ON)
  set(Boost_USE_STATIC_RUNTIME    OFF)
#   find_package(Boost COMPONENTS regex filesystem system thread program_options REQUIRED)
# else()
#   find_package(Boost REQUIRED)
endif()
# find_package(Boost COMPONENTS regex filesystem system thread program_options REQUIRED)
find_package(Boost COMPONENTS program_options REQUIRED)

if(Boost_FOUND)
  list(APPEND ADDITIONAL_LIBRARY_PATHS ${BOOST_LIBRARYDIR})
  #list(APPEND LIBRARIES ${Boost_LIBRARIES})
  set(Boost_SUBSYSTEM "")
  if(WIN32)
    # list(APPEND Boost_SUBSYSTEM ${Boost_SYSTEM_LIBRARY})
    # list(APPEND Boost_SUBSYSTEM ${Boost_FSYSTEM_LIBRARY})
    # list(APPEND Boost_SUBSYSTEM ${Boost_REGEX_LIBRARY})
    # list(APPEND Boost_SUBSYSTEM ${Boost_THREAD_LIBRARY})
    list(APPEND Boost_SUBSYSTEM ${Boost_POPTIONS_LIBRARY})
  else()
    # list(APPEND Boost_SUBSYSTEM boost_system)
    # list(APPEND Boost_SUBSYSTEM boost_filesystem)
    # list(APPEND Boost_SUBSYSTEM boost_regex)
    # list(APPEND Boost_SUBSYSTEM boost_thread)
    list(APPEND Boost_SUBSYSTEM boost_program_options)
  endif()
  list(APPEND LIBRARIES ${Boost_SUBSYSTEM})
  list(APPEND INCLUDE_DIRS ${Boost_INCLUDE_DIR})
  link_directories(${BOOST_LIBRARYDIR})
  link_libraries(${Boost_LIBRARIES} ${Boost_SUBSYSTEM})
endif(Boost_FOUND)


execute_process(
    COMMAND nc-config --includedir
    OUTPUT_VARIABLE netCDF_INCLUDE_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
    COMMAND ncxx4-config --prefix
    OUTPUT_VARIABLE NETCDFCXX_LIB_PREFIX
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

target_include_directories(ParticleTrackTrace PUBLIC ${netCDF_INCLUDE_DIR} ${Boost_INCLUDE_DIR})

cmake_print_variables(netCDF_INCLUDE_DIR "${NETCDFCXX_LIB_PREFIX}/lib" "${NETCDFCXX_LIB_PREFIX}/lib/x86_64-linux-gnu" NETCDF_LIBRARY)

find_library(NETCDF_LIBRARY NAMES netcdf-cxx4 netcdf_c++4 PATHS "${NETCDFCXX_LIB_PREFIX}/lib" "${NETCDFCXX_LIB_PREFIX}/lib/x86_64-linux-gnu" NO_DEFAULT_PATH)
get_filename_component(NETCDFCXX_LIB_DIR ${NETCDF_LIBRARY} DIRECTORY)
get_filename_component(NETCDFCXX_LIBNAME ${NETCDF_LIBRARY} NAME_WE)

cmake_print_variables(netCDF_INCLUDE_DIR NETCDFCXX_LIB_DIR NETCDF_LIBRARY NETCDFCXX_LIBNAME)

# Prevent a "command line is too long" failure in Windows.
set(CMAKE_NINJA_FORCE_RESPONSE_FILE "ON" CACHE BOOL "Force Ninja to use response files.")
target_link_libraries(ParticleTrackTrace ${NETCDF_LIBRARY} ${VTK_LIBRARIES} sfml-audio ${Boost_LIBRARIES})

# vtk_module_autoinit is needed
vtk_module_autoinit(
  TARGETS ParticleTrackTrace
  MODULES ${VTK_LIBRARIES}
)

if(WIN32)
add_custom_command(
        TARGET main
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM)
endif()

# == INSTALL routine ==
message( STATUS "Installation root directory: ${CMAKE_INSTALL_PREFIX}")
install( TARGETS ParticleTrackTrace )
