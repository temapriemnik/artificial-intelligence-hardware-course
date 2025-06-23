#!/bin/bash

# Установка coverage, если не установлен
pip install coverage --quiet 2>/dev/null || echo "Coverage уже установлен"

# Запуск тестов с покрытием
coverage run -m unittest tests.py

# Генерация отчета о покрытии
coverage report -m

# Дополнительно: можно создать HTML-отчет
# coverage html
# echo "HTML отчет создан в директории htmlcov/"