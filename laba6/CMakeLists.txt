cmake_minimum_required(VERSION 3.10)
project(hash_table_avl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включение покрытия кода
option(ENABLE_COVERAGE "Enable code coverage reporting" OFF)

if(ENABLE_COVERAGE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        message(STATUS "Code coverage enabled")
        add_compile_options(-fprofile-arcs -ftest-coverage)
        add_link_options(--coverage)
    else()
        message(WARNING "Code coverage not supported for this compiler")
    endif()
endif()

# Подключаем папку с заголовками
include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

# Основная библиотека
add_library(hash_table_avl STATIC
    src/avl_tree.cpp
    src/hash_table.cpp
)

# Основное приложение
add_executable(hash_table_app src/main.cpp)
target_link_libraries(hash_table_app hash_table_avl)

# Тесты
enable_testing()
add_subdirectory(tests)

# Настройка генерации отчёта о покрытии
if(ENABLE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    find_program(LCOV lcov REQUIRED)
    find_program(GENHTML genhtml REQUIRED)
    find_program(GCOVR gcovr REQUIRED)

    add_custom_target(coverage
        # Очистка предыдущих данных
        COMMAND ${LCOV} --directory . --zerocounters
        # Запуск тестов
        COMMAND ctest --output-on-failure
        # Сбор данных
        COMMAND ${LCOV} --capture --directory . --output-file coverage.info
        # Фильтрация
        COMMAND ${LCOV} --remove coverage.info '*/usr/*' '*/tests/*' '*/include/*' '/usr/include/*' --output-file filtered.info
        # Генерация HTML
        COMMAND ${GENHTML} filtered.info --output-directory coverage-report
        # Альтернативный отчёт
        COMMAND ${GCOVR} -r ${CMAKE_SOURCE_DIR} --exclude-unreachable-branches --exclude-throw-branches --html-details -o coverage-gcovr.html
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generating coverage reports"
        DEPENDS hash_table_tests
    )

    # Упрощённая цель для быстрой проверки покрытия
    add_custom_target(coverage-quick
        COMMAND ${GCOVR} -r ${CMAKE_SOURCE_DIR} --exclude-unreachable-branches --exclude-throw-branches
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Quick coverage report"
    )
endif()