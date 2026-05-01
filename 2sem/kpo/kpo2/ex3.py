import unittest
def summ_of_dividers(a,b):
    max_summ = 0 
    max = 0
    if a>b:
        raise ValueError
    if (a<b):
        for i in range(a, b+1):
            x=0
            for k in range(1,i+1):
                if (i%k==0):
                    x = x + k
                if (max_summ<x):
                    max_summ = x
                    max = i
        return max
class numbers_test(unittest.TestCase):
    def test_dividers_1(self):
        self.assertEqual(summ_of_dividers(1,5),4)
    def test_dividers_2(self):
        self.assertEqual(summ_of_dividers(1,10),10)
    def test_dividers_3(self):
        self.assertEqual(summ_of_dividers(1,100),96)
    def test_dividers_4(self):
        with self.assertRaises(ValueError):
           summ_of_dividers(5,3)
    def test_dividers_5(self):
        self.assertEqual(summ_of_dividers(1,1000),960)
if __name__ == "__main__":
    a = int(input())
    b = int(input())
    print ()
    unittest.main()