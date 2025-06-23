from views.expression_nodes import NodeSystem

class Interface:
    def __init__(self):
        self.parser = NodeSystem()
    
    def start(self):
        print("Custom Logic Tool v2.1")
        while True:
            user_input = input("> ")
            if user_input.lower() == 'exit':
                break
            tokens = self.parser.tokenize_input(user_input)
            print(f"Tokens: {tokens}")

if __name__ == "__main__":
    app = Interface()
    app.start()