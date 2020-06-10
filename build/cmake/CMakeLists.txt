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

# compile flags
set (CMAKE_CXX_FLAGS   "-std=c++11 -W -Wall -O2" )
include_directories (../../include )

# build .so
aux_source_directory ( ../../src/core        CORE_SRC )
aux_source_directory ( ../../src/event       EVENT_SRC )
aux_source_directory ( ../../src/exception   EXCEPTION_SRC )
aux_source_directory ( ../../src/window      WINDOW_SRC )
aux_source_directory ( ../../src/graphics    GRAPHICS_SRC )
add_library ( Tsuki  SHARED  ${CORE_SRC} ${EVENT_SRC} ${EXCEPTION_SRC} ${WINDOW_SRC} ${GRAPHICS_SRC} )
set_target_properties(Tsuki   PROPERTIES   LINK_FLAGS   ${SDL2_LIBRARY} )
set_target_properties(Tsuki   PROPERTIES   LINK_FLAGS   ${SDL2_IMAGE_LIBRARY} )

# install header file
install(DIRECTORY ../../include/Tsuki DESTINATION include
        FILES_MATCHING PATTERN "*.h")

install(DIRECTORY ../../include/Tsuki DESTINATION include
        FILES_MATCHING PATTERN "*.hpp")

# install library
install(TARGETS Tsuki
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib)