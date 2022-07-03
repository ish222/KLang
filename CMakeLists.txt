cmake_minimum_required(VERSION 3.22)
project(KLang C)

set(CMAKE_C_STANDARD 99)

add_executable(KLang src/main.c include/util.h include/token.h include/lexer.h src/util.c src/token.c src/lexer.c src/parser.c include/parser.h)
