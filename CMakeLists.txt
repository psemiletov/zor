cmake_minimum_required(VERSION 3.0)
set (QT_MIN_VERSION "5.4.0")

include_directories(${Qt5Widgets_INCLUDE_DIRS})
add_definitions(${Qt5Widgets_DEFINITIONS})

set(PROJECT "zor")
project ($PROJECT VERSION 1.0.0)


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED Core Widgets)

if(BUILD_TESTING)
  find_package(Qt5Test ${QT_MIN_VERSION} CONFIG REQUIRED)
endif()


#qt5_add_resources(QT_RESOURCES zor.qrc)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} -fuse-ld=gold")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")


if (UNIX AND NOT APPLE)
  execute_process(COMMAND ${CMAKE_C_COMPILER} -fuse-ld=gold -Wl,--version ERROR_QUIET OUTPUT_VARIABLE ld_version)
  if ("${ld_version}" MATCHES "GNU gold")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=gold -Wl,--disable-new-dtags")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fuse-ld=gold -Wl,--disable-new-dtags")
  endif()
endif()

# Populate a CMake variable with the sources
set(zor_SRCS
    cmainwindow.cpp
    main.cpp
)

#set(zor_ICONPNG
#    ./icons/upsm.png
#)

#set(zor_ICONSVG
#    ./icons/upsm.svg
#)


#set(upsm_DESKTOP
#    ./desktop/upsm.desktop
#)


add_custom_target(dist
COMMAND git archive --prefix=${PROJECT}-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}/ master | bzip2 >${PROJECT}-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.tar.bz2
WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)



add_executable(${PROJECT} ${zor_SRCS} ${QT_RESOURCES})

target_link_libraries(${PROJECT} Qt5::Widgets Qt5::Core)

install (TARGETS ${PROJECT} DESTINATION bin)
#install (FILES ${upsm_ICONSVG} DESTINATION share/icons/hicolor/scalable/apps)
#install (FILES ${upsm_ICONPNG} DESTINATION share/icons/hicolor/128x128/apps)
#install (FILES ${upsm_DESKTOP} DESTINATION share/applications)
