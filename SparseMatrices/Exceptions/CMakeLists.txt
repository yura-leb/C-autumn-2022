cmake_minimum_required(VERSION 3.16) # Проверка версии CMake.
									# Если версия установленой программы
									# старее указаной, произайдёт аварийный выход.

                                    
project(Exceptions CXX)				# Название проекта

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_LIB OutOfRange.hpp BadCast.hpp ZeroDivision.hpp)		# Установка переменной со списком исходников

add_library(Exceptions STATIC ${SOURCE_LIB})# Создание статической библиотеки

set_target_properties(Exceptions PROPERTIES LINKER_LANGUAGE CXX)
