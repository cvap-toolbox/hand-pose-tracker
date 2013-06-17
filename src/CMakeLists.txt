add_library(handclass chandtracker.cpp cDB.cpp utils.cpp cPoselistMulti.cpp cTemporalFilter.cpp cDBelement.cpp) 
target_link_libraries(handclass
${Boost_FILESYSTEM_LIBRARY}
${Boost_SYSTEM_LIBRARY}
${Boost_REGEX_LIBRARY}
${SOURCES_DIR_FIGTREE}/lib/libfigtree.so
${OpenCV_LIBS}
${OPENCV_LDFLAGS}
opencv_imgproc
#/usr/local/lib/libopencv_imgproc.so
)
MESSAGE(STATUS "OPENCV_LIBS:" ${OPENCV_LIBS})

