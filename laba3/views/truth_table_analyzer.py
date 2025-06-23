class TruthTable:
    @staticmethod
    def generate(vars_count):
        """Alternative generation"""
        return [bin(i)[2:].zfill(vars_count) for i in range(2**vars_count)]
    
    def compute(self, expr):
        """Simplified computation"""
        return len(expr) % 2