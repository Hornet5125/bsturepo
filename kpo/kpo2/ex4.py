import unittest
def numbers(n,p,arr):
    x = 0.0
    if n < 0:
        raise ValueError
    for i in range(n): 
        if arr[i] > 20.5:
            x = x + arr[i]
    if x >= p:
        return False
    if x<p:
        return True
class numbers_test(unittest.TestCase):
    def test_numbers_3_200(self):
        arr=[100.0, 50.0, 30.0]
        self.assertEqual(numbers(3,200,arr),True)
    def test_numbers_5_80(self):
        arr = [100.0, 50.0, 30.0, 50.0, 40.0]
        self.assertEqual(numbers(5,80,arr),False)
    def test_numbers_1_50(self):
        arr=[25]
        self.assertEqual(numbers(1,50,arr),True)
    def test_negative(self):
        with self.assertRaises(ValueError):
            numbers(-1,0,arr)
    def test_numbers_2_90(self):
        arr = [25.0, 50.0]
        self.assertEqual(numbers(2,90,arr),True)
if __name__ == '__main__':
    arr = []
    n = int(input())
    p = int(input())
    for i in range(n):
        arr.append(float(input()))
    unittest.main()	
