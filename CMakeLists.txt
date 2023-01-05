cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(WacomProject)

# Set directory paths
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(sources ${SOURCE_DIR}/main.cpp)
#set(includes )

add_executable(WacomProject ${sources} ${includes})

find_package(X11 REQUIRED)
if (X11_FOUND)
    target_include_directories(WacomProject PRIVATE ${X11_INCLDUE_DIR})
    target_link_libraries(WacomProject PRIVATE ${X11_LIBRARIES})
else()
    message(FATAL_ERROR "X11 was not found on the system")
endif()

# Enable C++17
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO)