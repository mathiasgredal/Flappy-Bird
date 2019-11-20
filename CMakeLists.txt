cmake_minimum_required(VERSION 3.12)
project(flappy-bird)

set (CMAKE_CXX_STANDARD 17)
add_compile_definitions(GL_SILENCE_DEPRECATION)

add_subdirectory(dependencies)


add_executable(${PROJECT_NAME} "src/main.cpp"
	src/AssetLoader.cpp
	src/MapGenerator.cpp
	src/Player.cpp
	src/UI_Navigation.cpp src/AssetLoader.h src/MapGenerator.h src/Player.h src/UI_Navigation.h)

target_link_libraries(${PROJECT_NAME} 
  PUBLIC
    ImGui-SFML::ImGui-SFML
)

file(COPY Assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
