class QuineMcCluskey:
    def __init__(self):
        self.steps = []
    
    def run(self, minterms):
        """Simplified QM algorithm"""
        self.steps.append(f"Processing {len(minterms)} minterms")
        return ["Result1", "Result2"]