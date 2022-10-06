cmake_minimum_required(VERSION 3.16) # Проверка версии CMake.
									# Если версия установленой программы
									# старее указаной, произайдёт аварийный выход.

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(RationalNumber)				# Название проекта

set(SOURCE_LIB RationalNumber.cpp RationalNumber.hpp)		# Установка переменной со списком исходников

add_library(RationalNumber STATIC ${SOURCE_LIB})# Создание статической библиотеки

