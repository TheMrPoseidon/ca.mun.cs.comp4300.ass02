find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_library(ass02_lib
    ../include/Vec2.hpp
    ../include/Entity.hpp
    ../include/EntityManager.hpp
    ../include/Game.hpp
    ../include/Components.hpp
    Vec2.cpp
    EntityManager.cpp
    Entity.cpp
    Game.cpp)
add_library(ass02::lib ALIAS ass02_lib)

target_link_libraries(ass02_lib
        PUBLIC ass02::compiler_options sfml-graphics sfml-audio)
target_include_directories(ass02_lib PUBLIC "${PROJECT_SOURCE_DIR}/include")

if(${BP_BUILD_TESTS_COVERAGE})
    target_compile_options(ass02_lib PUBLIC -fprofile-arcs -ftest-coverage)
    target_link_libraries(ass02_lib PUBLIC gcov)
endif()

add_executable(ass02_app "main.cpp")
target_link_libraries(ass02_app PRIVATE ass02::lib)
add_dependencies(ass02_app ass02_assets)