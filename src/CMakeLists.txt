cmake_minimum_required(VERSION 3.15)

# set the project name
project(Sudoku VERSION 99.99.99.99)

# To build shared libraries in Windows, we set CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS to TRUE.
# See https://cmake.org/cmake/help/v3.4/variable/CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS.html
# See https://blog.kitware.com/create-dlls-on-windows-without-declspec-using-new-cmake-export-all-feature/
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS OFF)

# have all built output go to bin directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 
	${PROJECT_BINARY_DIR}/bin CACHE
    PATH "Directory where .exe and .dll files are dumped." FORCE)

# add the SudokuCommon library
add_subdirectory(SudokuCommon)

# add the SudokuGame library
add_subdirectory(SudokuGame)

#add the SudokuCLI executable
add_subdirectory(SudokuCLI)

target_link_libraries(SudokuCLI PUBLIC SudokuCommon SudokuGame)
target_link_libraries(SudokuGame PUBLIC SudokuCommon)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
