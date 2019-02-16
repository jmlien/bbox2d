#####################################################
#                COMMON Libraries                   #
#####################################################
set(libbbox2d_deps
  mathtool
  polygon)

########## add subdirectories ############
add_subdirectory(mathtool)
add_subdirectory(polygon)

#############################################
# libbbox2d
#############################################

set(LIBBBOX2D_SRC
    ${LIBBBOX2D_SRC}
    bbox2d.cpp)

add_library(libbbox2d STATIC ${LIBBBOX2D_SRC})
target_link_libraries(libbbox2d ${libbbox2d_deps})

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
add_dependencies(${APP_NAME} libbbox2d)

target_link_libraries(${APP_NAME}
                    ${libbbox2d_deps}
                    libbbox2d)
