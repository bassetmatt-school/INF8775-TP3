cmake_minimum_required(VERSION 3.16)

project(
	"TP3"
	LANGUAGES
	CXX
)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_compile_options(
	-Wall
	-Wextra
	-pedantic
	-O3
	-std=c++20
)
add_executable(tp3
	${SRC_FILES}
)


target_include_directories(tp3
	PRIVATE
	${PROJECT_SOURCE_DIR}/include
)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(tp3 ${SDL2_LIBRARIES})

set_target_properties(tp3
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/bin
)
