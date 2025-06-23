class EnhancedDiagonalMemory:
    def __init__(self, word_size=16):
        """
        Усовершенствованная диагональная память с дополнительными функциями
        :param word_size: размер слова (по умолчанию 16 бит)
        """
        self.word_size = word_size
        self.memory = [[0]*word_size for _ in range(word_size)]
        self.operations_map = {
            'CONJ': lambda a, b: [x & y for x, y in zip(a, b)],
            'DISJ': lambda a, b: [x | y for x, y in zip(a, b)],
            'XOR': lambda a, b: [x ^ y for x, y in zip(a, b)],
            'NEG': lambda a: [1-x for x in a],
            'IMP': lambda a, b: [1 if (x==1 and y==0) else 0 for x, y in zip(a, b)],
            'EQ': lambda a, b: [1 if x==y else 0 for x, y in zip(a, b)]
        }

    def initialize(self, matrix_data=None):
        """Инициализация памяти с возможностью случайной генерации"""
        if matrix_data:
            self._validate_matrix(matrix_data)
            self.memory = [row.copy() for row in matrix_data]
        else:
            import random
            self.memory = [[random.randint(0,1) for _ in range(self.word_size)] 
                          for _ in range(self.word_size)]

    def _validate_matrix(self, matrix):
        """Валидация входной матрицы"""
        if len(matrix) != self.word_size or any(len(row) != self.word_size for row in matrix):
            raise ValueError(f"Матрица должна быть размером {self.word_size}x{self.word_size}")
        if any(x not in (0,1) for row in matrix for x in row):
            raise ValueError("Матрица должна содержать только 0 и 1")

    def read_word(self, address, rotated=False):
        """
        Чтение слова по адресу
        :param rotated: если True, возвращает слово в обычном порядке (без диагонального сдвига)
        """
        if rotated:
            return self.memory[address].copy()
        return [self.memory[(i+address) % self.word_size][address] for i in range(self.word_size)]

    def write_word(self, address, data, rotated=False):
        """Запись слова по адресу"""
        if len(data) != self.word_size:
            raise ValueError(f"Длина данных должна быть {self.word_size}")
        
        if rotated:
            self.memory[address] = data.copy()
        else:
            for i in range(self.word_size):
                self.memory[(i+address) % self.word_size][address] = data[i]

    def read_column(self, column_idx):
        """Чтение столбца"""
        return [self.read_word(i)[column_idx] for i in range(self.word_size)]

    def perform_operation(self, op_name, *operands):
        """Выполнение логической операции"""
        if op_name not in self.operations_map:
            raise ValueError(f"Неподдерживаемая операция: {op_name}. Доступные: {list(self.operations_map.keys())}")
        return self.operations_map[op_name](*operands)

    def find_pattern(self, pattern, start=0, direction=1):
        """
        Поиск шаблона в памяти
        :param pattern: искомый шаблон (список битов)
        :param start: начальный адрес поиска
        :param direction: направление поиска (1 - вперед, -1 - назад)
        :return: список адресов, где найден шаблон
        """
        matches = []
        for i in range(self.word_size):
            addr = (start + direction*i) % self.word_size
            if self.read_word(addr) == pattern:
                matches.append(addr)
        return matches

    def arithmetic_operation(self, control_bits, operation='ADD'):
        """
        Арифметические операции над полями A и B
        :param control_bits: контрольные биты (3 бита)
        :param operation: тип операции (ADD, SUB, MUL)
        """
        ops = {
            'ADD': lambda a, b: a + b,
            'SUB': lambda a, b: a - b,
            'MUL': lambda a, b: a * b
        }
        
        for addr in range(self.word_size):
            word = self.read_word(addr)
            if word[:3] == control_bits:
                A = self._bits_to_int(word[3:7])
                B = self._bits_to_int(word[7:11])
                result = ops[operation](A, B) % 32
                new_word = word[:11] + self._int_to_bits(result, 5)
                self.write_word(addr, new_word)

    def _bits_to_int(self, bits):
        """Конвертация битов в целое число"""
        return int(''.join(map(str, bits)), 2)

    def _int_to_bits(self, number, bit_count):
        """Конвертация числа в битовый список"""
        return [int(x) for x in f"{number:0{bit_count}b}"[-bit_count:]]

    def visualize(self, highlight=None):
        """Визуализация памяти с подсветкой"""
        from tabulate import tabulate
        table = []
        for i, row in enumerate(self.memory):
            if highlight and i == highlight:
                table.append([f"\033[91m{x}\033[0m" for x in row])
            else:
                table.append(row)
        print(tabulate(table, tablefmt="grid"))