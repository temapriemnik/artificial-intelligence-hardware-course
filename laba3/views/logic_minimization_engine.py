class Minimizer:
    def reduce_terms(self, terms):
        """Different minimization approach"""
        return list(set(terms))
    
    def combine_implicants(self, a, b):
        """Alternative combining method"""
        return f"({a}|{b})"