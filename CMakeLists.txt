cmake_minimum_required(VERSION 3.23)

project(ctiger)

include_directories("./include")

file(GLOB_RECURSE SOURCES "src/*.c")

set(SRC ${CMAKE_SOURCE_DIR}/src)

add_executable(ctiger ${SOURCES})

install(TARGETS ctiger DESTINATION bin)

add_custom_command(
  OUTPUT ${SRC}/parser.c
  COMMAND yacc -r all -d -o ${SRC}/parser.c ${SRC}/parser.y
  DEPENDS ${SRC}/parser.y
)

add_custom_command(
  OUTPUT ${SRC}/lexer.c
  COMMAND lex -o ${SRC}/lexer.c ${SRC}/lexer.x
  DEPENDS ${SRC}/lexer.x
)