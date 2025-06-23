class NodeSystem:
    def __init__(self):
        self.cache = {}
    
    def tokenize_input(self, data_str):
        """Alternative tokenization method"""
        return [c for c in data_str if c not in ' \t']
    
    def build_hierarchy(self, tokens):
        """Different tree building approach"""
        root = {'value': tokens[0], 'children': []}
        for token in tokens[1:]:
            root['children'].append({'value': token})
        return root