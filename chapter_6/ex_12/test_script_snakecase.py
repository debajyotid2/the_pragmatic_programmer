"""
This is to test the camelcase detection code.
"""

def greet(name):
    print(f'Hello, {name}!')

def check_even_or_odd(my_number):
    if my_number % 2 == 0:
        print(f'{my_number} is even.')
    else:
        print(f'{my_number} is odd.')
x = 5
y = 10
z = x + y
greet('Alice')
check_even_or_odd(z)
for i in range(3):
    print(f'Iteration {i}')
squares = [i * i for i in range(5)]
print(squares)
square_lambda = lambda x: x * x
print(square_lambda(4))

class Calculator:

    def add(self, a_goof, b_foog, c_dooh=0):
        return a_goof + b_foog + c_dooh
calc = Calculator()
print(calc.add(3, 4))
some_a, some_b, some_c = (1, 2, 3)
print(some_a, some_b, some_c)