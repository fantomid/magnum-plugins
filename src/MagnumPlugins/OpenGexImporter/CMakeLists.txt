#
#   This file is part of Magnum.
#
#   Copyright © 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018
#             Vladimír Vondruš <mosra@centrum.cz>
#
#   Permission is hereby granted, free of charge, to any person obtaining a
#   copy of this software and associated documentation files (the "Software"),
#   to deal in the Software without restriction, including without limitation
#   the rights to use, copy, modify, merge, publish, distribute, sublicense,
#   and/or sell copies of the Software, and to permit persons to whom the
#   Software is furnished to do so, subject to the following conditions:
#
#   The above copyright notice and this permission notice shall be included
#   in all copies or substantial portions of the Software.
#
#   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
#   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
#   DEALINGS IN THE SOFTWARE.
#

find_package(Magnum REQUIRED Trade AnyImageImporter)

if(BUILD_PLUGINS_STATIC)
    set(MAGNUM_OPENGEXIMPORTER_BUILD_STATIC 1)
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/configure.h.cmake
               ${CMAKE_CURRENT_BINARY_DIR}/configure.h)

if(MAGNUM_BUILD_DEPRECATED)
    add_subdirectory(OpenDdl)
endif()

set(OpenGexImporter_SRCS
    OpenGexImporter.cpp)

set(OpenGexImporter_HEADERS
    OpenGexImporter.h
    OpenGex.h)

set(OpenGexImporter_PRIVATE_HEADERS
    openGexSpec.hpp)

# OpenGexImporter plugin
add_plugin(OpenGexImporter
    "${MAGNUM_PLUGINS_IMPORTER_DEBUG_BINARY_INSTALL_DIR};${MAGNUM_PLUGINS_IMPORTER_DEBUG_LIBRARY_INSTALL_DIR}"
    "${MAGNUM_PLUGINS_IMPORTER_RELEASE_BINARY_INSTALL_DIR};${MAGNUM_PLUGINS_IMPORTER_RELEASE_LIBRARY_INSTALL_DIR}"
    OpenGexImporter.conf
    ${OpenGexImporter_SRCS}
    ${OpenGexImporter_HEADERS}
    ${OpenGexImporter_PRIVATE_HEADERS})
if(BUILD_PLUGINS_STATIC AND BUILD_STATIC_PIC)
    set_target_properties(OpenGexImporter PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()
target_include_directories(OpenGexImporter PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(OpenGexImporter PUBLIC Magnum::Trade MagnumOpenDdl)
if(CORRADE_TARGET_WINDOWS)
    target_link_libraries(OpenGexImporter PUBLIC Magnum::AnyImageImporter)
elseif(BUILD_PLUGINS_STATIC)
    target_link_libraries(OpenGexImporter INTERFACE Magnum::AnyImageImporter)
endif()

install(FILES ${OpenGexImporter_HEADERS} ${CMAKE_CURRENT_BINARY_DIR}/configure.h
    DESTINATION ${MAGNUM_PLUGINS_INCLUDE_INSTALL_DIR}/OpenGexImporter)

# Automatic static plugin import
if(BUILD_PLUGINS_STATIC)
    install(FILES importStaticPlugin.cpp DESTINATION ${MAGNUM_PLUGINS_INCLUDE_INSTALL_DIR}/OpenGexImporter)
    if(NOT CMAKE_VERSION VERSION_LESS 3.1)
        target_sources(OpenGexImporter INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/importStaticPlugin.cpp)
    endif()
endif()

if(BUILD_TESTS)
    add_subdirectory(Test)
endif()

# MagnumPlugins OpenGexImporter target alias for superprojects
add_library(MagnumPlugins::OpenGexImporter ALIAS OpenGexImporter)
