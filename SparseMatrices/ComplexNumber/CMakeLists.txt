cmake_minimum_required(VERSION 3.0) # Проверка версии CMake.
									# Если версия установленой программы
									# старее указаной, произайдёт аварийный выход.

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(ComplexNumber)				# Название проекта

set(SOURCE_LIB ComplexNumber.cpp ComplexNumber.hpp)		# Установка переменной со списком исходников

add_library(ComplexNumber STATIC ${SOURCE_LIB})# Создание статической библиотеки