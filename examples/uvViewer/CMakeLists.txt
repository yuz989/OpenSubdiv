#
#   Copyright 2013 Pixar
#
#   Licensed under the Apache License, Version 2.0 (the "Apache License")
#   with the following modification; you may not use this file except in
#   compliance with the Apache License and the following modification to it:
#   Section 6. Trademarks. is deleted and replaced with:
#
#   6. Trademarks. This License does not grant permission to use the trade
#      names, trademarks, service marks, or product names of the Licensor
#      and its affiliates, except as required to comply with Section 4(c) of
#      the License and to reproduce the content of the NOTICE file.
#
#   You may obtain a copy of the Apache License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the Apache License with the above modification is
#   distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
#   KIND, either express or implied. See the Apache License for the specific
#   language governing permissions and limitations under the Apache License.
#

# *** uvViewer ***

set(SHADER_FILES
     shader.glsl
)

set(PLATFORM_LIBRARIES
    ${OSD_LINK_TARGET}
    ${OPENGL_LIBRARY}
    ${GLFW_LIBRARIES}
)

include_directories(
    ${PROJECT_SOURCE_DIR}/opensubdiv
    ${PROJECT_SOURCE_DIR}/regression
    ${GLFW_INCLUDE_DIR}
)

if ( GLEW_FOUND )
    include_directories(${GLEW_INCLUDE_DIR})
    list(APPEND PLATFORM_LIBRARIES ${GLEW_LIBRARY})
endif()

#-------------------------------------------------------------------------------
# Shader Stringification
# We want to use preprocessor include directives to include GLSL and OpenCL
# shader source files in cpp files, but since the sources contain newline
# characters we would need raw string literals from C++11 to do this directly.
# To avoid depending on C++11 we instead use a small tool called "line_quote"
# to generate source files that are suitable for direct inclusion.
foreach(shader_file ${SHADER_FILES})

    string(REGEX REPLACE ".*[.](.*)" "\\1" extension ${shader_file})

    string(REGEX REPLACE "(.*)[.].*" "\\1.inc" inc_file ${shader_file})
    list(APPEND INC_FILES ${inc_file})

    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${inc_file}
        COMMAND stringify ${CMAKE_CURRENT_SOURCE_DIR}/${shader_file}
            ${CMAKE_CURRENT_SOURCE_DIR}/${inc_file}
        DEPENDS stringify ${CMAKE_CURRENT_SOURCE_DIR}/${shader_file}
    )
endforeach()

_add_glfw_executable(uvViewer
    viewer.cpp
    ../common/font_image.cpp
    ../common/hud.cpp
    ../common/gl_hud.cpp
    ${SHADER_FILES}
    ${INC_FILES}
)

target_link_libraries(uvViewer
    ${PLATFORM_LIBRARIES}
)

install(TARGETS uvViewer DESTINATION ${CMAKE_BINDIR_BASE})
