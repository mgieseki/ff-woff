cmake_minimum_required(VERSION 3.3)
project(ff-woff)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(SOURCE_FILES
	fontforge/PfEd.h
	fontforge/configure-fontforge.h
	fontforge/edgelist.h
	fontforge/edgelist2.h
	fontforge/encoding.h
	fontforge/fontforge-config.h
	fontforge/fontforge.h
	fontforge/fontforgevw.h
	fontforge/libffstamp.h
	fontforge/namehash.h
	fontforge/psfont.h
	fontforge/sd.h
	fontforge/sfd1.h
	fontforge/splinefont.h
	fontforge/stemdb.h
	fontforge/tables.h
	fontforge/ttf.h
	fontforge/ttfinstrs.h
	fontforge/uiinterface.h
	fontforge/alphabet.c
	fontforge/asmfpst.c
	fontforge/autohint.c
	fontforge/char.c
	fontforge/cjk.c
	fontforge/cvundoes.c
	fontforge/dumppfa.c
	fontforge/encoding.c
	fontforge/fvfonts.c
	fontforge/gwwiconv.c
	fontforge/lookups.c
	fontforge/macbinary.c
	fontforge/macenc.c
	fontforge/mathconstants.c
	fontforge/memory.c
	fontforge/mm.c
	fontforge/namelist.c
	fontforge/nouiutil.c
	fontforge/nowakowskittfinstr.c
	fontforge/parsepfa.c
	fontforge/parsettf.c
	fontforge/parsettfatt.c
	fontforge/psread.c
	fontforge/pua.c
	fontforge/sfd.c
	fontforge/sfd1.c
	fontforge/splinechar.c
	fontforge/splinefont.c
	fontforge/splineorder2.c
	fontforge/splineoverlap.c
	fontforge/splinerefigure.c
	fontforge/splinesave.c
	fontforge/splinesaveafm.c
	fontforge/splineutil.c
	fontforge/splineutil2.c
	fontforge/start.c
	fontforge/stemdb.c
	fontforge/tottf.c
	fontforge/tottfaat.c
	fontforge/tottfgpos.c
	fontforge/tottfvar.c
	fontforge/ttfinstrs.c
	fontforge/ttfspecial.c
	fontforge/unialt.c
	fontforge/ustring.c
	fontforge/utils.c
	fontforge/utype.c
	fontforge/woff.c)

include_directories(fontforge)
include_directories(inc)

find_package(ZLIB REQUIRED)

add_library(${CMAKE_PROJECT_NAME} SHARED ${SOURCE_FILES})
add_library(${CMAKE_PROJECT_NAME}-static STATIC ${SOURCE_FILES})
target_link_libraries(${CMAKE_PROJECT_NAME} ${ZLIB_LIBRARIES})
