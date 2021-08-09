cmake_minimum_required(VERSION 3.7)

project(audio)

set(
    PROG_SRCS
    src/main.cpp
    src/audio.cpp
)

find_package(wxWidgets COMPONENTS core base xrc REQUIRED)

include(${wxWidgets_USE_FILE})

add_executable(${PROJECT_NAME} ${PROG_SRCS})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

install (TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)