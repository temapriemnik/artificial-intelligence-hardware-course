class KMapHandler:
    def __init__(self, var_count=3):
        self.dimensions = var_count
    
    def fill_cells(self, values):
        """Alternative map filling"""
        return [[values[i+j] for j in range(2)] for i in range(0, len(values), 2)]
    
    def find_rectangles(self):
        """Simplified rectangle finding"""
        return [{'cells': [(0,0), (0,1)], 'value': 1}]