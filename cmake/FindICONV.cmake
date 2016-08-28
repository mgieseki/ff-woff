#  Copyright (c) 2006, Peter Kümmel, <syntheticpp@gmx.net>
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions
#  are met:
#
#  1. Redistributions of source code must retain the copyright
#     notice, this list of conditions and the following disclaimer.
#  2. Redistributions in binary form must reproduce the copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
#  3. The name of the author may not be used to endorse or promote products
#     derived from this software without specific prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
#  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
#  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
#  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
#  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
#  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
#  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
#  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
#  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true)

if (ICONV_INCLUDE_DIR)
  # Already in cache, be silent
  set(ICONV_FIND_QUIETLY TRUE)
endif()

find_path(ICONV_INCLUDE_DIR NAMES iconv.h
	PATHS ${ICONV_ROOT}/include /usr/include /usr/local/include)

set(POTENTIAL_ICONV_LIBS libiconv libiconv2 iconv)

find_library(ICONV_LIBRARY NAMES ${POTENTIAL_ICONV_LIBS}
	PATHS ${ICONV_ROOT}/lib /usr/lib /usr/local/lib)

include(CheckFunctionExists)
check_function_exists(iconv HAVE_ICONV_IN_LIBC)
if(ICONV_INCLUDE_DIR AND HAVE_ICONV_IN_LIBC)
	set(ICONV_FOUND TRUE)
	set(ICONV_LIBRARY CACHE TYPE STRING FORCE)
endif()
if(ICONV_INCLUDE_DIR AND ICONV_LIBRARY)
	set(ICONV_FOUND TRUE)
endif()


if(ICONV_FOUND)
   if(NOT ICONV_FIND_QUIETLY)
      message(STATUS "Found iconv: ${ICONV_LIBRARY}")
   endif()
else()
   if(ICONV_FIND_REQUIRED)
      message(STATUS "Looked for iconv library named ${POTENTIAL_ICONV_LIBS}.")
      message(STATUS "Found no acceptable iconv library. This is fatal.")
      message(STATUS "iconv header: ${ICONV_INCLUDE_DIR}")
      message(STATUS "iconv lib   : ${ICONV_LIBRARY}")
      message(FATAL_ERROR "Could NOT find iconv library")
   endif()
endif()

mark_as_advanced(ICONV_LIBRARY ICONV_INCLUDE_DIR)

