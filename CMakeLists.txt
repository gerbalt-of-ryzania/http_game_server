cmake_minimum_required(VERSION 3.11)

project(game_server CXX)
set(CMAKE_CXX_STANDARD 20)
add_compile_definitions(BOOST_ALL_NO_LIB)

if(MSVC)
    add_compile_options(/bigobj)
endif()

if(EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo_multi.cmake")
    include("${CMAKE_BINARY_DIR}/conanbuildinfo_multi.cmake")
else()
    include("${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
endif()
conan_basic_setup(TARGETS)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(GAME_SERVER_SOURCES
    src/infra/http_server.cpp
    src/infra/http_server.h
    src/sdk.h
    src/domain/game/model.h
    src/domain/game/model.cpp
    src/domain/game/geom.h
    src/domain/game/loot_generator.h
    src/domain/game/loot_generator.cpp
    src/domain/game/collision_detector.h
    src/domain/game/collision_detector.cpp
    src/domain/game/tagged.h
    src/domain/game/json_loader.h
    src/domain/game/json_loader.cpp
    src/domain/game/extra_data.h
    src/domain/game/extra_data.cpp
    src/storage/records_repository.h
    src/storage/records_repository.cpp
    src/api/middleware/request_utils.h
    src/api/middleware/request_utils.cpp
    src/api/serializers/game_serializers.h
    src/api/serializers/game_serializers.cpp
    src/api/static_files/static_file_handler.h
    src/api/handlers/responses.h
    src/api/handlers/request_handler.cpp
    src/api/handlers/request_handler.h
)

add_executable(game_server
    src/main.cpp
    ${GAME_SERVER_SOURCES}
)
target_include_directories(game_server PRIVATE
    src
    src/api/handlers
    src/api/middleware
    src/api/serializers
    src/api/static_files
    src/domain/game
    src/infra
    src/storage
)
target_link_libraries(game_server PRIVATE
    Threads::Threads
    CONAN_PKG::boost
    CONAN_PKG::libpqxx
)

add_executable(game_server_tests
    ${GAME_SERVER_SOURCES}
    tests/loot_generator_tests.cpp
    tests/model-tests.cpp
)
target_include_directories(game_server_tests PRIVATE
    src
    src/api/handlers
    src/api/middleware
    src/api/serializers
    src/api/static_files
    src/domain/game
    src/infra
    src/storage
)
target_link_libraries(game_server_tests PRIVATE
    Threads::Threads
    CONAN_PKG::catch2
    CONAN_PKG::boost
    CONAN_PKG::libpqxx
)

enable_testing()
add_test(NAME game_server_tests COMMAND game_server_tests)
