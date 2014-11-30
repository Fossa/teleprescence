cmake_minimum_required(VERSION 2.6)
include(ExternalProject)

macro(join_arguments var)
   set(_var)
   foreach(_v ${${var}})
     set(_var "${_var}${_v}")
   endforeach(_v ${${var}})
   string(STRIP ${_var} _var)
   set(${var} ${_var})
endmacro(join_arguments)

function(JOIN VALUES GLUE OUTPUT)
  string (REGEX REPLACE "([^\\]|^);" "\\1${GLUE}" _TMP_STR "${VALUES}")
  string (REGEX REPLACE "[\\](.)" "\\1" _TMP_STR "${_TMP_STR}") #fixes escaping
  set (${OUTPUT} "${_TMP_STR}" PARENT_SCOPE)
endfunction()

# Path for 3rd party find modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/3rd-party")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

# set the install path, Default is /usr/local/bin
set (CMAKE_INSTALL_PREFIX "${PROJECT_BINARY_DIR}/install_dir")
message("install prefix: ${CMAKE_INSTALL_PREFIX}")

# find_package(SPEEX REQUIRED)
# find_package(FFMPEG REQUIRED)
# find_package(SRTP REQUIRED)
# find_package(VPX REQUIRED)

# message("SPEEX_FOUND: ${SPEEX_FOUND}")
# message("SPEEX_INCLUDE_DIR: ${SPEEX_INCLUDE_DIR}")
# message("SPEEX_LIBRARY: ${SPEEX_LIBRARY}")
# message("FFMPEG_FOUND: ${FFMPEG_FOUND}")
# message("FFMPEG_INCLUDE_DIR: ${FFMPEG_INCLUDE_DIR}")
# message("FFMPEG_LIBRARIES: ${FFMPEG_LIBRARIES}")
# message("SRTP_FOUND: ${SRTP_FOUND}")
# message("SRTP_INCLUDE_DIR: ${SRTP_INCLUDE_DIR}")
# message("SRTP_LIBRARIES: ${SRTP_LIBRARIES}")
# message("VPX_FOUND: ${VPX_FOUND}")
# message("VPX_INCLUDE_DIR: ${VPX_INCLUDE_DIR}")
# message("VPX_LIBRARIES: ${VPX_LIBRARIES}")


if(BUILD_264 OR BUILD_ALL)
	set(X264_PREFIX x264)
	ExternalProject_Add(
		x264
		PREFIX ${X264_PREFIX}
		URL http://download.videolan.org/pub/x264/snapshots/last_x264.tar.bz2
		CONFIGURE_COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${FFMPEG_PREFIX}/configure --prefix=${CMAKE_INSTALL_PREFIX} 
	)
endif(BUILD_264 OR BUILD_ALL)

if(BUILD_YUV OR BUILD_ALL)
	set(YUV_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR}/yuv-prefix/src/yuv/)
	ExternalProject_Add(
		yuv
		SVN_REPOSITORY http://libyuv.googlecode.com/svn/trunk
		CMAKE_ARGS
			-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
      -DCFLAGS=-Wl,--whole-archive
      -DCXXFLAGS=-Wl,--whole-archive
    #BUILD_COMMAND ${CMAKE_COMMAND} -E chdir ${YUV_SRC_DIR} make -j6 V=1 -r libyuv BUILDTYPE=Release
	)
	ExternalProject_Add_Step(
		yuv cp_head
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_INSTALL_PREFIX}/include/libyuv.h ${CMAKE_INSTALL_PREFIX}/include/libyuv/libyuv.h
		DEPENDEES install
	)
endif(BUILD_YUV OR BUILD_ALL)

if(BUILD_OPENCORE OR BUILD_ALL)
	set(OPENCORE_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR}/opencore-prefix/src/opencore)
	ExternalProject_Add(
		opencore
		GIT_REPOSITORY git://git.code.sf.net/p/opencore-amr/code
		GIT_TAG v0.1.3
		CONFIGURE_COMMAND ${SHELL_EXECUTABLE} ${OPENCORE_SRC_DIR}/configure --prefix=${CMAKE_INSTALL_PREFIX}
	)
	ExternalProject_Add_Step(
		opencore autoreconf
		COMMAND ${CMAKE_COMMAND} -E chdir ${OPENCORE_SRC_DIR} autoreconf -i
		DEPENDEES patch
		DEPENDERS configure
	)
endif(BUILD_OPENCORE OR BUILD_ALL)

