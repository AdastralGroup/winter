project(net)
find_package(CURL REQUIRED)
add_library(${PROJECT_NAME} net.cpp)
target_include_directories(net PUBLIC .)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)
include(FetchContent)
# Get the name of this folder as the project name
get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME_WE)
target_link_libraries(${PROJECT_NAME} PRIVATE CURL::libcurl nlohmann_json::nlohmann_json shared)