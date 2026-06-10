cmake_minimum_required(VERSION 3.20)
project(ToonShader VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# ---------------------------------------------------------------------------
# Core engine library (fetches its own dependencies + runs its own tests)
# ---------------------------------------------------------------------------
FetchContent_Declare(SpeltEngine
        GIT_REPOSITORY https://github.com/r11b22/SpeltEngine.git
        GIT_TAG        main
)

FetchContent_MakeAvailable(SpeltEngine)

# ---------------------------------------------------------------------------
# Application executable
# ---------------------------------------------------------------------------
add_executable(${PROJECT_NAME}
    main.cpp
        src/ToonScene.cpp
        include/ToonScene.h
        src/OutlineRenderPass.cpp
        include/OutlineRenderPass.h
        include/MainRenderPass.h
        src/MainRenderPass.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# All headers, libs, and compile options come transitively from CGVCCore
target_link_libraries(${PROJECT_NAME} PRIVATE SpeltEngine)