if(BUILD_OPUS OR BUILD_ALL)
	set(OPUS_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR}/opus-prefix/src/opus)
	ExternalProject_Add(
		opus
		URL http://downloads.xiph.org/releases/opus/opus-1.0.2.tar.gz
		CONFIGURE_COMMAND ${SHELL_EXECUTABLE} ${OPUS_SRC_DIR}/configure --with-pic --enable-float-approx --prefix=${CMAKE_INSTALL_PREFIX}
	)
endif(BUILD_OPUS OR BUILD_ALL)

if(BUILD_SPEEX OR BUILD_ALL)
	set(SPEEX_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR}/speex-prefix/src/speex)
	ExternalProject_Add(
		speex
		URL http://downloads.xiph.org/releases/speex/speex-1.2beta3.tar.gz
		CONFIGURE_COMMAND ${SHELL_EXECUTABLE} ${SPEEX_SRC_DIR}/configure --disable-oggtest --without-libogg --prefix=${CMAKE_INSTALL_PREFIX}
	)
endif(BUILD_SPEEX OR BUILD_ALL)

if(BUILD_GSM OR BUILD_ALL)
	set(GSM_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR}/gsm-prefix/src/gsm)
	ExternalProject_Add(
		gsm
		URL http://www.quut.com/gsm/gsm-1.0.13.tar.gz
		CONFIGURE_COMMAND ""
		BUILD_COMMAND ${CMAKE_COMMAND} -E chdir ${GSM_SRC_DIR} make
		INSTALL_COMMAND ${CMAKE_COMMAND} -E chdir ${GSM_SRC_DIR} make install
	)
	ExternalProject_Add_Step(
		gsm cp_files
		COMMAND ${CMAKE_COMMAND} -E copy ${GSM_SRC_DIR}/lib/libgsm.a ${CMAKE_INSTALL_PREFIX}/lib/
		COMMAND ${CMAKE_COMMAND} -E copy ${GSM_SRC_DIR}/inc/gsm.h ${CMAKE_INSTALL_PREFIX}/include/
		DEPENDEES install
	)
endif(BUILD_GSM OR BUILD_ALL)



if(BUILD_G729 OR BUILD_ALL)
	set(G729_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR}/g729-prefix/src/g729)
  set(G729_BAD_LSF_PATCH 
"--- dec_ld8a.c 2014-11-20 16:00:36.693377956 +0100\n"
"+++ dec_ld8a.c  2014-11-20 16:04:23.554502899 +0100\n"
"@@ -136,7 +136,7 @@\n"
"   Word32  L_temp\;\r\n"
" \r\n"
"   Word16 bad_pitch\;             /* bad pitch indicator */\r\n"
"-  extern Word16 bad_lsf\;        /* bad LSF indicator   */\r\n"
"+  Word16 bad_lsf\;        /* bad LSF indicator   */\r\n"
" \r\n"
"   /* for G.729B */\r\n"
"   Word16 ftyp\;\r\n"
"\n"
)

  message(${G729_BAD_LSF_PATCH})
  file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/bad_lsf.patch ${G729_BAD_LSF_PATCH})

  ExternalProject_Add(
		g729
		SVN_REPOSITORY http://g729.googlecode.com/svn/trunk/
		# https://code.google.com/p/g729/issues/detail?id=3
		PATCH_COMMAND patch -f -d ${G729_SRC_DIR} -p1 --ignore-whitespace --verbose dec_ld8a.c -i bad_lsf.patch || true
		CONFIGURE_COMMAND ${SHELL_EXECUTABLE} ${G729_SRC_DIR}/configure --enable-static --disable-shared --prefix=${CMAKE_INSTALL_PREFIX}
	)
	
	set(G729_PATCH1_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR}/g729_patch1-prefix/src/g729_patch1)
	ExternalProject_Add_Step(
		g729 cp_patch
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/bad_lsf.patch ${G729_SRC_DIR}/bad_lsf.patch
    DEPENDEES update
    DEPENDERS patch
	)
	ExternalProject_Add_Step(
		g729 autogen
		COMMAND ${CMAKE_COMMAND} -E chdir ${G729_SRC_DIR} autogen.sh
		DEPENDEES patch
		DEPENDERS configure
	)
	ExternalProject_Add_Step(
		g729 install_include
		COMMAND ${CMAKE_COMMAND} -E copy ${G729_SRC_DIR}/typedef.h ${CMAKE_INSTALL_PREFIX}/include/g729b/
		COMMAND ${CMAKE_COMMAND} -E copy ${G729_SRC_DIR}/ld8a.h ${CMAKE_INSTALL_PREFIX}/include/g729b/
    COMMAND ${CMAKE_COMMAND} -E copy ${G729_SRC_DIR}/dtx.h ${CMAKE_INSTALL_PREFIX}/include/g729b/
    COMMAND ${CMAKE_COMMAND} -E copy ${G729_SRC_DIR}/octet.h ${CMAKE_INSTALL_PREFIX}/include/g729b/
		DEPENDEES install
	)
