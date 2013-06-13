#Ogre is needed for re-rendering the hand poses.
#include_directories( ${OIS_INCLUDE_DIRS}
#        ${OGRE_INCLUDE_DIRS}
#        ${OGRE_SAMPLES_INCLUDEPATH}
#)

add_executable(renderhand renderhand.cc)
target_link_libraries(renderhand 
boost_system boost_filesystem boost_program_options
opencv_highgui opencv_core opencv_video
#${OGRE_LIBRARIES}
sqlite3 handclass)

