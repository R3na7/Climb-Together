cmake_minimum_required(VERSION 3.20)
project(Climb_Together)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-fsanitize=address,leak,undefined")
if(MINGW)
    set(CMAKE_CXX_FLAGS "-static -mwindows")
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build" FORCE)
    set(CMAKE_CXX_FLAGS "-fsanitize=address,leak,undefined -Wall")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(SOURCES 
    src/main.cpp
    src/game.cpp    
    src/game_menu.cpp
    src/init_menu.cpp
    src/collidable.cpp
    src/object.cpp

    src/Entity/entity.cpp
    src/Entity/player.cpp

    src/World/world.cpp

    src/Animation/animation.cpp
    src/Animation/animation_component.cpp

    src/UI/ui_element.cpp
    src/UI/button.cpp

    src/Interactive/interactivable.cpp
)
set(RESOURCES_DIR "resources")

# Настройка FetchContent
include(FetchContent)
set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/external")
set(FETCHCONTENT_QUIET OFF)

# Загрузка raylib
FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "5.5" 
)

FetchContent_MakeAvailable(raylib)


# Загрузка Box2D
FetchContent_Declare(
    box2d
    GIT_REPOSITORY "https://github.com/erincatto/box2d.git"
    GIT_TAG "v2.4.1" 
)
    
set(BOX2D_BUILD_TESTBED OFF)
set(BUILD_SHARED_LIBS OFF)
set(BOX2D_BUILD_UNIT_TESTS OFF CACHE BOOL "Disable Box2D unit tests" FORCE)
set(BOX2D_BUILD_TESTBED OFF CACHE BOOL "Disable Box2D testbed" FORCE)

FetchContent_MakeAvailable(box2d)

add_executable(${PROJECT_NAME} ${SOURCES})

# Настройка include-директорий
target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/include/Animation"
    "${CMAKE_SOURCE_DIR}/include/Entities"
    "${CMAKE_SOURCE_DIR}/include/Menu"
    "${CMAKE_SOURCE_DIR}/include/UI"
    "${CMAKE_SOURCE_DIR}/include/World"
    "${CMAKE_SOURCE_DIR}/include/Interactive"
    "${CMAKE_SOURCE_DIR}/external/tmxlite/tmxlite/include"
    "${box2d_SOURCE_DIR}/include/box2d"

)

# Линковка библиотек
target_link_libraries(${PROJECT_NAME} PRIVATE 
    raylib
    box2d
    ${CMAKE_SOURCE_DIR}/external/tmxlite/tmxlite/build/libtmxlite.a
)

# Платформо-специфичные настройки
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE opengl32 gdi32 winmm)
endif()
if(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
    )
endif()

if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        GL pthread dl rt X11
    )
endif()

# Копирование ресурсов при конфигурации
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})