endif(BUILD_G729 OR BUILD_ALL)

if(BUILD_iLBC OR BUILD_ALL)
  set(iLBC_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR}/iLBC-prefix/src/iLBC)
  file(DOWNLOAD http://www.ietf.org/rfc/rfc3951.txt ${CMAKE_CURRENT_BINARY_DIR}/rfc3951.txt)
  ExternalProject_Add(
    iLBC
    SVN_REPOSITORY http://doubango.googlecode.com/svn/branches/2.0/doubango/thirdparties/scripts/ilbc
    CONFIGURE_COMMAND ${SHELL_EXECUTABLE} ${iLBC_SRC_DIR}/configure --prefix=${CMAKE_INSTALL_PREFIX}
  )
  ExternalProject_Add_Step(
    iLBC awk
    COMMAND 
      ${CMAKE_COMMAND} -E chdir 
        ${iLBC_SRC_DIR} 
        awk -f extract.awk ${CMAKE_CURRENT_BINARY_DIR}/rfc3951.txt
    DEPENDEES patch
  )
  ExternalProject_Add_Step(
    iLBC autogen
    COMMAND ${CMAKE_COMMAND} -E chdir ${iLBC_SRC_DIR} autogen.sh
    DEPENDEES awk
    DEPENDERS configure
  )
  ExternalProject_Add_Step(
    iLBC install_include
    COMMAND ${CMAKE_COMMAND} -E copy ${iLBC_SRC_DIR}/iLBC_define.h ${CMAKE_INSTALL_PREFIX}/include/ilbc/
    COMMAND ${CMAKE_COMMAND} -E copy ${iLBC_SRC_DIR}/iLBC_encode.h ${CMAKE_INSTALL_PREFIX}/include/ilbc/
    COMMAND ${CMAKE_COMMAND} -E copy ${iLBC_SRC_DIR}/iLBC_decode.h ${CMAKE_INSTALL_PREFIX}/include/ilbc/
    DEPENDEES install
  )
endif(BUILD_iLBC OR BUILD_ALL)

if(BUILD_FFMPEG OR BUILD_ALL)
	set(FFMPEG_PREFIX ffmpeg)
	set(FFMPEG_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR}/${FFMPEG_PREFIX}/src/ffmpeg/)
	set(FFMPEG_CONF_FLAGS --extra-cflags="-fPIC" 
												--extra-ldflags="-lpthread"
												--enable-pic
												--enable-memalign-hack
												--enable-pthreads
												--enable-shared
												--disable-static
												--disable-network
												--enable-pthreads
												--disable-ffmpeg
												--disable-ffplay
												--disable-ffserver
												--disable-ffprobe
												--enable-gpl
												--enable-nonfree
												--disable-debug
												--enable-libx264
												--enable-encoder=libx264
												--enable-decoder=h264
												--enable-encoder=h263
												--enable-encoder=h263p
												--enable-decoder=h263
												--enable-libtheora
												--enable-encoder=libtheora
												--enable-decoder=theora
												--enable-encoder=mpeg4
												--enable-decoder=mpeg4
	)
	ExternalProject_Add(
		ffmpeg
		PREFIX ffmpeg
		#DOWNLOAD
		#GIT_REPOSITORY git://source.ffmpeg.org/ffmpeg.git
		GIT_REPOSITORY https://github.com/FFmpeg/FFmpeg.git
		GIT_TAG release/1.2
		#CONFIGURE
		CONFIGURE_COMMAND ${SHELL_EXECUTABLE} ${FFMPEG_SRC_DIR}/configure ${FFMPEG_CONF_FLAGS} --prefix=${CMAKE_INSTALL_PREFIX}
		#INSTALL
		# INSTALL_COMMAND ""
	)
endif(BUILD_FFMPEG OR BUILD_ALL)

