cmake_minimum_required(VERSION 3.12)

project(paper_client_cpp LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB CPP_FILES ${PROJECT_SOURCE_DIR}/lib/*.cpp)

if (NOT TARGET paper_client_c)
	add_subdirectory(${PROJECT_SOURCE_DIR}/extern/paper-client-c)
endif()

add_library(${PROJECT_NAME} ${CPP_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PUBLIC paper_client_c)
