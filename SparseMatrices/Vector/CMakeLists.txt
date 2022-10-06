cmake_minimum_required(VERSION 3.0) # Проверка версии CMake.
									# Если версия установленой программы
									# старее указаной, произайдёт аварийный выход.

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Vector)				# Название проекта

set(SOURCE_LIB Vector.hpp)		# Установка переменной со списком исходников

add_library(Vector STATIC ${SOURCE_LIB})# Создание статической библиотеки

set_target_properties(Vector PROPERTIES LINKER_LANGUAGE CXX)
