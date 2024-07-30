cmake_minimum_required(VERSION 3.10)
project(dino_game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Encuentra la librería SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Encuentra la librería SDL2_ttf
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIRS})

# Encuentra la librería SDL2_image
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

# Añadir directorios de inclusión
include_directories(include)

# Recopilar todos los archivos fuente en src
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Añadir el ejecutable
add_executable(dino_game ${SOURCES})

# Especificar las rutas manualmente para SDL2, SDL2_ttf y SDL2_image en macOS
include_directories(/opt/homebrew/include)
link_directories(/opt/homebrew/lib)

# Vincular SDL2, SDL2_ttf y SDL2_image con tu ejecutable
target_link_libraries(dino_game
    ${SDL2_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    /opt/homebrew/lib/libSDL2.dylib
    /opt/homebrew/lib/libSDL2_ttf.dylib
    /opt/homebrew/lib/libSDL2_image.dylib
)

# Configurar los flags de compilación
target_compile_definitions(dino_game PRIVATE SDL_MAIN_HANDLED)

message(STATUS "SDL2 libraries: ${SDL2_LIBRARIES}")
message(STATUS "SDL2_ttf libraries: ${SDL2_TTF_LIBRARIES}")
message(STATUS "SDL2_image libraries: ${SDL2_IMAGE_LIBRARIES}")
