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

# Let's set compiler-specific flags
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # G++
    target_compile_options(SudokuGame PRIVATE -Wall -Wextra)	
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # MSVC
	# Debug config compiler options
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
	# Release config compiler options
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	# Cross-configuration compiler options
    target_compile_options(SudokuGame PRIVATE /EHsc /W4 /WX /c)
endif()