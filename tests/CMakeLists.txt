add_executable(chandtracker_test chandtracker_test.cpp)
target_link_libraries(chandtracker_test ${Boost_LIBRARIES} ${OpenCV_LIBS} handclass)

add_executable(hog_test hog_test.cpp) 
target_link_libraries(hog_test ${Boost_LIBRARIES} ${OpenCV_LIBS} handclass)

add_executable(ann_test ann_test.cpp) 
target_link_libraries(ann_test ${Boost_LIBRARIES} ${OpenCV_LIBS} ${GSL_LIBRARIES} lshkit)

add_executable(cDB_test cDB_test.cpp) 
target_link_libraries(cDB_test ${Boost_LIBRARIES} sqlite3 handclass)

add_executable(cPose_test cPose_test.cpp) 
target_link_libraries(cPose_test ${Boost_LIBRARIES} sqlite3 handclass)

add_executable(cPoselistMulti_test cPoselistMulti_test.cpp) 
target_link_libraries(cPoselistMulti_test ${Boost_LIBRARIES} sqlite3 ann_figtree_version figtree handclass)

add_executable(compare_hogdb_hogim compare_hogdb_hogim.cpp) 
target_link_libraries(compare_hogdb_hogim ${Boost_LIBRARIES} sqlite3 ann_figtree_version figtree ${OpenCV_LIBS} handclass)

ADD_TEST(chandtracker_test ${EXECUTABLE_OUTPUT_PATH}/chandtracker_test Hello)
ADD_TEST(hog_test ${EXECUTABLE_OUTPUT_PATH}/hog_test Hello)
ADD_TEST(ann_test ${EXECUTABLE_OUTPUT_PATH}/ann_test Hello)
ADD_TEST(cDB_test ${EXECUTABLE_OUTPUT_PATH}/cDB_test Hello)
ADD_TEST(cPose_test ${EXECUTABLE_OUTPUT_PATH}/cPose_test Hello)
ADD_TEST(cPoselistMulti_test ${EXECUTABLE_OUTPUT_PATH}/cPoselistMulti_test Hello)
