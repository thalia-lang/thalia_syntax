cmake_minimum_required(VERSION 3.9)
project(
	ThaliaSyntax
	VERSION 0.0.0
	DESCRIPTION "Thalia syntax analizer and optimizer"
	LANGUAGES CXX
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	set(CMAKE_CXX_STANDARD 17 CACHE STRING "The C++ standard to use")
	set(CMAKE_CXX_STANDARD_REQUIRED ON)
	set(CMAKE_CXX_EXTENSIONS OFF)

	file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
	if(EXISTS "${LOC_PATH}")
		message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
	endif()

	include(CheckIPOSupported)
	check_ipo_supported(RESULT IPO_SUPPORTED)
	if(IPO_SUPPORTED)
		message(STATUS "Interprocedural optimization supported")
	else()
		message(STATUS "Interprocedural optimization not supported")
	endif()

	if(MSVC)
		add_compile_options(/W4 /WX)
	else()
		add_compile_options(-Wall -Wextra -pedantic -Werror)
	endif()
endif()

set(THALIA_SYNTAX_PUBLIC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(THALIA_SYNTAX_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(THALIA_SYNTAX_DEMO_DIR "${CMAKE_CURRENT_SOURCE_DIR}/demo")

file(GLOB THALIA_SYNTAX_PUBLIC "${THALIA_SYNTAX_PUBLIC_DIR}/*.hpp" "${THALIA_SYNTAX_PUBLIC_DIR}/**/*.hpp")
file(GLOB THALIA_SYNTAX_SOURCES "${THALIA_SYNTAX_SOURCE_DIR}/*.cpp" "${THALIA_SYNTAX_SOURCE_DIR}/**/*.cpp")
file(GLOB THALIA_SYNTAX_DEMO_SOURCES "${THALIA_SYNTAX_DEMO_DIR}/*.cpp" "${THALIA_SYNTAX_DEMO_DIR}/**/*.cpp")

add_library(thalia_syntax "${THALIA_SYNTAX_SOURCES}" "${THALIA_SYNTAX_TOOLS}")
target_include_directories(thalia_syntax PRIVATE "${THALIA_SYNTAX_SOURCE_DIR}")
target_include_directories(thalia_syntax PUBLIC "${THALIA_SYNTAX_PUBLIC_DIR}")
if(IPO_SUPPORTED)
  set_target_properties(thalia_syntax PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

add_executable(demo "${THALIA_SYNTAX_DEMO_SOURCES}")
target_include_directories(demo PRIVATE "${THALIA_SYNTAX_PUBLIC_DIR}")
target_include_directories(demo PRIVATE "${THALIA_SYNTAX_DEMO_DIR}")
target_link_libraries(demo thalia_syntax)

install(FILES ${THALIA_SYNTAX_PUBLIC} DESTINATION include/thalia/syntax)
install(TARGETS thalia_syntax ARCHIVE DESTINATION lib)
