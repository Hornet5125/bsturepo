import time 
start = time.time()
n = 25
def fibonacci_recursion(n):
    if n <= 1:
        return n 
    return fibonacci_recursion(n-1) + fibonacci_recursion(n-2)
print(fibonacci_recursion(n))
def fibonacci(n):
    if n <= 1:
        return n
    a, b = 0, 1
    for i in range (2, n+1):
        a, b = b, a + b
    return b
print(fibonacci(n))
end = time.time() - start
print(end)
