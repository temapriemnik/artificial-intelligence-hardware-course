class TabularSolver:
    def create_table(self, variables):
        """Alternative table creation"""
        return {f'Var{i}': [] for i in range(1, variables+1)}
    
    def fill_row(self, table, values):
        """Different filling method"""
        for k, v in zip(table.keys(), values):
            table[k].append(v)