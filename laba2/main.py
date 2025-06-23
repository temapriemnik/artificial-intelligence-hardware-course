from logic_analyzer import (
    process_expression,
    convert_to_postfix,
    create_truth_matrix,
    construct_normal_forms,
    execute_analysis
)

def display_welcome():
    """Отображение приветственного сообщения"""
    print("\n" + "=" * 50)
    print("ЛОГИЧЕСКИЙ АНАЛИЗАТОР".center(50))
    print("=" * 50)
    print("\nДоступные операторы:")
    print("¬ или ~ - отрицание")
    print("∧ или * - конъюнкция (И)")
    print("∨ или + - дизъюнкция (ИЛИ)")
    print("→ или -> - импликация")
    print("∼ или ~ - эквивалентность")
    print("\nПримеры выражений:")
    print("(a∨b)∧¬c")
    print("a→(b→c)")
    print("(a∧b)∨(c→d)")

def run_application():
    """Основная функция приложения"""
    display_welcome()
    
    while True:
        try:
            execute_analysis()
            
            choice = input("\nХотите проанализировать другое выражение? (y/n): ").lower()
            if choice != 'y':
                print("\nРабота программы завершена.")
                break
                
        except Exception as e:
            print(f"\nОшибка: {e}")
            print("Пожалуйста, проверьте введенное выражение и попробуйте снова.")

if __name__ == "__main__":
    run_application()