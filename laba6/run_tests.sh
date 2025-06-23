#!/bin/bash

set -e  # Прерывать при ошибках

# Очистка предыдущей сборки
rm -rf build
mkdir -p build
cd build

# Конфигурация
cmake .. -DENABLE_COVERAGE=ON -DCMAKE_BUILD_TYPE=Debug

# Сборка
make -j$(nproc)

# Запуск тестов
echo -e "\n\033[1;34mRunning tests...\033[0m"
ctest --output-on-failure

make coverage-quick

cd ..
rm -rf build