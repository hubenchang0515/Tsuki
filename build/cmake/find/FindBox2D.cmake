# Locate BOX2D library
# This module defines
# BOX2D_LIBRARY, the name of the library to link against
# BOX2D_FOUND, if false, do not try to link to BOX2D
# BOX2D_INCLUDE_DIR, where to find Box2D.h
#
# Additional Note: If you see an empty BOX2D_LIBRARY_TEMP in your configuration
# and no BOX2D_LIBRARY, it means CMake did not find your BOX2D library
# (BOX2D.dll, libBOX2D.so, BOX2D.framework, etc).
# Set BOX2D_LIBRARY_TEMP to point to your Box2D library, and configure again.
# Similarly, if you see an empty Box2DMAIN_LIBRARY, you should set this value
# as appropriate. These values are used to generate the final BOX2D_LIBRARY
# variable, but when these values are unset, BOX2D_LIBRARY does not get created.
#
# $Box2D is an environment variable that would
# correspond to the ./configure --prefix=$Box2D
# used in building Box2D.
# l.e.galup 9-20-02
#
# Modified by Eric Wing.
# Added code to assist with automated building by using environmental variables
# and providing a more controlled/consistent search behavior.
# Added new modifications to recognize OS X frameworks and
# additional Unix paths (FreeBSD, etc).
# Also corrected the header search path to follow "proper" Box2D guidelines.
# Added a search for Box2Dmain which is needed by some platforms.
# Added a search for threads which is needed by some platforms.
# Added needed compile switches for MinGW.
#
# On OSX, this will prefer the Framework version (if found) over others.
# People will have to manually change the cache values of
# BOX2D_LIBRARY to override this selection or set the CMake environment
# CMAKE_INCLUDE_PATH to modify the search paths.
#
# Note that the header path has changed from Box2D/SDL.h to just SDL.h
# This needed to change because "proper" Box2D convention
# is #include "SDL.h", not <Box2D/SDL.h>. This is done for portability
# reasons because not all systems place things in Box2D/ (see FreeBSD).
#
# Ported by Johnny Patterson. This is a literal port for Box2D of the FindSDL.cmake
# module with the minor edit of changing "SDL" to "Box2D" where necessary. This
# was not created for redistribution, and exists temporarily pending official
# Box2D CMake modules.
# 
# Note that on windows this will only search for the 32bit libraries, to search
# for 64bit change x86/i686-w64 to x64/x86_64-w64

#=============================================================================
# Copyright 2003-2009 Kitware, Inc.
#
# CMake - Cross Platform Makefile Generator
# Copyright 2000-2014 Kitware, Inc.
# Copyright 2000-2011 Insight Software Consortium
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# * Redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer.
#
# * Redistributions in binary form must reproduce the above copyright
# notice, this list of conditions and the following disclaimer in the
# documentation and/or other materials provided with the distribution.
#
# * Neither the names of Kitware, Inc., the Insight Software Consortium,
# nor the names of their contributors may be used to endorse or promote
# products derived from this software without specific prior written
# permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
# License text for the above reference.)

FIND_PATH(BOX2D_INCLUDE_DIR Box2D.h
	HINTS
	${Box2D}
	$ENV{Box2D}
	$ENV{BOX2D}
	PATH_SUFFIXES include/Box2D include Box2D
	i686-w64-mingw32/include/Box2D
	x86_64-w64-mingw32/include/Box2D
	PATHS
	~/Library/Frameworks
	/Library/Frameworks
	/usr/local/include/Box2D
	/usr/include/Box2D
	/sw # Fink
	/opt/local # DarwinPorts
	/opt/csw # Blastwave
	/opt
)

# Lookup the 64 bit libs on x64
IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
	FIND_LIBRARY(BOX2D_LIBRARY_TEMP
		NAMES Box2D
		HINTS
		${Box2D}
		$ENV{Box2D}
		$ENV{BOX2D}
		PATH_SUFFIXES lib64 lib
		lib/x64
		x86_64-w64-mingw32/lib
		PATHS
		/sw
		/opt/local
		/opt/csw
		/opt
	)
# On 32bit build find the 32bit libs
ELSE(CMAKE_SIZEOF_VOID_P EQUAL 8)
	FIND_LIBRARY(BOX2D_LIBRARY_TEMP
		NAMES Box2D
		HINTS
		${Box2D}
		$ENV{Box2D}
		$ENV{BOX2D}
		PATH_SUFFIXES lib
		lib/x86
		i686-w64-mingw32/lib
		PATHS
		/sw
		/opt/local
		/opt/csw
		/opt
	)
ENDIF(CMAKE_SIZEOF_VOID_P EQUAL 8)

SET(BOX2D_FOUND "NO")
	IF(BOX2D_LIBRARY_TEMP)
	# Set the final string here so the GUI reflects the final state.
	SET(BOX2D_LIBRARY ${BOX2D_LIBRARY_TEMP} CACHE STRING "Where the BOX2D Library can be found")
	# Set the temp variable to INTERNAL so it is not seen in the CMake GUI
	SET(BOX2D_LIBRARY_TEMP "${BOX2D_LIBRARY_TEMP}" CACHE INTERNAL "")
	SET(BOX2D_FOUND "YES")
ENDIF(BOX2D_LIBRARY_TEMP)

INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(BOX2D REQUIRED_VARS BOX2D_LIBRARY BOX2D_INCLUDE_DIR)

