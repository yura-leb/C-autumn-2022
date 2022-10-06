cmake_minimum_required(VERSION 3.0) # Проверка версии CMake.
									# Если версия установленой программы
									# старее указаной, произайдёт аварийный выход.

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(SparseMatrices)				# Название проекта

set(SOURCE_EXE main.cpp)			# Установка переменной со списком исходников

include_directories(RationalNumber			# Расположение заголовочных файлов
					ComplexNumber			# Расположение заголовочных файлов
					LongNumber			# Расположение заголовочных файлов
					Matrix			# Расположение заголовочных файлов
					Parser			# Расположение заголовочных файлов
					Vector			# Расположение заголовочных файлов
					Exceptions)			# Расположение заголовочных файлов

# add_executable(main ${SOURCE_EXE})	# Создает исполняемый файл с именем main
add_library(main ${SOURCE_EXE})	# Создает исполняемый файл с именем main

add_subdirectory(RationalNumber)	# Добавление подпроекта, указывается имя дирректории
add_subdirectory(ComplexNumber)		# Добавление подпроекта, указывается имя дирректории
add_subdirectory(LongNumber)	# Добавление подпроекта, указывается имя дирректории
add_subdirectory(Matrix)	# Добавление подпроекта, указывается имя дирректории
add_subdirectory(Parser)	# Добавление подпроекта, указывается имя дирректории
add_subdirectory(Vector)			# Добавление подпроекта, указывается имя дирректории
add_subdirectory(Exceptions)			# Добавление подпроекта, указывается имя дирректории


target_link_libraries(main RationalNumber)		# Линковка программы с библиотекой
target_link_libraries(main ComplexNumber)		# Линковка программы с библиотекой
target_link_libraries(main LongNumber)		# Линковка программы с библиотекой
target_link_libraries(main Matrix)		# Линковка программы с библиотекой
target_link_libraries(main Parser)		# Линковка программы с библиотекой
target_link_libraries(main Vector)		# Линковка программы с библиотекой
target_link_libraries(main Exceptions)		# Линковка программы с библиотекой

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(LongNumberTest tests/LongNumberTest.cpp)
target_link_libraries(LongNumberTest gtest_main)
target_link_libraries(LongNumberTest main)
add_test(NAME LongNumberTest COMMAND LongNumberTest)

add_executable(ComplexNumberTest tests/ComplexNumberTest.cpp)
target_link_libraries(ComplexNumberTest gtest_main)
target_link_libraries(ComplexNumberTest main)
add_test(NAME ComplexNumberTest COMMAND ComplexNumberTest)

add_executable(RationalNumberTest tests/RationalNumberTest.cpp)
target_link_libraries(RationalNumberTest gtest_main)
target_link_libraries(RationalNumberTest main)
add_test(NAME RationalNumberTest COMMAND RationalNumberTest)

add_executable(MatrixTest tests/MatrixTest.cpp)
target_link_libraries(MatrixTest gtest_main)
target_link_libraries(MatrixTest main)
add_test(NAME MatrixTest COMMAND MatrixTest)

add_executable(VectorTest tests/VectorTest.cpp)
target_link_libraries(VectorTest gtest_main)
target_link_libraries(VectorTest main)
add_test(NAME VectorTest COMMAND VectorTest)

add_executable(ParserTest tests/ParserTest.cpp)
target_link_libraries(ParserTest gtest_main)
target_link_libraries(ParserTest main)
add_test(NAME ParserTest COMMAND ParserTest)

