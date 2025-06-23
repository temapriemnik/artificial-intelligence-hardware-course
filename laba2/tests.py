# test_logic_analyzer.py

import unittest
from logic_analyzer import *

class TestLogicFunctions(unittest.TestCase):
    def test_binary_conversion(self):
        self.assertEqual(binary_representation(5, 4), '0101')
        self.assertEqual(binary_representation(0, 3), '000')
        self.assertEqual(binary_representation(15, 4), '1111')
        self.assertEqual(binary_representation(63, 6), '111111')

    def test_expression_processing(self):
        vars, expr = process_expression('(a∨b)*¬c')
        self.assertEqual(vars, ['a', 'b', 'c'])
        self.assertEqual(expr, '(a+b)*~c')

        vars, expr = process_expression('x→y~z')
        self.assertEqual(vars, ['x', 'y', 'z'])
        self.assertEqual(expr, 'x→y↔z')

    def test_postfix_evaluation(self):
        self.assertEqual(compute_expression(['a', 'b', '+'], {'a':1, 'b':0}), 1)
        self.assertEqual(compute_expression(['a', '~'], {'a':1}), 0)
        self.assertEqual(compute_expression(['a', 'b', '→'], {'a':1, 'b':1}), 1)

    def test_postfix_conversion(self):
        self.assertEqual(convert_to_postfix('a+b'), ['a', 'b', '+'])
        self.assertEqual(convert_to_postfix('~a*b'), ['a', '~', 'b', '*'])
        self.assertEqual(convert_to_postfix('(a+b)*c'), ['a', 'b', '+', 'c', '*'])

    def test_truth_matrix(self):
        vars = ['a', 'b']
        postfix = ['a', 'b', '*']
        matrix = create_truth_matrix(vars, postfix)
        self.assertEqual(matrix, [
            ([0, 0], 0),
            ([0, 1], 0),
            ([1, 0], 0),
            ([1, 1], 1)
        ])

    def test_normal_forms(self):
        matrix = [([0], 0), ([1], 1)]
        forms = construct_normal_forms(matrix, ['a'])
        self.assertEqual(forms['dnf'], '(a)')
        self.assertEqual(forms['cnf'], '(a)')
        self.assertEqual(forms['index'], '1 (01)')

    def test_complete_workflow(self):
        vars, expr = process_expression('a*b')
        postfix = convert_to_postfix(expr)
        matrix = create_truth_matrix(vars, postfix)
        forms = construct_normal_forms(matrix, vars)
        
        self.assertEqual(len(matrix), 4)
        self.assertEqual(forms['dnf_nums'], '3')

if __name__ == '__main__':
    unittest.main()