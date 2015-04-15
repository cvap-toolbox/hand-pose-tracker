add_executable(chandtracker_gui chandtracker_gui.cpp)
target_link_libraries(chandtracker_gui ${OpenCV_LIBS} ${Boost_LIBRARIES} handclass)

add_executable(hog_gui hog_gui.cpp) 
target_link_libraries(hog_gui ${Boost_LIBRARIES} ${OpenCV_LIBS} handclass)

#add_executable(nn_hogJointsParts nn_hogJointsParts.cpp) 
#target_link_libraries(nn_hogJointsParts boost_system boost_filesystem boost_regex handclass sqlite3 ${GSL_LIBRARIES} lshkit ${OpenCV_LIBS})

add_executable(handTracker handTracker.cpp) 
target_link_libraries(handTracker ${Boost_LIBRARIES} sqlite3 ann_figtree_version figtree handclass lshkit ${OpenCV_LIBS} ${GSL_LIBRARIES})

add_executable(createFeatDB createFeatDB.cpp) 
target_link_libraries(createFeatDB ${Boost_LIBRARIES} handclass sqlite3 ${GSL_LIBRARIES} lshkit ${OpenCV_LIBS})

add_executable(recompute_hog recompute_hog.cpp)
target_link_libraries(recompute_hog ${Boost_LIBRARIES} handclass sqlite3 ${GSL_LIBRARIES} lshkit ${OpenCV_LIBS})

add_executable(test_hog_db test_hog_db.cpp)
target_link_libraries(test_hog_db ${Boost_LIBRARIES} handclass sqlite3 ${GSL_LIBRARIES} lshkit ${OpenCV_LIBS})

add_executable(createRenderDB createRenderDB.cpp) 
target_link_libraries(createRenderDB ${Boost_LIBRARIES} handclass sqlite3 ${GSL_LIBRARIES} lshkit ${OpenCV_LIBS})
