# - Try to find VPX
# Once done this will define
#
#  VPX_FOUND - system has VPX
#  VPX_INCLUDE_DIRS - the VPX include directory
#  VPX_LIBRARIES - Link these to use VPX
#  VPX_DEFINITIONS - Compiler switches required for using VPX
#
#  Copyright (c) 2014 Karl Johnson <kajo0715@student.miun.se>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#


if (VPX_LIBRARIES AND VPX_INCLUDE_DIRS)
  # in cache already
  set(VPX_FOUND TRUE)
else (VPX_LIBRARIES AND VPX_INCLUDE_DIRS)
  find_path(VPX_INCLUDE_DIR
    NAMES
      vpx/vp8.h
    PATHS
      /usr/include
      /usr/local/include
      /opt/local/include
      /sw/include
    PATH_SUFFIXES
      vpx
  )

  find_library(VPX_LIBRARY
    NAMES
      vpx
    PATHS
      /usr/lib
      /usr/local/lib
      /opt/local/lib
      /sw/lib
  )

  set(VPX_INCLUDE_DIRS
    ${VPX_INCLUDE_DIR}
  )
  set(VPX_LIBRARIES
    ${VPX_LIBRARY}
)

  if (VPX_INCLUDE_DIRS AND VPX_LIBRARIES)
     set(VPX_FOUND TRUE)
  endif (VPX_INCLUDE_DIRS AND VPX_LIBRARIES)

  if (VPX_FOUND)
    if (NOT VPX_FIND_QUIETLY)
      message(STATUS "Found VPX: ${VPX_LIBRARIES}")
    endif (NOT VPX_FIND_QUIETLY)
  else (VPX_FOUND)
    if (VPX_FIND_REQUIRED)
      message(FATAL_ERROR "Could not find VPX")
    endif (VPX_FIND_REQUIRED)
  endif (VPX_FOUND)

  # show the VPX_INCLUDE_DIRS and VPX_LIBRARIES variables only in the advanced view
  mark_as_advanced(VPX_INCLUDE_DIRS VPX_LIBRARIES)

endif (VPX_LIBRARIES AND VPX_INCLUDE_DIRS)

