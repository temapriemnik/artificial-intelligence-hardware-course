def binary_representation(number, bits):
    """Конвертация числа в бинарный формат заданной длины"""
    return ''.join('1' if number & (1 << (bits - 1 - i)) else '0' for i in range(bits))

def process_expression(input_expr):
    """Обработка и нормализация логического выражения"""
    vars_list = sorted({char for char in input_expr if char.isalpha() and char.islower()})
    cleaned_expr = input_expr.replace(' ', '')
    replacements = [
        ('∨', '+'), ('∧', '*'), ('→', '→'),
        ('->', '→'), ('∼', '↔'), ('~', '↔'),
        ('¬', '~')
    ]
    for old, new in replacements:
        cleaned_expr = cleaned_expr.replace(old, new)
    return vars_list, cleaned_expr

def compute_expression(postfix_expr, var_values):
    """Вычисление значения постфиксного выражения"""
    calculation_stack = []
    operations = {
        '~': lambda x: 1 - x,
        '*': lambda x, y: x and y,
        '+': lambda x, y: x or y,
        '→': lambda x, y: 0 if x == 1 and y == 0 else 1,
        '↔': lambda x, y: 1 if x == y else 0
    }
    
    for token in postfix_expr:
        if token in operations:
            if token == '~':
                operand = calculation_stack.pop()
                calculation_stack.append(operations[token](operand))
            else:
                right = calculation_stack.pop()
                left = calculation_stack.pop()
                calculation_stack.append(operations[token](left, right))
        else:
            calculation_stack.append(var_values[token])
    return calculation_stack[0]

def convert_to_postfix(normalized_expr):
    """Преобразование инфиксного выражения в постфиксное"""
    op_priority = {'~': 5, '*': 4, '+': 3, '→': 2, '↔': 1}
    output_queue = []
    operator_stack = []
    
    i = 0
    while i < len(normalized_expr):
        current = normalized_expr[i]
        if current.isalpha():
            output_queue.append(current)
        elif current == '(':
            operator_stack.append(current)
        elif current == ')':
            while operator_stack[-1] != '(':
                output_queue.append(operator_stack.pop())
            operator_stack.pop()
        else:
            while (operator_stack and operator_stack[-1] != '(' and 
                   op_priority.get(operator_stack[-1], 0) >= op_priority.get(current, 0)):
                output_queue.append(operator_stack.pop())
            operator_stack.append(current)
        i += 1
    
    while operator_stack:
        output_queue.append(operator_stack.pop())
    
    return output_queue

def create_truth_matrix(variables, postfix_expr):
    """Создание матрицы истинности"""
    var_count = len(variables)
    truth_data = []
    for combination in range(2 ** var_count):
        values = [(combination >> (var_count - 1 - pos)) & 1 for pos in range(var_count)]
        var_dict = dict(zip(variables, values))
        result = compute_expression(postfix_expr, var_dict)
        truth_data.append((values, result))
    return truth_data

def construct_normal_forms(truth_data, variables):
    """Построение нормальных форм"""
    dnf_parts = []
    cnf_parts = []
    dnf_nums = []
    cnf_nums = []
    index_value = 0
    
    for row_num, (inputs, output) in enumerate(truth_data):
        index_value = (index_value << 1) | output
        
        if output:
            dnf_nums.append(str(row_num))
            terms = []
            for var, val in zip(variables, inputs):
                terms.append(f"{var if val else '~' + var}")
            dnf_parts.append('(' + ' * '.join(terms) + ')')
        else:
            cnf_nums.append(str(row_num))
            terms = []
            for var, val in zip(variables, inputs):
                terms.append(f"{'~' + var if val else var}")
            cnf_parts.append('(' + ' + '.join(terms) + ')')
    
    return {
        'dnf': ' + '.join(dnf_parts),
        'cnf': ' * '.join(cnf_parts),
        'dnf_nums': ', '.join(dnf_nums),
        'cnf_nums': ', '.join(cnf_nums),
        'index': f"{index_value} ({binary_representation(index_value, len(truth_data))})"
    }

def execute_analysis():
    """Основная функция выполнения анализа"""
    user_expr = input("Введите логическое выражение: ")
    vars_list, processed_expr = process_expression(user_expr)
    postfix_form = convert_to_postfix(processed_expr)
    truth_matrix = create_truth_matrix(vars_list, postfix_form)
    forms = construct_normal_forms(truth_matrix, vars_list)

    print("\nМатрица истинности:")
    header = ' | '.join(vars_list) + ' | Значение'
    print(header)
    print('-' * len(header))
    for inputs, output in truth_matrix:
        print(' | '.join(map(str, inputs)) + f' | {output}')

    print("\nДизъюнктивная форма:")
    print(forms['dnf'])
    print("Числовая ДНФ: ∨(", forms['dnf_nums'], ")")

    print("\nКонъюнктивная форма:")
    print(forms['cnf'])
    print("Числовая КНФ: ∧(", forms['cnf_nums'], ")")

    print("\nИндексная форма:")
    print(forms['index'])

if __name__ == "__main__":
    execute_analysis()