SET(TOOLS fitdata lsh-run mplsh-run apost-run mplsh-predict mplsh-tune sketch-run forest-run scan embed txt2bin dump-query run-spectral createIndex)
# FIND_PACKAGE(Boost COMPONENTS program_options file_system)
FOREACH(TOOL ${TOOLS})
ADD_EXECUTABLE(${TOOL} ${TOOL}.cpp)
TARGET_LINK_LIBRARIES(${TOOL} lshkit ${Boost_LIBRARIES} ${GSL_LIBRARIES})
ENDFOREACH(TOOL)

