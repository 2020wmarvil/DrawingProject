cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(WacomProject)

# Set directory paths
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(sources 
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/pen.h
    ${SOURCE_DIR}/pen.cpp
)

set(includes ${SOURCE_DIR})

add_executable(WacomProject ${sources} ${includes})

find_package(X11 REQUIRED) # find X11 cmake manpage: https://cmake.org/cmake/help/v3.0/module/FindX11.html
if (X11_FOUND)
    message(TRACE "X11 was found on the system")
else()
    message(FATAL_ERROR "X11 was not found on the system")
endif()

if (X11_Xinput_FOUND)
    message(TRACE "X11 input was found on the system")
else()
    message(FATAL_ERROR "X11 input was not found on the system")
endif()

target_include_directories(WacomProject PRIVATE 
    ${X11_INCLDUE_DIR}
    ${X11_Xinput_INCLDUE_PATH}
)

target_link_libraries(WacomProject PRIVATE 
    ${X11_LIBRARIES}
    ${X11_Xinput_LIB}
)

# Enable C++17
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO)

#add_compile_options(-Wall -Wextra -pedantic -Werror -lXi)