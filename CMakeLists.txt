cmake_minimum_required(VERSION 3.10)
project(FPS_Game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${OPENGL_INCLUDE_DIR})

# Source files
set(SOURCES
    src/main.cpp
    src/engine/game.cpp
    src/engine/window.cpp
    src/engine/input.cpp
    src/engine/camera.cpp
    src/graphics/shader.cpp
    src/graphics/mesh.cpp
    src/graphics/renderer.cpp
    src/physics/physics.cpp
    src/entity/player.cpp
    src/entity/enemy.cpp
    src/entity/projectile.cpp
    src/world/world.cpp
)

# Create executable
add_executable(fps_game ${SOURCES})

# Link libraries
target_link_libraries(fps_game
    ${OPENGL_LIBRARIES}
    glfw
    glm::glm
)
