cmake_minimum_required(VERSION 3.25)
project(jeeson VERSION 1.0 LANGUAGES C)
set(SOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(EXECUTABLE jeeson)
set(LIB core)
add_executable(${EXECUTABLE})

target_compile_options(${EXECUTABLE} PRIVATE -Wall -Wextra -Wpedantic -Werror -g)
target_include_directories(${EXECUTABLE} PUBLIC ${INCLUDE_DIR})
target_sources(${EXECUTABLE} PUBLIC ${SOURCE_DIRECTORY}/main.c)
add_library(${LIB} SHARED
  source/lexer.c
  source/io.c
  source/token.c
  source/parser.c
  source/api.c
  source/json.c
)

target_include_directories(${LIB} PRIVATE ${INCLUDE_DIR})
set_target_properties(${LIB} PROPERTIES VERSION ${PROJECT_VERSION} LIBRARY_OUTPUT_DIRECTORY lib)
set_target_properties(${LIB} PROPERTIES PUBLIC_HEADER include/api.h)
target_link_libraries(${LIB} m)
target_link_libraries(${EXECUTABLE} ${LIB})