if(BUILD_DOUBANGO OR BUILD_ALL)
	set(DOUBANGO_PREFIX doubango)
	set(DOUBANGO_URL "http://doubango.googlecode.com/svn/")
	#set(DOUBANGO_SRC_DIR "${PROJECT_BINARY_DIR}/doubango_src")
	set(DOUBANGO_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR}/${DOUBANGO_PREFIX}/src/doubango/branches/2.0/doubango/)
	
	set(DOUBANGO_BIN_DIR "./doubango_bin")
	set(DOUBANGO_CONFIGURE 
			configure --with-ssl 
									--with-srtp 
									--with-vpx 
									--with-yuv 
									--with-amr 
									--with-speex 
									--with-speexdsp 
									--enable-speexresampler 
									--enable-speexdenoiser 
									--with-opus 
									--with-gsm 
									--with-ilbc 
									--with-g729=${CMAKE_INSTALL_PREFIX} 
									--with-ffmpeg=${CMAKE_INSTALL_PREFIX}
									--prefix=${CMAKE_INSTALL_PREFIX}
	)
	ExternalProject_Add(
		doubango
		PREFIX ${DOUBANGO_PREFIX}
		#--DOWNLOAD
		SVN_REPOSITORY ${DOUBANGO_URL}
		#--PATCH/UPDATE
		#--CONFIGURE
		#SOURCE_DIR ${DOUBANGO_SRC_DIR}
		# CONFIGURE_COMMAND ${CMAKE_COMMAND} -E chdir ${DOUBANGO_SRC_DIR}/branches/2.0/doubango ${SHELL_EXECUTABLE} configure --prefix=${CMAKE_INSTALL_PREFIX}
		CONFIGURE_COMMAND ${SHELL_EXECUTABLE} LDFLAGS=-L${CMAKE_INSTALL_PREFIX}/lib/ CFLAGS=-I${CMAKE_INSTALL_PREFIX}/include CXXFLAGS=-I${CMAKE_INSTALL_PREFIX}/include ${DOUBANGO_SRC_DIR}/${DOUBANGO_CONFIGURE}
		# CONFIGURE_COMMAND ${SHELL_EXECUTABLE} ${DOUBANGO_SRC_DIR}/${DOUBANGO_CONFIGURE}
		#--BUILD
		#BUILD_COMMAND ${SHELL_EXECUTABLE} LDFLAGS="-L${CMAKE_INSTALL_PREFIX}/lib"${DOUBANGO_SRC_DIR}/make
		#--INSTALL
		#INSTALL_COMMAND ""
		#INSTALL_COMMAND ${SHELL_EXECUTABLE} ${DOUBANGO_SRC_DIR}/make install
		#--TEST
		#--OUTPUT LOGGING
		# LOG_DOWNLOAD 1
		# LOG_UPDATE 1
		# LOG_CONFIGURE 1
		# LOG_BUILD 1
		# LOG_TEST 1
		# LOG_INSTALL 1
	)

	ExternalProject_Add_Step(
		doubango autogen
		COMMAND ${CMAKE_COMMAND} -E chdir ${DOUBANGO_SRC_DIR} autogen.sh
		# COMMAND ${CMAKE_COMMAND} -E chdir ${DOUBANGO_SRC_DIR} libtoolize --copy --force --verbose
		# COMMAND ${CMAKE_COMMAND} -E chdir ${DOUBANGO_SRC_DIR} autoheader --prepend-include=-I${CMAKE_INSTALL_PREFIX}/lib --verbose
		# COMMAND ${CMAKE_COMMAND} -E chdir ${DOUBANGO_SRC_DIR} autoreconf -i --prepend-include=-I${CMAKE_INSTALL_PREFIX}/include --verbose
		DEPENDEES update
		DEPENDERS configure
	)
  ExternalProject_Add_Step(
    doubango cp_src
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${DOUBANGO_SRC_DIR} ${CMAKE_CURRENT_BINARY_DIR}/doubango/src/doubango-build/
    DEPENDEES configure
    DEPENDERS build
  )
endif(BUILD_DOUBANGO OR BUILD_ALL)

if(BUILD_YUV OR BUILD_ALL)
	add_dependencies(doubango yuv)
endif(BUILD_YUV OR BUILD_ALL)

if(BUILD_OPENCORE OR BUILD_ALL)
	add_dependencies(doubango opencore)
endif(BUILD_OPENCORE OR BUILD_ALL)

if(BUILD_OPUS OR BUILD_ALL)
	add_dependencies(doubango opus)
endif(BUILD_OPUS OR BUILD_ALL)

if(BUILD_SPEEX OR BUILD_ALL)
	add_dependencies(doubango speex)
endif(BUILD_SPEEX OR BUILD_ALL)

if(BUILD_GSM OR BUILD_ALL)
	add_dependencies(doubango gsm)
endif(BUILD_GSM OR BUILD_ALL)

if(BUILD_G729 OR BUILD_ALL)
	add_dependencies(doubango g729)
endif(BUILD_G729 OR BUILD_ALL)

if(BUILD_iLBC OR BUILD_ALL)
  add_dependencies(doubango iLBC)
endif(BUILD_iLBC OR BUILD_ALL)

if(BUILD_FFMPEG OR BUILD_ALL)
	add_dependencies(doubango ffmpeg)
endif(BUILD_FFMPEG OR BUILD_ALL)

