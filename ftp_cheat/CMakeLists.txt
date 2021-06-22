cmake_minimum_required(VERSION 3.13.0)
project(FTP)

set(CMAKE_C_FLAGS_RELEASE "-O3 -fvisibility=hidden -flto -fno-exceptions -DNDEBUG -Wfatal-errors")

if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -fno-rtti")

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} --no-gnu-unique")
endif()

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/FTP/*.cpp")
list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/FTP/imgui/GL/gl3w.c")
list(REMOVE_ITEM SOURCES "${CMAKE_SOURCE_DIR}/FTP/imgui/imgui_impl_dx9.cpp") 
list(REMOVE_ITEM SOURCES "${CMAKE_SOURCE_DIR}/FTP/imgui/imgui_impl_win32.cpp") 
list(REMOVE_ITEM SOURCES "${CMAKE_SOURCE_DIR}/FTP/Hooks/MinHook.cpp") 

# FreeType sources
list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/FTP/freetype/src/autofit/autofit.c")
list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/FTP/freetype/src/cff/cff.c")
list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/FTP/freetype/src/base/ftbase.c")
list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/FTP/freetype/src/base/ftbitmap.c")
list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/FTP/freetype/src/base/ftdebug.c")
list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/FTP/freetype/src/base/ftglyph.c")
list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/FTP/freetype/src/base/ftinit.c")
list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/FTP/freetype/src/base/ftsynth.c")
list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/FTP/freetype/src/base/ftsystem.c")
list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/FTP/freetype/src/psaux/psaux.c")
list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/FTP/freetype/src/pshinter/pshinter.c")
list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/FTP/freetype/src/psnames/psnames.c")
list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/FTP/freetype/src/raster/raster.c")
list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/FTP/freetype/src/sfnt/sfnt.c")
list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/FTP/freetype/src/smooth/smooth.c")
list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/FTP/freetype/src/truetype/truetype.c")

add_compile_definitions(FT2_BUILD_LIBRARY)

include_directories(/usr/local/include /usr/include/SDL2/ "${CMAKE_SOURCE_DIR}/FTP/freetype/")
link_directories(/usr/local/lib)

add_library(FTP SHARED ${SOURCES})

target_link_libraries(FTP SDL2 GL dl)
target_link_options(FTP PRIVATE LINKER:--no-undefined)
