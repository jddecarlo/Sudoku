# find the source files
file(GLOB SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

#find the header files
file(GLOB HEADER_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)

# add the library
add_library(SudokuCommon SHARED ${SOURCE_FILES} ${HEADER_FILES})

# Let's set compiler-specific flags
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # G++
    target_compile_options(SudokuCommon PRIVATE -Wall -Wextra)	
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # MSVC
    target_compile_options(SudokuCommon PRIVATE /EHsc /MTd /W2 /c)
    target_compile_definitions(SudokuCommon PRIVATE COMMON_EXPORT)
endif()
