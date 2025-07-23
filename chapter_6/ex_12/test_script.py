# test_script.py
"""
This is to test the camelcase detection code.
"""

# A simple function to greet a user
def greet(name):
    print(f"Hello, {name}!")

# A function that checks if a number is even or odd
def checkEvenOrOdd(myNumber):
    if myNumber % 2 == 0:
        print(f"{myNumber} is even.")
    else:
        print(f"{myNumber} is odd.")

# Assigning values to variables
x = 5
y = 10
z = x + y

# Calling the functions
greet("Alice")
checkEvenOrOdd(z)

# A for-loop example
for i in range(3):
    print(f"Iteration {i}")

# An example of list comprehension
squares = [i * i for i in range(5)]
print(squares)

# Lambda function example
squareLambda = lambda x: x * x
print(squareLambda(4))

# A class with a method
class Calculator:
    def add(self, aGoof, bFoog, cDooh=0):
        return aGoof + bFoog + cDooh

calc = Calculator()
print(calc.add(3, 4))

# Multiple assignments in a single line
someA, someB, someC = 1, 2, 3
print(someA, someB, someC)
