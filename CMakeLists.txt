cmake_minimum_required(VERSION 3.25)
project(jeeson VERSION 1.0 LANGUAGES C)
set(SOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(EXECUTABLE main)
add_executable(${EXECUTABLE})

target_compile_options(${EXECUTABLE} PRIVATE -Wall -Wextra -Wpedantic -Werror -g)
target_include_directories(${EXECUTABLE} PUBLIC ${INCLUDE_DIR})
target_sources(${EXECUTABLE} PUBLIC ${SOURCE_DIRECTORY}/${EXECUTABLE}.c)
add_library(jeeson SHARED
  source/lexer.c
  source/io.c
  source/token.c
  source/parser.c
  source/api.c
  source/json.c
)

target_include_directories(jeeson PRIVATE ${INCLUDE_DIR})
set_target_properties(jeeson PROPERTIES VERSION ${PROJECT_VERSION} LIBRARY_OUTPUT_DIRECTORY lib)
set_target_properties(jeeson PROPERTIES PUBLIC_HEADER include/api.h)
target_link_libraries(jeeson m)
target_link_libraries(${EXECUTABLE} jeeson)
