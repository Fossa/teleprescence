# - Try to find SRTP
# Once done this will define
#
#  SRTP_FOUND - system has SRTP
#  SRTP_INCLUDE_DIRS - the SRTP include directory
#  SRTP_LIBRARIES - Link these to use SRTP
#  SRTP_DEFINITIONS - Compiler switches required for using SRTP
#
#  Copyright (c) 2014 Karl Johnson <kajo0715@student.miun.se>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#


if (SRTP_LIBRARIES AND SRTP_INCLUDE_DIRS)
  # in cache already
  set(SRTP_FOUND TRUE)
else (SRTP_LIBRARIES AND SRTP_INCLUDE_DIRS)
  # use pkg-config to get the directories and then use these values
  # in the FIND_PATH() and FIND_LIBRARY() calls
  include(UsePkgConfig)

  pkgconfig(libsrtp _SRTPIncDir _SRTPLinkDir _SRTPLinkFlags _SRTPCflags)

  set(SRTP_DEFINITIONS ${_SRTPCflags})

  find_path(SRTP_INCLUDE_DIR
    NAMES
      srtp/srtp.h
    PATHS
      ${_SRTPIncDir}
      /usr/include
      /usr/local/include
      /opt/local/include
      /sw/include
  )

  find_library(SRTP_LIBRARY
    NAMES
      srtp
    PATHS
      ${_SRTPLinkDir}
      /usr/lib
      /usr/local/lib
      /opt/local/lib
      /sw/lib
  )

  set(SRTP_INCLUDE_DIRS
    ${SRTP_INCLUDE_DIR}
  )
  set(SRTP_LIBRARIES
    ${SRTP_LIBRARY}
)

  if (SRTP_INCLUDE_DIRS AND SRTP_LIBRARIES)
     set(SRTP_FOUND TRUE)
  endif (SRTP_INCLUDE_DIRS AND SRTP_LIBRARIES)

  if (SRTP_FOUND)
    if (NOT SRTP_FIND_QUIETLY)
      message(STATUS "Found SRTP: ${SRTP_LIBRARIES}")
    endif (NOT SRTP_FIND_QUIETLY)
  else (SRTP_FOUND)
    if (SRTP_FIND_REQUIRED)
      message(FATAL_ERROR "Could not find SRTP")
    endif (SRTP_FIND_REQUIRED)
  endif (SRTP_FOUND)

  # show the SRTP_INCLUDE_DIRS and SRTP_LIBRARIES variables only in the advanced view
  mark_as_advanced(SRTP_INCLUDE_DIRS SRTP_LIBRARIES)

endif (SRTP_LIBRARIES AND SRTP_INCLUDE_DIRS)

