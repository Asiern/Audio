cmake_minimum_required(VERSION 3.7)
include(FetchContent)

project(audio)

set(
    PROG_SRCS
    src/main.cpp
    src/audio.cpp
    src/updater.cpp
    src/menu.cpp
)

if(WIN32)
  add_executable(${PROJECT_NAME} WIN32 ${PROG_SRCS})
else()
  add_executable(${PROJECT_NAME} ${PROG_SRCS})
endif()


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

if(WIN32)
  set(CURL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/thirdparty/CURL/include)
  set(CURL_LIBRARY ${CMAKE_SOURCE_DIR}/thirdparty/CURL/lib/libcurl.a)
  add_definitions(-DCURL_STATICLIB)
  find_package(CURL REQUIRED)
  include_directories(${CURL_INCLUDE_DIR})
  target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARY})
else()
  find_package(CURL REQUIRED)
  target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})
endif()


###########      BASS     ###########
add_library(BASS SHARED IMPORTED)
if(WIN32)
  set(BASS_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/thirdparty/BASS/c)
  set(BASS_LIBRARY ${CMAKE_SOURCE_DIR}/thirdparty/BASS/c/x64/bass.lib)
  include_directories(${BASS_INCLUDE_DIR})
  target_link_libraries(${PROJECT_NAME} ${BASS_LIBRARY})
else()
  set_target_properties(BASS PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/thirdparty/x64/libbass.so)
  target_include_directories(BASS INTERFACE ${CMAKE_SOURCE_DIR}/thirdparty)
  target_link_libraries(${PROJECT_NAME} BASS)
endif()



install (TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)