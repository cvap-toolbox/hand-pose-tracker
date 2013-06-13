cmake_minimum_required(VERSION 2.6)
enable_testing()
cmake_policy(SET CMP0014 OLD)
set (CMAKE_BUILD_TYPE DEBUG)
#set (CMAKE_BUILD_TYPE RELWITHDEBINFO)
#set (CMAKE_BUILD_TYPE RELEASE)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
#set(CMAKE_CXX_FLAGS " -O0 -g -std=c++0x -msse -msse2 -msse3 -Wall -Wextra -Winit-self -Wpointer-arith -Wno-sign-compare -Wcast-qual -Wno-unused-parameter -Wno-uninitialized -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wsign-promo ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS " -O3 -g -std=gnu++0x -msse -msse2 -msse3 -Wall -Wextra -Winit-self -Wpointer-arith -Wno-sign-compare -Wcast-qual -Wno-unused-parameter -Wno-uninitialized -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wsign-promo -lboost_filesystem ${CMAKE_CXX_FLAGS}")
set (SOURCES_DIR_LSHKIT ${CMAKE_SOURCE_DIR}/3rdparty/lshkit-0.2.1)
set (SOURCES_DIR_ANN ${CMAKE_SOURCE_DIR}/3rdparty/ann_1.1.2)
set (SOURCES_DIR_FIGTREE ${CMAKE_SOURCE_DIR}/3rdparty/figtree-0.9.3)
set (SCENE_PATH ${CMAKE_SOURCE_DIR}/scene)

set(DATA_BASEPATH ${CMAKE_SOURCE_DIR} CACHE STRING "")

set(FLANN_BIN_PATH ${DATA_BASEPATH}/flann.bin CACHE FILEPATH "Write the path to the flann binary file" )
set(FLANN_INDEX_PATH ${DATA_BASEPATH}/flann.idx CACHE FILEPATH "Write the path to the flann index file")
set(LSH_BIN_PATH ${DATA_BASEPATH}/data.bin CACHE FILEPATH "Write the path to the lsh binary file" )
set(LSH_INDEX_PATH ${DATA_BASEPATH}/data.idx CACHE FILEPATH "Write the path to the lsh index file")
set(DB_PATH ${DATA_BASEPATH}/hands.db CACHE FILEPATH "Write the path to the SQL DB path")

configure_file(${CMAKE_SOURCE_DIR}/handclass_config.h.in ${CMAKE_SOURCE_DIR}/include/handclass_config.h)

include (FindPkgConfig)
find_package(Boost REQUIRED)
find_package(Boost COMPONENTS regex filesystem system)
find_package(GSL REQUIRED)
pkg_check_modules ( OPENCV REQUIRED opencv)

if(WIN32)
    set(CMAKE_MODULE_PATH "$ENV{OGRE_HOME}/CMake/;${CMAKE_MODULE_PATH}")
    set(OGRE_SAMPLES_INCLUDEPATH
            $ENV{OGRE_HOME}/Samples/include
       )
endif(WIN32)

if(UNIX)
    if(EXISTS "/usr/local/lib/OGRE/cmake")

    set(CMAKE_MODULE_PATH "/usr/local/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
    set(OGRE_SAMPLES_INCLUDEPATH "/usr/local/share/OGRE/samples/Common/include/") # We could just *assume* that developers uses this basepath : /usr/local

    endif(EXISTS "/usr/local/lib/OGRE/cmake")
    
    if(EXISTS "/usr/lib/OGRE/cmake")

    set(CMAKE_MODULE_PATH "/usr/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
    set(OGRE_SAMPLES_INCLUDEPATH "/usr/share/OGRE/samples/Common/include/") # Otherwise, this one

    endif(EXISTS "usr/lib/OGRE/cmake")

else ()
    message(SEND_ERROR "Failed to find module path.")
endif(UNIX)

    if (CMAKE_BUILD_TYPE STREQUAL "")
# CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
# differentiation between debug and release builds.
    set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()

    set(CMAKE_DEBUG_POSTFIX "_d")

    set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/dist")

find_package(OGRE REQUIRED)


include_directories (${CMAKE_SOURCE_DIR}/include
    /usr/include/eigen3
    ${OPENCV_INCLUDE_DIRS} ${SOURCES_DIR_CVBLOBS}
    ${CMAKE_BINARY_DIR}
    ${SOURCES_DIR_UDPSOCKET}
    ${SOURCES_DIR_LSHKIT}/include
    ${SOURCES_DIR_FIGTREE}/include)

link_directories(${SOURCES_DIR_FIGTREE}/lib)

add_subdirectory(${SOURCES_DIR_FIGTREE})
add_subdirectory(${SOURCES_DIR_LSHKIT})
add_subdirectory(src)
add_subdirectory(apps)
add_subdirectory(scene)
add_subdirectory(tests)
