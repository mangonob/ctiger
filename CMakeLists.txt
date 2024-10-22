cmake_minimum_required(VERSION 3.23)

project(ctiger)

set(CMAKE_C_STANDARD 11)

include_directories("./include")

set(SRC ${CMAKE_SOURCE_DIR}/src)

file(GLOB_RECURSE SOURCES ${SRC}/*.c)

add_executable(tigerc ${SOURCES})

install(TARGETS tigerc DESTINATION bin)

add_custom_command(
  OUTPUT ${SRC}/parser.c
  COMMAND yacc -r all -d -Wno-yacc -o ${SRC}/parser.c ${SRC}/parser.y
  DEPENDS ${SRC}/parser.y
)

add_custom_command(
  OUTPUT ${SRC}/lexer.c
  COMMAND lex -o ${SRC}/lexer.c ${SRC}/lexer.x
  DEPENDS ${SRC}/lexer.x
)
