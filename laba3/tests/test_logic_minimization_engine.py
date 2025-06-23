import unittest
from ..views.expression_nodes import NodeSystem

class TestNodeSystem(unittest.TestCase):
    def setUp(self):
        self.system = NodeSystem()
    
    def test_tokenizer(self):
        result = self.system.tokenize_input("A & B")
        self.assertEqual(len(result), 3)