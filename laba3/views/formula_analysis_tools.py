class FormulaInspector:
    @staticmethod
    def check_syntax(formula):
        """Simplified syntax check"""
        return all(c.isalpha() or c in '&|!()' for c in formula)
    
    def count_operators(self, formula):
        """Alternative counting method"""
        return sum(1 for c in formula if c in '&|!')