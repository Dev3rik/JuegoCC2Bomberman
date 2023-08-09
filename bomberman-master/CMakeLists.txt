cmake_minimum_required(VERSION 3.16)
project(bomberman)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")
file(GLOB_RECURSE INCLUDE_FILES "include/*.h")
include_directories("include/")

find_package(nlohmann_json REQUIRED)

add_executable(bomberman ${SOURCE_FILES} ${INCLUDE_FILES})

target_link_libraries(bomberman nlohmann_json::nlohmann_json)
target_link_libraries(bomberman nlohmann_json)



set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2.5.1 COMPONENTS system window graphics network audio REQUIRED)

if (SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")

    link_directories(${SFML_LIBRARY_DIR})
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(bomberman ${SFML_LIBRARIES})
endif()

add_custom_command(TARGET bomberman PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resource/ $<TARGET_FILE_DIR:bomberman>/resource/)

