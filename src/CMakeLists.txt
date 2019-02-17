#####################################################
#                COMMON Libraries                   #
#####################################################
set(bbox2dlib_deps
  mathtool
  polygon)

########## add subdirectories ############
add_subdirectory(mathtool)
add_subdirectory(polygon)

#############################################
# bbox2dlib
#############################################

set(bbox2dlib_SRC
    ${bbox2dlib_SRC}
    bbox2d.cpp)

add_library(bbox2dlib STATIC ${bbox2dlib_SRC})
target_link_libraries(bbox2dlib ${bbox2dlib_deps})

#################################################################
# BBOX EXE
#################################################################

set(APP_NAME bbox2d)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

include_directories(
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/src/polygon"
    "${CMAKE_SOURCE_DIR}/src/mathtool")

set(BBOX2D_SRC
  ${BBOX2D_SRC}
  main.cpp
)

add_executable(${APP_NAME} ${BBOX2D_SRC})
add_dependencies(${APP_NAME} bbox2dlib)

target_link_libraries(${APP_NAME}
                    ${bbox2dlib_deps}
                    bbox2dlib)
