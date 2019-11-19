# find the source files
file(GLOB SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

#find the header files
file(GLOB HEADER_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)

# add the executable
add_executable(SudokuCLI ${SOURCE_FILES} ${HEADER_FILES})
add_dependencies(SudokuCLI SudokuCommon SudokuGame)

# add the directories to search for header files
target_include_directories(SudokuCLI PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/SudokuCommon"
                          "${PROJECT_SOURCE_DIR}/SudokuGame")
