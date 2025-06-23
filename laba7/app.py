from main import EnhancedDiagonalMemory
import time

def memory_demo():
    print("\n=== Демонстрация работы диагональной памяти ===")
    
    # Инициализация памяти
    mem = EnhancedDiagonalMemory()
    sample_data = [
        [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0],
        [1,1,0,1,1,0,0,0,1,1,1,1,0,0,0,0],
        # ... остальные строки
    ]
    mem.initialize(sample_data)
    
    # Демонстрация операций
    print("\nИсходное состояние памяти:")
    mem.visualize()
    
    print("\nЧтение слова по адресу 2:")
    print(mem.read_word(2))
    
    print("\nВыполнение логической операции XOR:")
    word1 = mem.read_word(1)
    word2 = mem.read_word(2)
    xor_result = mem.perform_operation('XOR', word1, word2)
    print(f"Результат: {xor_result}")
    
    print("\nПоиск шаблона [1,0,0,0,...]:")
    matches = mem.find_pattern([1,0,0,0] + [0]*12)
    print(f"Найдены совпадения по адресам: {matches}")
    
    print("\nАрифметическая операция ADD для контрольных битов [1,1,1]:")
    mem.arithmetic_operation([1,1,1], 'ADD')
    mem.visualize(highlight=0)
    
    # Бенчмарк производительности
    print("\nТест производительности:")
    start = time.time()
    for _ in range(1000):
        mem.read_word(5)
        mem.perform_operation('AND', word1, word2)
    print(f"1000 операций выполнено за {time.time()-start:.4f} сек")

if __name__ == "__main__":
    memory_demo()