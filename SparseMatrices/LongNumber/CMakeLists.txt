cmake_minimum_required(VERSION 3.0) # Проверка версии CMake.
									# Если версия установленой программы
									# старее указаной, произайдёт аварийный выход.

project(LongNumber)				# Название проекта

set(SOURCE_LIB LongNumber.cpp LongNumber.hpp)		# Установка переменной со списком исходников

add_library(LongNumber STATIC ${SOURCE_LIB})# Создание статической библиотеки