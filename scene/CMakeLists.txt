#Ogre is needed for re-rendering the hand poses.
#include_directories( ${OIS_INCLUDE_DIRS}
#        ${OGRE_INCLUDE_DIRS}
#        ${OGRE_SAMPLES_INCLUDEPATH}
#)

add_executable(renderhand renderhand.cc)
add_executable(convert convert.cpp)
target_link_libraries(renderhand ${Boost_LIBRARIES} ${OpenCV_LIBS}
#${OGRE_LIBRARIES}
sqlite3 handclass
)

