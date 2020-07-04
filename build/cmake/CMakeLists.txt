# Tsuki

# cmake version
cmake_minimum_required ( VERSION   3.11 )

project ( Tsuki )

include(CheckLibraryExists)
include(FindPkgConfig)

# find packages
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/find")
find_package ( SDL2   REQUIRED )
find_package ( SDL2_image REQUIRED )
find_package ( Box2D REQUIRED )

# compile flags
set (CMAKE_CXX_FLAGS   "-std=c++11 -W -Wall -O2 -g" )
include_directories (../../include )

# build .so
aux_source_directory ( ../../src/Core        CORE_SRC )
aux_source_directory ( ../../src/Event       EVENT_SRC )
aux_source_directory ( ../../src/Exception   EXCEPTION_SRC )
aux_source_directory ( ../../src/Window      WINDOW_SRC )
aux_source_directory ( ../../src/Graphics    GRAPHICS_SRC )
aux_source_directory ( ../../src/Physics     PHYSICS_SRC )

ADD_LIBRARY( Tsuki  SHARED  ${CORE_SRC} ${EVENT_SRC} ${EXCEPTION_SRC} ${WINDOW_SRC} ${GRAPHICS_SRC} ${PHYSICS_SRC} )

SET(TSUKI_LINK_FLAGS ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${BOX2D_LIBRARY})
MESSAGE("SDL2_LIBTSUKI_LINK_FLAGSRARY = ${TSUKI_LINK_FLAGS}")
TARGET_LINK_LIBRARIES(Tsuki ${TSUKI_LINK_FLAGS} )

# install header file
install(DIRECTORY ../../include/Tsuki DESTINATION include
        FILES_MATCHING PATTERN "*.hpp")

install(DIRECTORY ../../include/Tsuki DESTINATION include
        FILES_MATCHING PATTERN "*.h")

# install library
install(TARGETS Tsuki
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib)