cmake_minimum_required(VERSION 3.7)
include(FetchContent)

project(audio)

set(
    PROG_SRCS
    src/main.cpp
    src/audio.cpp
)

add_executable(${PROJECT_NAME} ${PROG_SRCS})


########### NLohmann Json ###########

FetchContent_Declare(json GIT_REPOSITORY https://github.com/nlohmann/json.git GIT_TAG v3.7.3)
FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)

###########   wxWidgets   ###########

find_package(wxWidgets COMPONENTS core base xrc REQUIRED)
include(${wxWidgets_USE_FILE})
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

###########      CURL     ###########

find_package(CURL REQUIRED)
target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})


install (TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)