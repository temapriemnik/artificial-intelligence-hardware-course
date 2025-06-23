# Поиск GoogleTest
find_package(GTest REQUIRED)
include(GoogleTest)

# Создание исполняемого файла для тестов
add_executable(hash_table_tests
    test_avl_tree.cpp
    test_hash_table.cpp
)

# Линковка с библиотекой и GTest
target_link_libraries(hash_table_tests
    PRIVATE
    hash_table_avl
    GTest::GTest
    GTest::Main
)

# Для покрытия кода
if(ENABLE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(hash_table_tests PRIVATE --coverage)
    target_link_options(hash_table_tests PRIVATE --coverage)
endif()

# Автоматическое обнаружение тестов
gtest_discover_tests(hash_table_tests
    PROPERTIES
    LABELS "unit_tests"
    TIMEOUT 10
)

# Дополнительные цели для удобства
add_custom_target(run_tests
    COMMAND ctest --output-on-failure
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS hash_table_tests
    COMMENT "Running all tests"
)