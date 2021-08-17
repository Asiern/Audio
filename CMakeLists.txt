cmake_minimum_required(VERSION 3.7)
include(FetchContent)

project(audio)

set(
    PROG_SRCS
    src/main.h
    src/main.cpp
    src/audio.h
    src/audio.cpp
    src/updater.h
    src/updater.cpp
    src/menu.h
    src/menu.cpp
    src/utils.h
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

if(WIN32)

  set(wxBUILD_SHARED OFF CACHE BOOL "Build wx libraries as shared libs")
  set(wxBUILD_PRECOMP OFF CACHE BOOL "Use precompiled headers")
  set(wxBUILD_MONOLITHIC OFF CACHE BOOL "Build a single library")

  FetchContent_Declare(
      wxWidgets 
      GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
      GIT_TAG        v3.1.4
      GIT_SHALLOW     TRUE
  )

  FetchContent_GetProperties(wxWidgets)
  FetchContent_MakeAvailable(wxWidgets)

  target_link_libraries(${PROJECT_NAME}
      wxbase
      wxcore
      wxnet
  )

else()
  find_package(wxWidgets COMPONENTS core base xrc REQUIRED)
  include(${wxWidgets_USE_FILE})
  target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
endif()

###########      CURL     ###########

if(WIN32)
  set(CURL_STATICLIB ON CACHE BOOL "Set to ON to build libcurl with static linking.")
  FetchContent_Declare(
      curl 
      GIT_REPOSITORY https://github.com/curl/curl.git
      GIT_TAG        curl-7_78_0
      GIT_SHALLOW     TRUE
  )

  FetchContent_GetProperties(curl)
  if(NOT curl_POPULATED)
    FetchContent_POPULATE(curl)
    add_subdirectory(${curl_SOURCE_DIR} ${curl_BINARY_DIR} EXCLUDE_FROM_ALL)
  endif()
  target_link_libraries(${PROJECT_NAME} libcurl)
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