cmake_minimum_required(VERSION 3.0) # Проверка версии CMake.
									# Если версия установленой программы
									# старее указаной, произайдёт аварийный выход.

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Parser)				# Название проекта

set(PARSER Parser.cpp Parser.hpp)		# Установка переменной со списком исходников

add_library(Parser ${PARSER})# Создание статической библиотеки
