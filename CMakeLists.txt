    cmake_minimum_required(VERSION 3.28)
    project(VroomVroom LANGUAGES CXX)

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)

    include(FetchContent)
    FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
    FetchContent_MakeAvailable(SFML)

    add_executable(VroomVroom)

    target_sources(VroomVroom PRIVATE
        src/main.cpp
        src/util/singleton.hpp
        src/core/gsm.cpp
        src/core/game.cpp
        src/states/demo_state.cpp
        src/render/render_context.cpp
        src/util/event_handler.cpp
        src/util/logger.cpp
    )

    target_include_directories(VroomVroom PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

    target_compile_features(VroomVroom PRIVATE cxx_std_17)
    target_link_libraries(VroomVroom PRIVATE
        SFML::Graphics
        SFML::Audio
        SFML::Network
    )

    add_custom_target(copy_assets ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:VroomVroom>/assets
    )
    add_dependencies(VroomVroom copy_assets)