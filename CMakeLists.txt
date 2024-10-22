cmake_minimum_required(VERSION 3.23)

project(ctiger)

set(CMAKE_C_STANDARD 11)

set(SRC ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE ${CMAKE_SOURCE_DIR}/include)

include_directories(${INCLUDE})

file(GLOB_RECURSE SOURCES ${SRC}/*.c)

add_executable(tigerc ${SOURCES} ${SRC}/parser.c ${SRC}/lexer.c ${SRC}/tree_tiling.c)

install(TARGETS tigerc DESTINATION bin)

add_custom_command(
  OUTPUT ${SRC}/parser.c
  COMMAND bison -r all --header=${INCLUDE}/parser.h -o ${SRC}/parser.c ${SRC}/parser.yy
  DEPENDS ${SRC}/parser.yy
)

add_custom_command(
  OUTPUT ${SRC}/tree_tiling.c
  COMMAND bison -r all --header=${INCLUDE}/tree_tiling.h -o ${SRC}/tree_tiling.c ${SRC}/tree_tiling.yy
  DEPENDS ${SRC}/tree_tiling.yy
)

add_custom_command(
  OUTPUT ${SRC}/lexer.c
  COMMAND lex -o ${SRC}/lexer.c ${SRC}/lexer.x
  DEPENDS ${SRC}/lexer.x
)
