import unittest
from main import EnhancedDiagonalMemory

class TestEnhancedMemory(unittest.TestCase):
    def setUp(self):
        self.mem = EnhancedDiagonalMemory(8)  # Используем уменьшенный размер для тестов
        test_data = [
            [1,0,0,0,0,0,0,1],
            [0,1,0,0,0,0,1,0],
            [0,0,1,0,0,1,0,0],
            [0,0,0,1,1,0,0,0],
            [1,1,1,1,0,0,0,0],
            [0,0,0,0,1,1,1,1],
            [1,0,1,0,1,0,1,0],
            [0,1,0,1,0,1,0,1]
        ]
        self.mem.initialize(test_data)

    def test_memory_operations(self):
        # Тест чтения/записи
        self.assertEqual(self.mem.read_word(0), [1,0,0,0,1,0,1,0])
        self.mem.write_word(0, [1]*8)
        self.assertEqual(self.mem.read_word(0), [1]*8)
        
        # Тест столбцов
        self.assertEqual(self.mem.read_column(0), [1,0,0,0,1,0,1,0])
        
        # Тест логических операций
        a = self.mem.read_word(1)
        b = self.mem.read_word(2)
        self.assertEqual(self.mem.perform_operation('CONJ', a, b), [0,0,0,0,0,0,0,0])
        self.assertEqual(self.mem.perform_operation('DISJ', a, b), [0,1,1,0,1,1,1,1])
        
        # Тест арифметики
        self.mem.write_word(3, [1,1,1,0,0,1,0,1,0,1,0,1,0,0,0,0])
        self.mem.arithmetic_operation([1,1,1], 'ADD')
        result = self.mem.read_word(3)
        self.assertEqual(result[11:16], [1,0,1,1,0])  # 5 + 10 = 15 (01010 + 00101 = 01111)

    def test_pattern_search(self):
        self.assertEqual(self.mem.find_pattern([1,0,0,0,1,0,1,0]), [0])
        self.mem.write_word(4, self.mem.read_word(0))
        self.assertEqual(len(self.mem.find_pattern(self.mem.read_word(0))), 2)

    def test_edge_cases(self):
        # Тест пустой инициализации
        empty_mem = EnhancedDiagonalMemory(4)
        empty_mem.initialize()
        self.assertEqual(len(empty_mem.read_word(0)), 4)
        
        # Тест исключений
        with self.assertRaises(ValueError):
            empty_mem.initialize([[1,0],[0,1]])
        with self.assertRaises(ValueError):
            empty_mem.perform_operation('UNKNOWN', [1,0])

if __name__ == "__main__":
    unittest.main(failfast=True)