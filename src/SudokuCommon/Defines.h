// Copyright (c) Jonathan DeCarlo.
// Licensed under the MIT license.

#pragma once

// Define EXPORTED for any platform
#if defined _WIN32 || defined __CYGWIN__
#ifdef COMMON_EXPORT
  // Exporting...
#ifdef __GNUC__
#define EXPORTED __attribute__ ((dllexport))
#else
#define EXPORTED __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
#endif
#else
#ifdef __GNUC__
#define EXPORTED __attribute__ ((dllimport))
#else
#define EXPORTED __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
#endif
#endif
#define NOT_EXPORTED
#else
#if __GNUC__ >= 4
#define EXPORTED __attribute__ ((visibility ("default")))
#define NOT_EXPORTED  __attribute__ ((visibility ("hidden")))
#else
#define EXPORTED
#define NOT_EXPORTED
#endif
#endif

#define DECLARE_SMART_PTR(TYPE) typedef std::shared_ptr<TYPE> TYPE##Ptr;
#define CONVERT_TO_SMART_PTR(SMART_PTR_TYPE, VAR_NAME, PTR, RELEASE_FUNC) SMART_PTR_TYPE VAR_NAME(PTR, RELEASE_FUNC)
#define BLANK_CELL 0

#define GET_ROW_START_INDEX(i) (i / 9)
#define GET_COLUMN_START_INDEX(i) (i % 9)
#define GET_SQUARE_INDEX(i) (GET_COLUMN_START_INDEX(i) / 3 + 3 * (GET_ROW_START_INDEX(i) / 3))
#define GET_SQUARE_START_INDEX(i) ((GET_SQUARE_INDEX(i) % 3) * 3 + (GET_SQUARE_INDEX(i) / 3 * 27))
