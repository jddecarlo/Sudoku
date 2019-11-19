# find the source files
file(GLOB SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

#find the header files
file(GLOB HEADER_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)

# add the library
add_library(SudokuGame ${SOURCE_FILES} ${HEADER_FILES})
add_dependencies(SudokuGame SudokuCommon)

# add the directories to search for header files
target_include_directories(SudokuGame PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/SudokuCommon"
                          )