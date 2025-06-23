class TreeConstructor:
    def __init__(self):
        self.node_id = 0
    
    def create_node(self, value):
        """Unique node creation"""
        self.node_id += 1
        return {'id': self.node_id, 'value': value, 'branches': []}
    
    def connect_nodes(self, parent, child):
        """Different linking approach"""
        parent['branches'].append(child)