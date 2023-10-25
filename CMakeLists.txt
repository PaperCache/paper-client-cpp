cmake_minimum_required(VERSION 3.12)

project(paper_client_cpp LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB CPP_FILES ${PROJECT_SOURCE_DIR}/lib/*.cpp)
file(GLOB TEST_FILES ${PROJECT_SOURCE_DIR}/tests/*.cpp)

if (NOT TARGET paper_client_c)
	add_subdirectory(${PROJECT_SOURCE_DIR}/extern/paper-client-c)
endif()

add_library(${PROJECT_NAME} ${CPP_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PUBLIC paper_client_c)

if (BUILD_TESTING_CPP)
	enable_testing()

	if (NOT TARGET Catch2)
		add_subdirectory(${PROJECT_SOURCE_DIR}/extern/Catch2)
	endif()

	foreach (test_file ${TEST_FILES})
		get_filename_component(file_name ${test_file} NAME_WE)
		add_executable(${file_name} ${test_file})

		target_link_libraries(${file_name} PRIVATE ${PROJECT_NAME})
		target_link_libraries(${file_name} PRIVATE Catch2::Catch2WithMain)

		add_test(NAME ${file_name} COMMAND ${file_name})
	endforeach()
endif()
