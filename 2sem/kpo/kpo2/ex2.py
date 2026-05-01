import unittest
def fibonacci_recursion(n):
    if n <= 1:
        return n 
    return fibonacci_recursion(n-1) + fibonacci_recursion(n-2)
def fibonacci(n):
    if n <= 1:
        return n
    a, b = 0, 1
    for i in range (2, n+1):
        a, b = b, a + b
    return b
class Test_fibonacci(unittest.TestCase):
  def test_1_recursion(self):
      self.assertEqual(fibonacci_recursion(1), 1)
  def test_2_recursion(self):
      self.assertEqual(fibonacci_recursion(2), 1)
  def test_5_recursion(self):
      self.assertEqual(fibonacci_recursion(5), 5)
  def test_10_recursion(self):
      self.assertEqual(fibonacci_recursion(10),55)
  def test_15_recursion(self):
      self.assertEqual(fibonacci_recursion(15), 610)
if __name__ == '__main__':
    print( fibonacci(int(input())))
unittest.main()

