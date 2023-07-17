cmake_minimum_required(VERSION 3.0)

project(isbtree)							# Название проекта

set(SRC_LIST isbtree.cpp)					# Установка переменной со списком исходников для исполняемого файла

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic-errors -g")

add_executable(${PROJECT_NAME} ${SRC_LIST})	# Создает исполняемый файл с именем проекта

