cmake_minimum_required(VERSION 3.0) # Проверка версии CMake.
									# Если версия установленой программы
									# старее указаной, произайдёт аварийный выход.

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(SparseMatrices)				# Название проекта

set(SOURCE_EXE main.cpp)			# Установка переменной со списком исходников

include_directories(RationalNumber)			# Расположение заголовочных файлов
include_directories(ComplexNumber)			# Расположение заголовочных файлов
include_directories(LongNumber)			# Расположение заголовочных файлов
# include_directories(Vector)			# Расположение заголовочных файлов

add_executable(main ${SOURCE_EXE})	# Создает исполняемый файл с именем main

add_subdirectory(RationalNumber)	# Добавление подпроекта, указывается имя дирректории
add_subdirectory(ComplexNumber)		# Добавление подпроекта, указывается имя дирректории
add_subdirectory(LongNumber)	# Добавление подпроекта, указывается имя дирректории
# add_subdirectory(Vector)			# Добавление подпроекта, указывается имя дирректории


target_link_libraries(main RationalNumber)		# Линковка программы с библиотекой
target_link_libraries(main ComplexNumber)		# Линковка программы с библиотекой
target_link_libraries(main LongNumber)		# Линковка программы с библиотекой
# target_link_libraries(main Vector)		# Линковка программы с библиотекой