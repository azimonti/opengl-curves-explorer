cmake_minimum_required(VERSION 3.13.4)
project(opengl-curves-explorer)
set (PROJECT_VERSION "1.0"    )
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION})
# location of ma-libs
set(MA_LIBS_ROOT "${CMAKE_SOURCE_DIR}/externals/ma-libs")
set(MA_LIBS_CPP_ROOT "${MA_LIBS_ROOT}/cpp")
list(APPEND CMAKE_MODULE_PATH "${MA_LIBS_ROOT}/cmake_modules")
include( COMPILERCOMMON     )
include( COMPILERCPP        )
include( FindLIBS           )
cmake_policy(SET CMP0072 NEW)
find_package(OpenGL REQUIRED)
set(CMAKE_CXX_STANDARD 17   )

if(WIN32)
    generic_libs_find(glew ON      )
    generic_libs_find(glfw ON      )
    generic_libs_find(glm  ON      )
else()
    generic_libs_find(glew OFF     )
    generic_libs_find(glfw OFF     )
    generic_libs_find(glm  OFF     )
endif()
generic_libs_find(imgui ON         )
generic_libs_find(implot ON        )
generic_libs_find(imGuIZMO.quat ON )

include_directories( ${IMGUI_INCLUDE_DIRS}           )
include_directories( ${IMGUI_INCLUDE_DIRS}/backends  )
include_directories( ${IMGUI_INCLUDE_DIRS}/misc/cpp  )
include_directories( ${GLM_INCLUDE_DIRS}             )
include_directories( ${GLEW_INCLUDE_DIRS}            )
include_directories( ${GLEW_INCLUDE_DIRS}/include    )
include_directories( ${GLFW_INCLUDE_DIRS}            )
include_directories( ${GLFW_INCLUDE_DIRS}/include    )
include_directories( ${IMGUIZMOQUAT_INCLUDE_DIRS}/imGuIZMO.quat )
include_directories( ${IMGUI_INCLUDE_DIRS}/..        )
include_directories( ${IMPLOT_INCLUDE_DIRS}          )
include_directories( ${MA_LIBS_CPP_ROOT}                )
include_directories( ${MA_LIBS_CPP_ROOT}/libgraphic_engine/src      )
include_directories( ${MA_LIBS_CPP_ROOT}/utils          )

add_definitions( -DVGIZMO_USES_GLM -DLOGGING )
add_definitions( -DGLEW_STATIC -DGLM_ENABLE_EXPERIMENTAL )

set( SRCS
  ./src/main.cpp
  ./src/gl_app.cpp
  ./src/gl_window.cpp
  ./src/imguizmo_dialog.cpp
  ./src/imguiparams_dialog.cpp
  ./src/geomshapes2.cpp
)
set( SRCS_LOG ${MA_LIBS_CPP_ROOT}/utils/log/log.cpp )

link_directories(${LIBS_DIR}          )
link_directories(${GLEW_LIBRARY_PATH} )
link_directories(${GLEW_LIBRARY_PATH2})
link_directories(${GLFW_LIBRARY_PATH} )
link_directories( ${MA_LIBS_ROOT}/build/${CMAKE_BUILD_TYPE} )
add_executable( ${PROJECT_NAME} ${SRCS} ${SRCS_LOG})

if(UNITYBUILD)
    set_property( TARGET ${PROJECT_NAME} PROPERTY UNITY_BUILD ON )
endif()

if (MSVC)
    target_link_libraries( ${PROJECT_NAME} imgui imguizmoquat ${OPENGL_gl_LIBRARY} glfw3 glew debug cpp_graphic_engined optimized cpp_graphic_engine)
elseif(APPLE)
    target_link_libraries( ${PROJECT_NAME} libimgui.a imguizmoquat ${OPENGL_gl_LIBRARY} libglfw.dylib glew debug cpp_graphic_engined optimized cpp_graphic_engine "-framework Foundation -framework IOKit -framework Cocoa" )
else()
    target_link_libraries( ${PROJECT_NAME} libimgui.a imguizmoquat implot ${OPENGL_gl_LIBRARY} libglfw.so libGLEW.so -ldl -lpthread -lGL -lGLU debug cpp_graphic_engined optimized cpp_graphic_engine)
endif()
